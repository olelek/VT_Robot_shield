/*
  _03_Robot_GetDistanceSerial

*/
#include <Robot_shield.h>

int zone = 20;  //"Secure" distance in cm

void setup()
{
  Robot.begin();
}

void loop()
{
  int measureIt = Robot.getDistance();
  if(measureIt <= zone) {
    Robot.beep(500);
    Robot.turnLight(ON);
  }
  else {
    Robot.noBeep();
    Robot.turnLight(OFF);
  }
  delay(100);
}
