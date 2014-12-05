/*
  _13_Robot_RemoteLCD

*/
#include <Robot_shield.h>

#include <Wire.h>  // Comes with Arduino IDE
#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>

LiquidCrystal_I2C lcd(0x20, 4, 5, 6, 0, 1, 2, 3, 7, POSITIVE);  // Set the LCD I2C address

void setup()
{
  Robot.begin();
  lcd.begin(16,2);         // initialize the lcd for 16 chars 2 lines]
  lcd.setBacklightPin(7, NEGATIVE);
  lcd.setBacklight(HIGH);
  // NOTE: Cursor Position: CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Remote test");
  lcd.setCursor(0,1); //Start at character 0 on line 1
}

void loop()
{
  if(irrecv.decode(&results))
  {
    lcd.clear();
    lcd.setCursor(0,0); //Start at character 0 on line 0
    lcd.print("Remote test");
    lcd.setCursor(0,1); //Start at character 0 on line 1
    lcd.print(Robot.dump(&results));
    lcd.print("-");
    lcd.print(results.value);
    irrecv.resume();
  }
  delay(10);
}
