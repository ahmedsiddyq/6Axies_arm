#include"motoedriver.h"

typedef struct
{
    uint16_t ratio;      //step per revluio
    float theta_i;

    float min_theta;     // use float if angles can be decimal
    float max_theta;

    bool dir; // 1 for postive
} stepper;


stepper m[num_axies];



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





void stepper_motion_all(flotes theata)
{
	for(uint8_t i=1;i<num_axies;i++)
	{
	float theata_d=m[i].theta_i-m[i].theta_i;
	m[i].theta_i=theata_desierd;
	if(theata_d<0)
	{																				
	
	}
	
	eles
	{
	}	
    }	
}