#include <SPI.h>
const int csPin = 10; //Slave Selected
void setup()
{
        Serial.begin(9600);
        Serial.println("ready");
        Serial.println();
  SPI.begin();
  pinMode(csPin,OUTPUT);
  digitalWrite(csPin, HIGH);
}
void loop() 
{
 for(int i=0; i<256; i++) 
 {
   Serial.println("R_WB : ");
   Serial.println(i);
//   if(i%10==0){delay(5000);}
   digitalPotWrite(i);
   delay(10);
 }
        
}
void digitalPotWrite(int value)
{
  digitalWrite(csPin, LOW); //select slave
//  SPI.transfer(0);
  SPI.transfer(value);
  digitalWrite(csPin, HIGH); //de-select slave
}

