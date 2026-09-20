#include "Arduino.h"
#include <LedKeypad.h>
#include <EEPROM.h>
#define cPEMF_PORT 13
// When final output is Non_inverting, Active_High (IRF730�� ���)
// otherwise, Active_low (IRF730�� IRFP240�� ����� ��)
#define cActive_High  1
#define cPulseWidth   125    //us
unsigned char repetition = 20;
char brightness = 0;
unsigned char running = 0;
unsigned char VoltageIndex = 0;
unsigned char FrequencyIndex = 0;
int DELAY;
//Intensity
unsigned char Voltage[6] = { 5, 10, 15, 20, 25, 30 };
//frequency
unsigned char Frequency[6] = { 0, 30, 40, 60, 75, 100 };
// 30Hz 28333
// 40Hz 20000
// 50Hz 15000
// 60Hz 11667
// 75Hz 8333
// 100Hz 5000
// one pulse = 250us, repetition=20
// 250us * repetition = 5msec
// 30Hz, 1/30 = 33.333ms 33.333-5 = 28333
// 0 30 40 50 60 100
unsigned int interval[6] = { 0, 28333, 20000, 11667, 8333, 5000 };
void load_data(void) {
  FrequencyIndex = EEPROM.read(0);
  //repetition = EEPROM.read(1);
  VoltageIndex = EEPROM.read(2);
}
void save_data(void) {
  EEPROM.write(0, FrequencyIndex);
  //EEPROM.write(1, repetition);
  EEPROM.write(2, VoltageIndex);
}
//The setup function is called once at startup of the sketch
void setup() {
  load_data();
  ledkeypad.begin(); /*Enable*/
  ledkeypad.setBrightness(2);/*Sets the brightness level*/
  //ledkeypad.display(Voltage[VoltageIndex] * 100 + Frequency[FrequencyIndex]); //Display character for testing
  ledkeypad.display(Frequency[FrequencyIndex]);
  pinMode(cPEMF_PORT, OUTPUT);
  digitalWrite(cPEMF_PORT, LOW);

  running=1;
}
// The loop function is called in an endless loop
void loop() {
  unsigned char keyValue = 0;
  keyValue = ledkeypad.getKey();/*Get key value*/
  switch (keyValue) {
  case KEY_DOWN:
  case KEY_LEFT:
    VoltageIndex++;
    if (VoltageIndex > 5)
      VoltageIndex = 0;
    //ledkeypad.display(Voltage[VoltageIndex] * 100 + Frequency[FrequencyIndex]); //Display character for testing
    ledkeypad.display(Frequency[FrequencyIndex]);
    break;
  case KEY_UP:
  case KEY_RIGHT:
    FrequencyIndex++;
    if (FrequencyIndex > 5)
      FrequencyIndex = 0;
    //ledkeypad.display(Voltage[VoltageIndex] * 100 + Frequency[FrequencyIndex]); //Display character for testing
    ledkeypad.display(Frequency[FrequencyIndex]);
    break;
  case KEY_SELECT:
    running ^= 1;
    if (running)
      ledkeypad.dotShow(3);
    else
      ledkeypad.dotVanish(3);
    break;
  default:
    break;
  }
  if (running == 1) {
    save_data();
    while (1) {
      GenPEMF(DELAY);
    }
  }
}
/* ************* GENERATION ********** */
void GenPEMF(int DELAY) {
#ifdef cActive_High
  if (FrequencyIndex == 0)
    digitalWrite(cPEMF_PORT, HIGH);
  else {
    for (int i = 0; i < repetition; i++) {
      PORTB |= 0x20;
      //digitalWrite(generate,HIGH);
      delayMicroseconds(cPulseWidth);
      PORTB &= ~0X20;
      //digitalWrite(generate,LOW);
      delayMicroseconds(cPulseWidth);
    }
    //delayMicroseconds(1000000);
    if (FrequencyIndex >= 3)
      delayMicroseconds(interval[FrequencyIndex] - cPulseWidth);
    else
      delay(interval[FrequencyIndex] / 1000);
  }
#else
  if(FrequencyIndex==0)
  digitalWrite(cPEMF_PORT,LOW);
  else {
    for(int i=0;i<repetition;i++)
    {
      PORTB &= ~0X20;
      //digitalWrite(generate,HIGH);
      delayMicroseconds(125);
      PORTB |= 0x20;
      //digitalWrite(generate,LOW);
      delayMicroseconds(125);
    }
    delayMicroseconds(DELAY);
  }
#endif
}

