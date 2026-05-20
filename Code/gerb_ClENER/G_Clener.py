import re

class GRBLCleaner:
    def __init__(self):
        # keep only safe GRBL commands
        self.allowed_prefixes = {
            "G0", "G1", "G2", "G3",
            "G4",
            "G20", "G21",
            "G28", "G90", "G91",
            "M3", "M4", "M5",
            "M30",
            "F", "S",
            "X", "Y", "Z", "A", "B", "C",
            "I", "J", "K",
            "T"
        }

        self.last_motion = None

    def strip_comments(self, line):
        # remove ; comments
        line = re.sub(r";.*", "", line)
        # remove () comments
        line = re.sub(r"\(.*?\)", "", line)
        return line.strip()

    def normalize(self, line):
        line = line.upper().strip()
        line = re.sub(r"\s+", " ", line)
        return line

    def is_safe_line(self, line):
        if not line:
            return False

        cmd = line.split()[0]

        # allow pure coordinates lines (X Y Z only)
        if re.match(r"^[XYZFMS]", cmd):
            return True

        # allow G/M codes
        if cmd in self.allowed_prefixes:
            return True

        return False

    def clean_line(self, line):
        line = self.strip_comments(line)
        if not line:
            return None

        line = self.normalize(line)

        if not self.is_safe_line(line):
            return None

        return line

    def reduce_redundancy(self, lines):
        cleaned = []
        last = None

        for line in lines:
            if not line:
                continue

            # skip repeated identical motion commands
            if line == last:
                continue

            # merge empty motion duplicates (optional optimization)
            if line.startswith("G1") and last and last.startswith("G1"):
                if line.split() == last.split():
                    continue

            cleaned.append(line)
            last = line

        return cleaned

    def enforce_absolute_mode(self, lines):
        # ensure G90 exists at start
        if not any("G90" in l for l in lines):
            return ["G90"] + lines
        return lines

    def clean_file(self, input_path, output_path):
        with open(input_path, "r") as f:
            raw_lines = f.readlines()

        cleaned = []

        for line in raw_lines:
            c = self.clean_line(line)
            if c:
                cleaned.append(c)

        cleaned = self.reduce_redundancy(cleaned)
        cleaned = self.enforce_absolute_mode(cleaned)

        with open(output_path, "w") as f:
            for line in cleaned:
                f.write(line + "\n")

        return cleaned


if __name__ == "__main__":
    cleaner = GRBLCleaner()

    inp = "input.gcode"
    out = "cleaned.gcode"

    result = cleaner.clean_file(inp, out)

    print(f"Done. Lines: {len(result)}")