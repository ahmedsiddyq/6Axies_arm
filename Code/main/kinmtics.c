#include "kinmtics.h"

Theta pos2theta(float x, float y, float z)
{
    Theta t;

    float R = sqrtf(x*x + y*y + z*z);

    // θ1
    t.theta1 = atan2f(y, x);

    float c3 = (x*x + y*y + z*z - L1*L1 - L2*L2) / (2.0f * L1 * L2);

    // clamp safety to float errors
    if (c3 > 1.0f) c3 = 1.0f;
    if (c3 < -1.0f) c3 = -1.0f;

    t.theta3 = -acosf(c3);

    // θ2
    t.theta2 =
        asinf(z / R) +
        atan2f(L2 * sinf(t.theta3),
               L1 + L2 * cosf(t.theta3));

    return t;
}