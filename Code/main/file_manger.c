#include "file_manger.h"
#include "esp_heap_caps.h"
#include <Arduino.h>

#define MAX_POSES 1000                  // max number of poses that can be stored

flotes* poseBuffer_pointer = NULL;      // pointer to the start of PSRAM block (no memory yet)
unsigned long poseCount = 0;            // how many poses are currently saved


void init_storge()
{
    // allocate 1000 × 12 = 12000 bytes in PSRAM and cast raw address to flotes*
    poseBuffer_pointer = (flotes*) ps_malloc(MAX_POSES * sizeof(flotes));
    //  sizeof(flotes)      → how many bytes is ONE pose struct = 12 bytes (3 floats × 4)
    //  ps_malloc(12000)    → allocate 12000 bytes in PSRAM
    //  (flotes*)           → CAST: tell C treat this address as pointer to flotes struct
    //             ┌─────────────┬─────────────┬─────────────┬─────
    //             │ d1 | d2 | d3│ d1 | d2 | d3│ d1 | d2 | d3│ ...
    //             │  [0]        │  [1]         │  [2]        │
    //             └─────────────┴─────────────┴─────────────┴─────
    //              ← 12 bytes  →← 12 bytes   →← 12 bytes   →

    if (poseBuffer_pointer == NULL) {
        // ps_malloc returns NULL if PSRAM is full or not enabled
        Serial.println("❌ PSRAM allocation failed!");
    }
    else {
        Serial.printf("✅ Allocated %d bytes in PSRAM\n", MAX_POSES * sizeof(flotes));
    }
}


bool save(flotes data, unsigned long i)
{
    if (i >= MAX_POSES) {               // prevent writing outside allocated memory
        Serial.println("❌ i out of range!");
        return false;
    }

    poseBuffer_pointer[i] = data;       // write the full flotes struct into PSRAM at index i
                                        // same as: poseBuffer_pointer[i].d1 = data.d1
                                        //          poseBuffer_pointer[i].d2 = data.d2
                                        //          poseBuffer_pointer[i].d3 = data.d3

    if (i >= poseCount) {
        poseCount = i + 1;              // update count so get() knows the valid range
    }                                   // example: save at i=5 → poseCount becomes 6

    return true;
}


flotes get(unsigned long i)
{
    if (i >= poseCount) {               // prevent reading unwritten memory
        Serial.println("❌ i out of range!");
        return {0, 0, 0};               // return empty pose instead of garbage data
    }
    return poseBuffer_pointer[i];       // read flotes struct from PSRAM at index i
}


void clearPoses() {
    poseCount = 0;                      // reset counter → old data still in PSRAM but ignored
}                                       // next save() will overwrite from index 0 again


void freePoseBuffer() {
    if (poseBuffer_pointer != NULL) {   // only free if memory was actually allocated
        free(poseBuffer_pointer);       // release the 12000 bytes back to PSRAM heap
        poseBuffer_pointer = NULL;      // set to NULL so no one can accidentally use freed memory
        poseCount = 0;                  // reset count since buffer no longer exists
    }
}