#define OUTPUT__BAUD_RATE 9600

void setup()
{
   Serial.begin(OUTPUT__BAUD_RATE);
}

int count1 = 0x30;
int timestamp = 0;
int timestamp_old = 0;

void loop()
{
  // Time to read the sensors again?
  if((millis() - timestamp) >= 100)
  {
    timestamp_old = timestamp;
    timestamp = millis();

    Serial.print("!Data: ");
    Serial.print(count1++);
    Serial.print(",");
    Serial.print(count1++);
    Serial.print(",");
    Serial.print(count1++);
    Serial.print(",");
    Serial.print(count1++);
    Serial.print(",");
    Serial.print(count1++);
    Serial.print(",");
    Serial.println(count1++);
    if( count1> 0x80 )
      count1 = 0x30;
  }
}
