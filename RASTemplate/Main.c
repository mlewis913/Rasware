#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/adc.h>

// Blink the LED to show we're on
tBoolean blink_on = true;

void blink(void) 
{
    SetPin(PIN_F3, blink_on);
    blink_on = !blink_on;
}

//initializes the 6 ADC pins for the line sensor
static tADC *adc[3];
static tADC *adc2[3];
static tBoolean initialized = false;
void initGPIOLineSensor(void)
{	
    if(initialized)
	{
	    return;
	}
	
    initialized = true;	

    adc[0] = InitializeADC(PIN_D0);
    adc[1] = InitializeADC(PIN_D1);
    adc[2] = InitializeADC(PIN_D2);

}

void initGPIODistanceSensor(void)
{
	if(initialized)
	{
		return;
	}
	
	initialized = true;

	adc2[0] = InitializeADC(PIN_D3);
	adc2[1] = InitializeADC(PIN_D4);
	adc2[2] = InitializeADC(PIN_D5);

}

//displays values of the linesensor and distance sensor, use to find what colors
//correspond to which values
void gpioLineSensorDemo(void)
{
    while(!KeyWasPressed())
	{
	    Printf("Line Sensor values: %1.3f, %1.3f, %1.3f\r" + ADCRead(adc[0]) + ADCRead(adc[1]) + ADCRead(adc[2]));
	}

    Printf("\n");

}

void IRSensorDemo(void)
{
    while(!KeyWasPressed())
	{
	    Printf("Distance Sensor values: %1.3f, %1.3f, %1.3f\r" + ADCRead(adc2[0]) + ADCRead(adc2[1]) + ADCRead(adc2[2]));
	}

    Printf("\n");

}

//decleares motors
static tMotor *left;
static tMotor *right;





// The 'main' function is the entry point of the program
int main(void) 
{
	// Initialization code can go here
    
	CallEvery(blink, 0, 0.5);
    
	left = InitializeServoMotor(PIN_B6, false);
	right = InitializeServoMotor(PIN_B7, true);

    //infinite loops are bad, but for the purpose
    //of a never ending sumo battle that is started and stopped 
    //by a drop it will suffice
	/*while(1 > 0)
	{
		//SenorRead();
		//DistanceRead();
	}*/
   
}


void reverse()
{
	SetMotor(left,-1.0);
	SetMotor(right, -1.0);
}

void forward()
{
	SetMotor(left, 1.0);
	SetMotor(right, 1.0);
}

void left()
{
	SetMotor(left, -1.0);
	SetMotor(right, 1.0);
}

void right()
{
	SetMotor(left, 1.0);
	SetMotor(right, -1.0);
}

//need to know values before proceeding
/*
void SensorRead()
{
	int x = 0;
	int y = 1;
	int z = 2;
	//qualifiers needed for middle values like .5 between .75 and .2.5
	if(ADCRead(adc[x]) > && ADCRead(adc[y]) >  && ADCRead(adc[z]) > )
	{
		reverse();
	}
	
	if(ADCRead(adc[x]) >  && ADCRead(adc[y]) >  && ADCRead(adc[z]) > )
	{
		reverse();
	}
}
*/

/*
//not sure how many values or how the values
//are returned for the distance sensor yet
void DistanceRead()
{
	int x = 0;
	int y = 1;
	int z = 2;
	//qualifiers needed for middle values like .5 between .75 and .2.5
	if(ADCRead(adc2[x]) > && ADCRead(adc2[y]) >  && ADCRead(adc2[z]) > )
	{
		reverse();
	}
	
	if(ADCRead(adc2[x]) >  && ADCRead(adc2[y]) >  && ADCRead(adc2[z]) > )
	{
		reverse();
	}
}
