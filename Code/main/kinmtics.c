#include "kinmtics.h"



flotes pos2theta(flotes pos)
{
    flotes t;
    float R = sqrtf(pos.d1*pos.d1 + pos.d2*pos.d2 + pos.d3*pos.d3);

    // Guard against degenerate case at origin
    if (R < 1e-6f)
    {
        t.d1 = 0.0f;
        t.d2 = 0.0f;
        t.d3 = 0.0f;
        return t;
    }

    // θ1
    t.d1 = atan2f(pos.d2, pos.d1);

    // θ3
    float c3 = (R*R - L1*L1 - L2*L2) / (2.0f * L1 * L2);

    // Clamp to [-1, 1] to guard against float precision errors
    if (c3 > 1.0f)  c3 = 1.0f;
    if (c3 < -1.0f) c3 = -1.0f;
    t.d3 = -acosf(c3);

    // θ2
    t.d2 =
        asinf(pos.d3 / R) +
        atan2f(L2 * sinf(t.d3),
               L1 + L2 * cosf(t.d3));

    return t;
}

void tehta_conversion()
{
	
for(i=0;i<dataSipos.d3e;i++)
 save(pos2theta(get(i), get(i),get(i)),i);

}