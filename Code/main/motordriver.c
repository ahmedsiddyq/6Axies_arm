#include"motoedriver.h"

typedef struct
{
	min_theta
	max_theta
	dir
}


void stepper_init() {
    // I2C (handled by Wire.begin, but shown for clarity)
    // Wire.begin(PIN_SDA, PIN_SCL);

    // Stepper DIR - Output
    pinMode(PIN_DIR1,  OUTPUT);
    pinMode(PIN_DIR2,  OUTPUT);
    pinMode(PIN_DIR3,  OUTPUT);
    pinMode(PIN_DIR4,  OUTPUT);
    pinMode(PIN_DIR5,  OUTPUT);

    // Stepper STEP - Output
    pinMode(PIN_STEP1, OUTPUT);
    pinMode(PIN_STEP2, OUTPUT);
    pinMode(PIN_STEP3, OUTPUT);
    pinMode(PIN_STEP4, OUTPUT);
    pinMode(PIN_STEP5, OUTPUT);

    // Limit Switches - Input with internal pull-up
    pinMode(PIN_LIMIT1, INPUT_PULLUP);
    pinMode(PIN_LIMIT2, INPUT_PULLUP);
    pinMode(PIN_LIMIT3, INPUT_PULLUP);
    pinMode(PIN_LIMIT4, INPUT_PULLUP);
    pinMode(PIN_LIMIT5, INPUT_PULLUP);
}





void motion(float*,)
{
	theata_d=theata_desierd-theatai
	theata_desierd=theatai
	if(theata_d<0)
	{
     dir=
	}
	eles
		
}

name 