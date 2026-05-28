
#define PIN_SDA       3    // J1_13 - GPIO3
#define PIN_SCL       2    // J3_5  - GPIO2

// --- Stepper Motor DIR Pins (OUTPUT) ---
#define PIN_DIR1      4    // J1_4  - GPIO4
#define PIN_DIR2      6    // J1_6  - GPIO6
#define PIN_DIR3      8    // J1_12 - GPIO8
#define PIN_DIR4      10   // J1_16 - GPIO10
#define PIN_DIR5      12   // J1_18 - GPIO12

// --- Stepper Motor STEP Pins (OUTPUT) ---
#define PIN_STEP1     5    // J1_5  - GPIO5
#define PIN_STEP2     7    // J1_7  - GPIO7
#define PIN_STEP3     9    // J1_15 - GPIO9
#define PIN_STEP4     11   // J1_17 - GPIO11
#define PIN_STEP5     13   // J1_19 - GPIO13

// --- Limit Switches (INPUT_PULLUP) ---
#define PIN_LIMIT1    15   // J1_8  - GPIO15
#define PIN_LIMIT2    16   // J1_9  - GPIO16
#define PIN_LIMIT3    17   // J1_10 - GPIO17
#define PIN_LIMIT4    18   // J1_11 - GPIO18
#define PIN_LIMIT5    21   // J3_18 - GPIO21
#define num_axies     3

void stepper_init();