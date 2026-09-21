/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN, for Teensy 3.5  BUILTIN_SDCARD)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>

#define TimerInterval 15

File myFile;

String strFn = "LOG00298";
int Fileindex = 0;
char buffer[13];
signed int sensorValue=0;

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  pinMode(LED_BUILTIN , OUTPUT);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("\r\ninitialization done.");

  do{
    snprintf(buffer,sizeof(buffer), "LOG%05d.txt", Fileindex++);
    Serial.println(buffer);
  }while(SD.exists(buffer) );

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(buffer, FILE_WRITE);
 // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.write(0x30);
    myFile.write(0x31);
    myFile.write(0x33);
    myFile.write(0x35);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
    myFile = SD.open(buffer, FILE_WRITE);
}

unsigned char utemp;

void loop() {
  int i;
  // nothing happens after setup
  digitalWrite(LED_BUILTIN , HIGH);
  sensorValue = analogRead(0);

  //little endian code
  utemp =sensorValue&0xff;
  i = myFile.write(utemp);
//  Serial.println(i);
  //delayMicroseconds(100);
  utemp = sensorValue>>8;
  i = myFile.write(utemp);
  myFile.print("aaa");
//  Serial.println(i);
  if(!i) {
    Serial.println(i);
    digitalWrite(LED_BUILTIN , LOW);

    myFile.close();
    exit(0);
  }
    myFile.flush(); 
  digitalWrite(LED_BUILTIN , LOW);
  delayMicroseconds(250-TimerInterval);        // delay in between reads for stability}
}
