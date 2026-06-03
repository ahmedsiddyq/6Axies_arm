#include "motoedriver.h"

void stepper_init()
{
    engine.init();

    for(int i = 0; i < num_axies; i++)
    {
        // Limit switch
        pinMode(PIN_LIMIT[i], INPUT_PULLUP);

        // Connect motor
        m[i].motor = engine.stepperConnectToPin(PIN_STEP[i]);

        // Configure motor
        m[i].motor->setDirectionPin(PIN_DIR[i]);
        m[i].motor->setEnablePin(PIN_ENABLE);
        m[i].motor->setAutoEnable(true);

        m[i].motor->setSpeedInHz(3000);
        m[i].motor->setAcceleration(10000);

        // default values
        m[i].theta_i = 0;
        m[i].ratio = 200;
        m[i].dir = 1;
    }
}	


void stepper_motion_all(flotes theta)
{
    for(uint8_t i = 0; i < num_axies; i++)
    {
        float theta_d = theta.d[i] - m[i].theta_i;

        long steps = (theta_d / 360.0f) * m[i].ratio;

        m[i].motor->move(steps);

        m[i].theta_i = theta.d[i];
    }
}
}