#include <Arduino.h>

#define SW_A	2

void setup()
{
  pinMode(SW_A, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop()
{
  if( digitalRead(SW_A) )
    digitalWrite(13, 1);
  else
    digitalWrite(13, 0);
  
  delay(100);   
}