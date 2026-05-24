#pragma once
#include "esp_heap_caps.h"
#include <Arduino.h>
#define MAX_POSES 1000                  // max number of poses that can be stored

typedef struct {
    float d1;
    float d2;
    float d3;
} flotes;

void init_storge();
bool save(flotes data, unsigned long i);
flotes get(unsigned long i);
void clearPoses() ;
void freePoseBuffer() ;
