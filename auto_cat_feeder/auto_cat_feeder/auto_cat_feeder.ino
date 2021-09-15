/*
 Name:		auto_cat_feeder.ino
 Created:	7/30/2021 7:16:14 PM
 Author:	bmk
*/
#include <Bounce.h>

#define RPMS                 175.0
#define STEP_PIN                9
#define DIRECTION_PIN           8
#define GO_PIN                  7
#define SLP_PIN                 6
#define STEPS_PER_REV         200
#define MICROSTEPS_PER_STEP     8
#define MICROSECONDS_PER_MICROSTEP   (1000000/(STEPS_PER_REV * MICROSTEPS_PER_STEP)/(RPMS / 60))

uint32_t LastStepTime = 0;
uint32_t CurrentTime = 0;

Bounce pushbutton = Bounce(GO_PIN, 10);  // 10 ms debounce

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(13, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
	pinMode(SLP_PIN, OUTPUT);
	pinMode(DIRECTION_PIN, OUTPUT);
	pinMode(GO_PIN, INPUT_PULLUP);
	digitalWrite(STEP_PIN, LOW);
	digitalWrite(DIRECTION_PIN, HIGH);
	digitalWrite(SLP_PIN, LOW);

	digitalWrite(13, HIGH);
}

// the loop function runs over and over again until power down or reset

int steps_per_press = 800;
//unsigned int six_hour_delay = 2160000;

void loop() 
{
	/*
  //move 1 step each high edge on "step"
	push_button_press();
	*/
	//feed_schedule(six_hour_delay);
	push_button_press();
}

void feed_schedule(long int delay_time)
{
	digitalWrite(SLP_PIN, HIGH);
	digitalWrite(13, LOW);
	for (int i = 0; i < steps_per_press; i++)
	{
		digitalWrite(STEP_PIN, HIGH);
		delay(1);
		digitalWrite(STEP_PIN, LOW);
		delay(1);
	}
	digitalWrite(13, HIGH);
	delay(delay_time);
}

void push_button_press()
{
	if (pushbutton.update())
	{
		if (pushbutton.fallingEdge())
		{
			digitalWrite(SLP_PIN, HIGH);
			digitalWrite(13, LOW);
			for (int i = 0; i < steps_per_press; i++)
			{
				digitalWrite(STEP_PIN, HIGH);
				delay(1);
				digitalWrite(STEP_PIN, LOW);
				delay(1);
			}
			digitalWrite(13, HIGH);
		}
	}
	else digitalWrite(SLP_PIN, LOW);
	delay(10);
}
