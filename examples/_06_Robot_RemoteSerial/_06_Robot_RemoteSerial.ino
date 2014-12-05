/*
  _06_Robot_RemoteSerial

*/
#include <Robot_shield.h>

void setup()
{
  Robot.begin();
  Serial.begin(9600);
}

void loop()
{
  if(irrecv.decode(&results))
  {
    Serial.print(Robot.dump(&results));
    Serial.print(" - ");
    Serial.println(results.value);
    irrecv.resume();
  }
  delay(10);
}
