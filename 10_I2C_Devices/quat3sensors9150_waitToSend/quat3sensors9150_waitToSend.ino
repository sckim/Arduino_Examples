// for mpu 9150 (with magnetometer). outputs quaterion of 3 sensors with a delay to make printing just 
//    slower than reading speed of simulink model used in EMG+sensor data acquision 
//    waits for serial command 's' to start sending data

// this script relies on a few edits to the standard libraries:
//    inv_mpu.ccp line 453. addr for each instance of MPU needs to be 0x69. 
//    inv_mpu.h line 36. MPU_MAX_DEVICES must = 3
//    MPU9150Lib.cpp line 445. negate 'newYaw'. Thus the line should be "m_fusedEulerPose[VEC3_Z] = -newYaw;"

//////printed strings when initializing the device. 
//Arduino9150 starting       // printed by this script
//Using mag cal              // printed by MPU9150Lib.ccp line 196 in "#ifdef MPULIB_DEBUG" statement
//Setting up compass         // printed by inv_mpu.ccp line 692 in a "#ifdef MPU_DEBUG" statement
//Compass sens: 278 279 291  // printed by inv_mpu.ccp line 2343 in a "#ifdef MPU_DEBUG" statement
//Loading firmware           // printed by MPU9150Lib.ccp line 220 
//Firmware loaded
//Using mag cal
//Setting up compass
//Compass sens: 289 291 305
//Loading firmware
//Firmware loaded

////////////////////////////////////////////////////////////////////////////
//
//  This file is part of MPU9150Lib
//
//  Copyright (c) 2013 Pansenti, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of 
//  this software and associated documentation files (the "Software"), to deal in 
//  the Software without restriction, including without limitation the rights to use, 
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
//  Software, and to permit persons to whom the Software is furnished to do so, 
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <Wire.h>    //TWI/I2C library
#include "I2Cdev.h"   // Abstracts bit and byte I2C R/W functions into a convenient class
#include "MPU9150Lib.h"
#include "CalLib.h"   // part of mpu9159Lib. erase, write, and read data in EEPROM. uses DueFlash if "due version," uses EEPROM if "AVR version"(i think we have avr)
#include <dmpKey.h> //in "MotionDriver" library, used in inv_mpu_dmp_motion_driver.h/ccp
#include <dmpmap.h> //in "MotionDriver" library, used in inv_mpu_dmp_motion_driver.h/ccp
#include <inv_mpu.h> //in "MotionDriver" library, used in inv_mpu_dmp_motion_driver.h/ccp
#include <inv_mpu_dmp_motion_driver.h>  //in "MotionDriver" library
#include <EEPROM.h>

//need to change numDevices and the variable in MPU[].  Works well with 2 devices.  breaks down with 3. 

int numDevices = 3;
MPU9150Lib MPU[MPU_MAX_DEVICES]; // MPU_NUM_DEVICEs must == 3 (set in inv_mpu.h line 36)

#define MPU_UPDATE_RATE  (15) //15 works pretty well //rate (in Hz) at which the MPU updates the sensor data and DMP output (<=100Hz)

//  MAG_UPDATE_RATE should be less than or equal to the MPU_UPDATE_RATE

#define MAG_UPDATE_RATE  (10)  //rate (in Hz) at which the MPU updates the magnetometer data
//must be <=MPU_UPDATE_RATE

//  MPU_MAG_MIX defines the influence that the magnetometer has on the yaw output.
//  The magnetometer itself is quite noisy so some mixing with the gyro yaw can help
//  significantly. Some example values are defined below:
// 0     // just use gyro yaw
// 1     // just use magnetometer and no gyro yaw
// 10    // a good mix value
// 50    // mainly gyros with a bit of mag correction

int MPU_MAG_MIX = 30;

#define MPU_LPF_RATE   10 //low pas filter rate and can be between 5 and 188Hz

//  SERIAL_PORT_SPEED defines the speed to use for the debug serial port

#define  SERIAL_PORT_SPEED  115200

int sensor1 = 4;
int sensor2 = 3;
int sensor3 = 2;

boolean runInitLoop = true;
boolean sendData = false;
char receivedVar;
float dataToSend[12];

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int active[3] = { sensor1, sensor2, sensor3 };

void setup() {
	// dont need anything here because initialization in main loop
}

void loop() {
	if (runInitLoop == true) {
		initialize();
		sweepFIFO();
		runInitLoop = false;
	}

	if (Serial.available()) {
		receivedVar = Serial.read();
		if (receivedVar == 's') { //start
			sendData = true;
		} else if (receivedVar == 'h') {  //halt
			sendData = false;
		} else if (receivedVar == 'r') { //reset
			runInitLoop = true;
			sendData = false;
		}
	}

	else if (sendData == true) {
		int temp = 0;
		for (int i = 0; i < numDevices; i++) {
			digitalWrite(active[i], HIGH);
			MPU[i].read();
			dataToSend[temp++] = MPU[i].m_fusedQuaternion[0];
			dataToSend[temp++] = MPU[i].m_fusedQuaternion[1];
			dataToSend[temp++] = MPU[i].m_fusedQuaternion[2];
			dataToSend[temp++] = MPU[i].m_fusedQuaternion[3];
			digitalWrite(active[i], LOW);
		}

		for (int i = 0; i < 4 * numDevices; i++) {
			if (i < (4 * numDevices - 1)) {
				Serial.print(dataToSend[i]);
				Serial.print("\t");
			} else if (i == (4 * numDevices - 1)) {
				Serial.println(dataToSend[i]);
			}
		}
    delay(12);  //12 ms delay results in .0277s btw samples (EMG mdl requires sampling at .025 so this is perfect)
	}  // end 'if sendData==true' loop
} //end main loop

// -------------- my functions ---------------- //

void initialize() {
	Serial.begin(SERIAL_PORT_SPEED);
//	Serial.println("Arduino9150 starting ...");

	Wire.begin();
	for (int i = 0; i < numDevices; i++) {
		pinMode(active[i], OUTPUT);
		digitalWrite(active[i], LOW); // make all the sensors have the address 0x68
	}

	for (byte i = 0; i < numDevices; i++) {
		//put a single sensor high so that when the addr 0x69 is read, the appropriate sensor is found
		digitalWrite(active[i], HIGH);

		MPU[i].useAccelCal(true); //just sets m_useAccelCalibration = true
		MPU[i].useMagCal(true);   //just sets m_useMagCalibration = true
		MPU[i].selectDevice(i);   //just sets m_device = i

//		MPU[i].init(MPU_UPDATE_RATE);
		MPU[i].init(MPU_UPDATE_RATE, MPU_MAG_MIX, MAG_UPDATE_RATE,
		MPU_LPF_RATE); // starts the MPU, loads firmware, returns 'true' if successful

		digitalWrite(active[i], LOW);
	}
}

//read each sensor as fast as possible to clear its fifo   
void sweepFIFO() {
	for (int i = 0; i < numDevices; i++) {
		digitalWrite(active[i], HIGH);

		while (MPU[i].read()) {
		} //continue to read until there is nothing to read (fifo empty)

		digitalWrite(active[i], LOW);
	}
}

