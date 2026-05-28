#include "file_manager.h"

// ── Private state ─────────────────────────────────────────────────────────────
static flotes*        poseBuffer_pointer = NULL;  // PSRAM block start
static unsigned long  poseCount          = 0;     // valid entries written so far

// ── Init ──────────────────────────────────────────────────────────────────────
void init_storage() {

    // Guard: PSRAM must be detected before allocating
    if (!psramFound()) {
        Serial.println("❌ No PSRAM detected! Check board config.");
        return;
    }

    // Already initialised — don't double-allocate
    if (poseBuffer_pointer != NULL) {
        Serial.println("⚠️  Storage already initialised.");
        return;
    }

    //  ps_malloc → allocates in PSRAM (not DRAM)
    //  MAX_POSES × sizeof(flotes) = 1000 × 12 = 12 000 bytes
    poseBuffer_pointer = (flotes*) ps_malloc(MAX_POSES * sizeof(flotes));

    if (poseBuffer_pointer == NULL) {
        Serial.println("❌ PSRAM allocation failed!");
    } else {
        memset(poseBuffer_pointer, 0, MAX_POSES * sizeof(flotes)); // zero-fill
        Serial.printf("✅ Allocated %u bytes in PSRAM\n",
                      (unsigned)(MAX_POSES * sizeof(flotes)));
    }
}

bool save(flotes data, unsigned long i) {

    if (poseBuffer_pointer == NULL) {
        Serial.println("❌ Buffer not initialised! Call init_storage() first.");
        return false;
    }
    if (i >= MAX_POSES) {
        Serial.printf("❌ Index %lu out of range (max %d)!\n", i, MAX_POSES - 1);
        return false;
    }

    poseBuffer_pointer[i] = data;           // write struct directly into PSRAM slot

    if (i >= poseCount) {
        poseCount = i + 1;                  // extend valid range
    }
    return true;
}

Flotes get(unsigned long i) {

    if (poseBuffer_pointer == NULL || i >= poseCount) {
        if (poseBuffer_pointer == NULL)
            Serial.println("❌ Buffer not initialised!");
        else
            Serial.printf("❌ Index %lu out of range (count=%lu)!\n", i, poseCount);

        return {0, 0, 0};        
    }

    return poseBuffer_pointer[i]
}


// ── Clear (keeps PSRAM, resets logical count) ─────────────────────────────────
void clearPoses() {
    poseCount = 0;
    // optional: zero-fill PSRAM so stale data can't be accidentally read
    if (poseBuffer_pointer != NULL) {
        memset(poseBuffer_pointer, 0, MAX_POSES * sizeof(flotes));
    }
}

// ── Free PSRAM block ──────────────────────────────────────────────────────────
void freePoseBuffer() {
    if (poseBuffer_pointer != NULL) {
        free(poseBuffer_pointer);
        poseBuffer_pointer = NULL;
        poseCount          = 0;
        Serial.println("🗑️  PSRAM buffer freed.");
    }
}