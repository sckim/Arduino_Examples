//Example Arduino sketch used to control two digital potential in a video tutorial on the ForceTronics YouTube Channel
//This code is in the public domain and free for anybody to use at their own risk

// SCK  13
// MOSI 11
// CS   2

#include "SPI.h" //SPI communication library

int nVolatile = 0b00100000; //status register value to store resistance value in non-volatile memory
int vWrite = 0b00000000; //status register to write resistance value (volatile)
int countPot1 = 0; //variable for MCP4161 dig pot value
int countPot2 = 0; //variable for MCP4131 dig pot value
int countDown1 = 0; //variable to control counting up and down for dig pot 1
int countDown2 = 0; //variable to control counting up and down for dig pot 2

void setup() {
  pinMode(6, OUTPUT);   //Set PWM pin to output 
  pinMode(10, OUTPUT);   //This pin controls SPI comm with dig pot 1
  pinMode(3, OUTPUT);   //This pin controls SPI comm with dig pot 2
  SPI.begin(); //Starts SPI communication
  //analogWrite(6, 100); //Set pin 6 to PWM at 39 percent duty cycle
}

void loop() {
  writeToDigPot1(countPot1); //write resistance setting to dig pot 1
  //writeToDigPot2(countPot2); //write resistance setting to dig pot 2

  countPot1=1;
//  if( countPot1>255 )
//    countPot1 = 0;
/*
 if(!countDown1 & countPot1 < 255) { //If counting up and below 256 
   countPot1++; //up the resistance setting by 1
 }
 else { //time to count down now
  if(countPot1 > 0) { //if resistor setting is above 0
    countPot1--; //reduce resistor value
    countDown1 = 1; //remain in countdown mode
  } 
  else { //switch back to count up mode
    countPot1++; //up the resistance setting by 1
    countDown1 = 0; //set to count up mode
  }
 }

 if(!countDown2 & countPot2 < 70) { //If counting up and below 70
  countPot2++; //up the resistance setting by 1
 }
 else { //time to count down now
  if(countPot2 > 0) { //if resistor setting is above 0
    countPot2--; //reduce resistor value
    countDown2 = 1; //remain in countdown mode
  } 
  else { //switch back to count up mode
    countPot2++; //up the resistance setting by 1
    countDown2 = 0; //set to count up mode
  }
 }
*/ 
  delay(10);
}

//This function handles the SPI communication to change resistor setting to dig pot 1
//input argument is resistance setting
void writeToDigPot1(int val) {
  digitalWrite(10, LOW);   //enable SPI comm to dig pot one
  digitalWrite(3, HIGH);  //disable SPI comm to dig pot 2
  delay(1); //short delay to ensure dig pins changed state
  SPI.transfer(vWrite); //status register set to write
  SPI.transfer(val); //write resistance value to dig pot
  digitalWrite(10, HIGH);   //enable SPI comm to dig pot one
}

//This function handles the SPI communication to change resistor setting to dig pot 2
//input argument is resistance setting
void writeToDigPot2(int val) {
  digitalWrite(3, LOW);   //enable SPI comm to dig pot 2
  digitalWrite(2, HIGH);  //disable SPI comm to dig pot 1
  delay(1); //short delay to ensure dig pins changed state
  SPI.transfer(vWrite); //status register set to write
  SPI.transfer(val); //write resistance value to dig pot
}

//This function handles the SPI communication to set dig pot 1 value in non-volatile memory
//input argument is resistance setting
void writeDigPot1NV(int val) {
  digitalWrite(2, LOW);   //enable SPI comm to dig pot one
  digitalWrite(3, HIGH);  //disable SPI comm to dig pot 2
  delay(1); //short delay to ensure dig pins changed state
  SPI.transfer(nVolatile); //status register set to non-volatile write
  SPI.transfer(val); //write resistance value to dig pot
}
