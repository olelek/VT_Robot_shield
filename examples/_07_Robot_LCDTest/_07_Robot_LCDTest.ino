/*
  _07_Robot_LCDTest

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

byte smileChar[8] = {
	0b00000,
	0b00000,
	0b01010,
	0b00000,
	0b10001,
	0b01110,
	0b00000,
	0b00000
};

void setup()
{
  Robot.begin();
  lcd.begin(16,2);         // initialize the lcd for 20 chars 4 lines]
  lcd.createChar(1, smileChar);
  lcd.setBacklightPin(7, NEGATIVE);
  lcd.setBacklight(HIGH);
  // NOTE: Cursor Position: CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Hello World! \x01");
  lcd.setCursor(4,1); //Start at character 4 on line 1
  lcd.print("Robot Shield");
}

void loop()
{
  // put your main code here, to run repeatedly:
  
}
