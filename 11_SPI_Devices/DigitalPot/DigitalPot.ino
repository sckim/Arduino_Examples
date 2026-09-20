#include "Arduino.h"

#include <SPI.h>
const int slaveSelectPin  = 7;

void setup()
{
  Serial.begin(115200);
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  // initialize SPI:
  SPI.begin();
}

int iPot=0;

void loop()
{
    // change the resistance on this channel from min to max:

    digitalPotWrite(iPot+=10);
    //digitalPotWrite(255);
    delay(1000); // Slave Select period, 10ms
    // wait a second at the top:
    // change the resistance on this channel from max to min:
    if( iPot> 256)
    	iPot=0;
    Serial.println(iPot);
}

void digitalPotWrite(int value)
{
  // take the SS pin low to select the chip:

  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(0);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}
