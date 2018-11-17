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

	if(ADCRead(adc2[0]) * 4096 < 1900)
	{
	SetMotor(left, .85);
	SetMotor(right, 1);
	Wait(1);
	}
		//intial motion if no robot in front of us
    while(1)
    {
		if(ADCRead(adc[0]) * 4096 <= 2000)
		{
		SetMotor(left, -1);
		SetMotor(right, -1);
                Wait(.65);
		SetMotor(left, 1);
		SetMotor(right, -1);
		Wait(.65);
		}
		//back up motoin if hit white line
		else if(ADCRead(adc[0]) * 4096 > 3000)
		{
			if(ADCRead(adc2[0]) * 4096 < 1845) 
			{
			SetMotor(left, .3);
			SetMotor(right, -.3);
		//turning detection motion
			}
			else if(ADCRead(adc2[0]) * 4096 > 1845 && ADCRead(adc2[0]) * 4096 < 1850)
			{
			SetMotor(left, -1);
			SetMotor(right, 1);
			}
		//counter motion to help lock onto other robot
			else if(ADCRead(adc2[0]) * 4096 >= 1850 && ADCRead(adc2[0]) * 4096 <= 3000)
			{
			SetMotor(left, .75);
			SetMotor(right, 1);
			}
		//intial start of chase code if a wait timer is needed to help lock on but don't need it at the moment 
			else if(ADCRead(adc2[0]) * 4096 >= 3000)
			{
			SetMotor(left, .75);
			SetMotor(right, 1);
			}
		//second part of chrge motion with no wait timer so it does not fall off field 
		}
    }

}
