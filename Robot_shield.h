/*
  Robot_shield.h - Robot Shield library
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

#ifndef VTROBOTS_H_
#define VTROBOTS_H_

#include <Arduino.h>
#include <IRremote.h>


#define ON	1
#define OFF 0


class _Robot {
private:
    long microsecondsToCentimeters(long microseconds);
	void timerFix();
	int speed;
public:
    _Robot();
	void begin();
	long getDistance(void);
	void goForward(void);
	void goBackward(void);
	void turnRight(void);
	void turnLeft(void);
	void stop(void);
	void turnLight(byte State);
	void beep(unsigned int frequency);
	void beep(unsigned int frequency, unsigned long duration);
	void noBeep(void);
	void setMotorSpeed(byte Speed);
	String dump(decode_results *results); 
	byte switchRead();
};

extern _Robot Robot;
extern IRrecv irrecv;
extern decode_results results;
#endif // VTROBOTS_H_
