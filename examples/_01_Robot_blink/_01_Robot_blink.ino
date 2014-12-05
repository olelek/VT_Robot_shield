/*
  _01_Robot_blink

*/
#include <Robot_shield.h>

void setup()
{
	Robot.begin();
}

void loop()
{
    Robot.turnLight(ON);
    delay(400);
    Robot.turnLight(OFF);
    delay(400);
}
