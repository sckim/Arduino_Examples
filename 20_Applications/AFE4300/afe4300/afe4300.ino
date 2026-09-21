/* AFE4300
by: Soochan Kim
date: April 20, 2016

This example code shows how you could use the Arduino SPI 
library to interface with a AFE4300.

Circuit:
Leonardo ICSP-------------- AFE4300 EVM (J103)
  5V   -------------------- VCC, 
  GND  -------------------- GND, 4 or 10 or 18
  4   -------------------- MOSI, 11
  1   -------------------- MISO, 13
  3   -------------------- SCLK, 3 
  8   -------------------- STE1, 1
  9   -------------------- RDY, 15
  10   -------------------- RESET_MCU, 8
    -------------------- CLK_MCU, 17, 1MHz from Funcion Gen
*/
#include <SPI.h> // Include the Arduino SPI library


/***************************
AFE4300 register address definitions
****************************/
#define ADC_DATA_RESULT         0x00
#define ADC_CONTROL_REGISTER    0x01
#define MISC1_REGISTER          0x02
#define MISC2_REGISTER          0x03
#define DEVICE_CONTROL_1        0x09
#define ISW_MATRIX              0x0A
#define VSW_MATRIX              0x0B
#define IQ_MODE_ENABLE          0x0C
#define WEIGHT_SCALE_CONTROL    0x0D
#define BCM_DAC_FREQ            0x0E
#define DEVICE_CONTROL_2        0x0F
#define ADC_CONTROL_REGISTER_2  0x10
#define MISC3_REGISTER          0x1A

// Define the SS pin
//  This is the only pin we can move around to any available
//  digital pin.
const int ssPin = 8; // output
const int rdyPin = 9; //input
const int rstmcuPin = 10;


// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal 
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimalsSPI(byte decimals)
{
  digitalWrite(ssPin, LOW);
  SPI.transfer(0x77);
  SPI.transfer(decimals);
  digitalWrite(ssPin, HIGH);
}

// write 3 bytes
// address MSB-byte LSB-byte
void writeRegister(unsigned char address, unsigned int data)
{
  digitalWrite(ssPin, LOW);


  unsigned char firstByte = (unsigned char)(data >> 8);
  unsigned char secondByte = (unsigned char)data;

  SPI.transfer(address);
  //Send 2 bytes to be written
  SPI.transfer(firstByte);
  SPI.transfer(secondByte);

  //SPI.transfer(firstByte,SPI_CONTINUE);
  //SPI.transfer(secondByte,SPI_LAST);

  digitalWrite(ssPin, HIGH);
}       


int readRegister(unsigned char address)
{
  int spiReceive = 0;
  unsigned char spiReceiveFirst = 0;
  unsigned char spiReceiveSecond = 0;
  address = address & 0x1F; //Last 5 bits specify address
  address = address | 0x20; //First 3 bits need to be 001 for read opcode

  digitalWrite(ssPin, LOW);
  SPI.transfer(address);
  spiReceiveFirst  = SPI.transfer(0x00);
  spiReceiveSecond = SPI.transfer(0x00);
  digitalWrite(ssPin, HIGH);


  //Combine the two received bytes into a signed int
  spiReceive = (spiReceiveFirst << 8);
  spiReceive |= spiReceiveSecond;
  return spiReceive;
}

void initAFE4300()
{
  writeRegister(ADC_CONTROL_REGISTER,0x5140);
  writeRegister(MISC1_REGISTER,0x0000);
  writeRegister(MISC2_REGISTER,0xFFFF);
  writeRegister(DEVICE_CONTROL_1,0x6004); //Power down both signal chains
  writeRegister(BCM_DAC_FREQ,0x0040);
  writeRegister(ADC_CONTROL_REGISTER_2,0x0011);
  writeRegister(MISC3_REGISTER,0x0030);
}

int readData()
{
  return readRegister(ADC_DATA_RESULT);
}

void setup()
{
  // -------- SPI initialization
  pinMode(ssPin, OUTPUT);  // Set the SS pin as an output
  pinMode(rstmcuPin, OUTPUT);
  pinMode(rdyPin, INPUT);

  digitalWrite(ssPin, HIGH);  // Set the SS pin HIGH
  SPI.begin();  // Begin SPI hardware
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // Slow down SPI clock as 2MHz
  SPI.setDataMode(SPI_MODE1); // falling edge



  initAFE4300();
}


char tempString[10];  // Will be used with sprintf to create strings

void loop()
{
  // Magical sprintf creates a string for us to send to the s7s.
  //  The %4d option creates a 4-digit integer.
  sprintf(tempString, "%4d", readData());


  delay(10);  // This will make the display update at 100Hz.*/
}

