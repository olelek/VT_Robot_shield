/*
  _03_Robot_GetDistanceSerial

*/
#include <Robot_shield.h>

void setup()
{
  Serial.begin(9600);
  Robot.begin();
}

void loop()
{
  Serial.println(Robot.getDistance());
  delay(1000);
}
