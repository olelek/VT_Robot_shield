/*
  _02_Robot_beep

*/
#include <Robot_shield.h>

void setup()
{
  Robot.begin();
}

void loop()
{
  Robot.beep(500);
  delay(200);
  Robot.noBeep();
  delay(1000);
}
