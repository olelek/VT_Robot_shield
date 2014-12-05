/*
  Robot_shield.cpp - Robot Shield library
  Written by Aleksander Kawęczyński
  Copyright (c) 2014 Virtmedia  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "Robot_shield.h"
#include <IRremote.h>
#ifdef VTROBOTS_H_

const int echo = 8;
const int trig = 9;
const int r_dir = 7;
const int r_pwm = 11;
const int l_dir = 4;
const int l_pwm = 5;
const int piezo = 6;
const int ir = 10;
const int led = 12;
const int sw1 = A4;

_Robot Robot;
static int backlight = 1;
IRrecv irrecv(ir);
decode_results results;
#endif
_Robot::_Robot() {
}

void _Robot::begin()
{
    speed = 100;
	pinMode(trig, OUTPUT);
	pinMode(r_dir, OUTPUT);
	pinMode(r_pwm, OUTPUT);
	pinMode(l_dir, OUTPUT);
	pinMode(l_pwm, OUTPUT);
	pinMode(piezo, OUTPUT);
	pinMode(led, OUTPUT); 
	pinMode(echo, INPUT);
	pinMode(sw1, INPUT_PULLUP);
	analogWrite(r_pwm,0);
	analogWrite(l_pwm,0);
	digitalWrite(r_dir,LOW);
	digitalWrite(l_dir,LOW);
	digitalWrite(trig,LOW);
	irrecv.enableIRIn(); // Start the receiver
}

long _Robot::getDistance(void)
{
  long duration;
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  return microsecondsToCentimeters(duration);
}

long _Robot::microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void _Robot::goForward(void)
{
  digitalWrite(r_dir,HIGH);
  digitalWrite(l_dir,HIGH);
  analogWrite(r_pwm,255-speed);
  analogWrite(l_pwm,255-speed);
}

void _Robot::goBackward(void)
{
  digitalWrite(r_dir,LOW);
  digitalWrite(l_dir,LOW);
  analogWrite(r_pwm,speed);
  analogWrite(l_pwm,speed);
}

void _Robot::turnRight(void)
{
  digitalWrite(r_dir,HIGH);
  digitalWrite(l_dir,LOW);
  analogWrite(r_pwm,255-speed);
  analogWrite(l_pwm,speed);
}

void _Robot::turnLeft(void)
{
  digitalWrite(r_dir,LOW);
  digitalWrite(l_dir,HIGH);
  analogWrite(r_pwm,speed);
  analogWrite(l_pwm,255-speed);
}

void _Robot::stop(void)
{
  digitalWrite(r_dir,LOW);
  digitalWrite(l_dir,LOW);
  analogWrite(r_pwm,0);
  analogWrite(l_pwm,0);
}

void _Robot::timerFix()
{
  #define sbi(sfr,b) (_SFR_BYTE(sfr) |= _BV(b))
  #if defined(__AVR_ATmega32U4__)
  //Tone will have hijacked the timer used for the 
  //RGB led RED channel so once we're done we need
  //to restore it.  First shutdown the tone internals
  //if not done already...
  noTone(piezo);

  //Now clear the Timer Count Control Registers to
  //have them in a known state.
  TCCR3A = 0;
  TCCR3B = 0;

  //Setup the clock source - clk/64 
  sbi(TCCR3B, CS31);
  sbi(TCCR3B, CS30);

  //Set the wave form generator for 10-bit PWM
  sbi(TCCR3A, WGM30);

  //re-link the PWM timer to output channel
  //by passing something other than 0 and 255
  //so that the analogWrite function is forced to
  //recompute the correct value for either the
  //OCR3A or OCR3B register (output control register) 
  //as appropriate
  #endif
  analogWrite(5, 1);

  //turn the LED channel off
  analogWrite(5, 0);
}

void _Robot::turnLight(byte State)
{
	digitalWrite(led, State);
}

void _Robot::beep(unsigned int frequency)
{
	tone(piezo, frequency);
}

void _Robot::beep(unsigned int frequency, unsigned long duration)
{
	tone(piezo, frequency, duration);
}

void _Robot::noBeep(void)
{
	noTone(piezo);
	timerFix();
}

String _Robot::dump(decode_results *results) 
{
  String message;
  if (results->decode_type == UNKNOWN) {
    message = "UNK";
  } 
  else if (results->decode_type == NEC) {
    message = "NEC";
  } 
  else if (results->decode_type == SONY) {
    message = "SON";
  } 
  else if (results->decode_type == RC5) {
    message = "RC5";
  } 
  else if (results->decode_type == RC6) {
    message = "RC6";
  }
  else if (results->decode_type == PANASONIC) {	
    message = "PAN";
  }
  else if (results->decode_type == JVC) {
    message = "JVC";
  }
  return message;
}

byte _Robot::switchRead()
{
	return !digitalRead(sw1);
}

void _Robot::setMotorSpeed(byte Speed)
{
	speed = Speed;
}