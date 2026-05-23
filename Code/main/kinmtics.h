#define L0 1:2
#define L1 232
#define L2 188.5+59.5


#pragma once
#include <math.h>

typedef struct {
    float theta1;
    float theta2;
    float theta3;
} Theta;

Theta pos2theta(float x, float y, float z);



 