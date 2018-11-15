#include <RASLib/inc/common.h>
#include <RASLib/inc/linesensor.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/adc.h>

static tMotor *left;
static tMotor *right;
static tADC *adc[2];
static tADC *adc2[1];
static tBoolean initialized = false;

void initLineSensor(void){
    if(initialized)
        return;
    initialized = true;
}

tBoolean led_on;
void blink(void) {
    SetPin(PIN_F1, led_on);
    SetPin(PIN_F3, !led_on);

    led_on = !led_on;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
int main(void) 
{
    CallEvery(blink, 0, 0.5f);
    left = InitializeServoMotor(PIN_E0, false);
    right = InitializeServoMotor(PIN_D3, true);
    adc[0] = InitializeADC(PIN_E2);
    adc[1] = InitializeADC(PIN_E3);
    int b1 = ADCRead(adc[0]) * 4096;
	//line sensor intialization
    adc2[0] = InitializeADC(PIN_E1);
    int b2 = ADCRead(adc2[0]) * 4096;
	//distance sensor intialization

    while(1)
    {
		if(ADCRead(adc[0]) * 4096 <= 3000)
		{
		SetMotor(left, -1);
		SetMotor(right, -1);
                Wait(.45);
		SetMotor(left, -1);
		SetMotor(right, 1);
		Wait(.85);
		}
		else if(ADCRead(adc[0]) * 4096 > 3000)
		{
			if(ADCRead(adc2[0]) * 4096 < 1900) 
			{
			SetMotor(left, .2);
			SetMotor(right, -.2);
		//sweeping detection motion
		//motion incorporated into sweep to help get checkpoint
			}
			else if(ADCRead(adc2[0]) * 4096 >= 1900)
		// previously 1000 but changed it to get checkpoint
			{
			Wait(.25);
			SetMotor(left, .85);
			SetMotor(right, 1);
			}
		//charge motion if within about 3 feet
		}
	//motion if reached edge
    }

}
