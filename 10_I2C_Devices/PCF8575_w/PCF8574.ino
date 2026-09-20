/*--------------------------------------------------------------
  Program:      two_wire_knigh_rider

  Description:  Uses a PCF8574 IO Expander IC on the Arduino
                TWI bus to interface 8 LEDs. A "knight
                rider" display is shown on the LEDs.

  Date:         25 April 2012

  Author:       W.A. Smith, http://startingelectronics.org
*/

#include <Wire.h>

// address of PCF8574 IC on TWI bus
#define IO_ADDR (0x40 >> 1)

void setup() {
  Wire.begin();        // initialize the I2C/TWI interface
}

void loop() {
  static unsigned char data = 0x01;  // data to display on LEDs
  static unsigned char direc = 1;    // direction of knight rider display

  // send the data to the LEDs
  Wire.beginTransmission(IO_ADDR);
  Wire.write(~data);
  Wire.endTransmission();
  delay(200);  // speed of display

  // shift the on LED in the specified direction
  if (direc) {
    data <<= 1;
  }
  else {
    data >>= 1;
  }
  // see if a direction change is needed
  if (data == 0x80) {
    direc = 0;
  }
  if (data == 0x01) {
    direc = 1;
  }
}
