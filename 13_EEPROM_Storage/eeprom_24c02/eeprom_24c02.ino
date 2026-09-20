#include <Wire.h>

#define device 0x50  // Address with three address pins grounded. 

void setup() {
 Wire.begin();
 Serial.begin(9600);
 delay(500);
 byte data, wordaddress;
 data = 0x01;
 wordaddress = 0x01;
 byte index;

 //write 5 bytes to the device in nice order
 for(index=0x01;index<=5;index++){
   showWrite(data,wordaddress);
   deviceWrite(data,wordaddress);
   wordaddress++;
   data++;
   delay(1500);
   };

 delay(3000);

 //read them back
 wordaddress = 0x01;
 for(index=0x01;index<=5;index++){
   data  = deviceRead(wordaddress);
   showRead(data,wordaddress);
   delay(1500);
   wordaddress++;
   };
 delay(3000);  

}//end setup

void showRead(byte data, byte wordaddress){
 Serial.print("Read data: ");
 Serial.print(data,HEX);
 Serial.print(" from: ");
 Serial.println(wordaddress,HEX);
}

void showWrite(byte data, byte wordaddress){
 Serial.print("Write data: ");
 Serial.print(data,HEX);
 Serial.print(" to: ");
 Serial.println(wordaddress,HEX);
}

void deviceWrite(byte data, byte wordaddress) {
 Wire.beginTransmission(device);
 Wire.send(wordaddress);
 Wire.send(data);
 Wire.endTransmission(); 
}

byte deviceRead(byte wordaddress) {
 byte result;
 Wire.beginTransmission(device);
 Wire.send(wordaddress);
 Wire.requestFrom(device, 1);
 if(Wire.available()) {
   result = Wire.receive();
 }
 Wire.endTransmission();
 return result;
}

void loop() {
}
