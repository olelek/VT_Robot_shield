/*
  _05_Robot_switchTest

*/
#include <Robot_shield.h>

void setup()
{
	Robot.begin();
}

void loop()
{
    Robot.turnLight(Robot.switchRead());
    delay(10);
}
