// Serial port를 통해서 컴퓨터의 명령어를 받아서 이에 반응하는 프로그램

int count=0;
int count1=0;
unsigned long timestamp;
unsigned long timestamp_old;

// Blocks until another byte is available on serial port
char readChar()
{
  while (Serial.available() < 1) { } // Block
  return Serial.read();
}

void setup()
{
  Serial.begin(9600);
}
  
void loop()
{
  // Read incoming control messages
  if (Serial.available() >= 2)
  {
    if (Serial.read() == '#') // Start of new control message
    {
      int command = Serial.read(); // Commands
      if (command == 'i') // request one output _f_rame
          count++;         
      else if (command == 'd') // _s_ynch request
          count--;
    }
  }
  // Time to read the sensors again?
  if((millis() - timestamp) >= 100)
  {
    timestamp_old = timestamp;
    timestamp = millis();

    Serial.print("Count1 = ");
    Serial.print(count1++);
    Serial.print(",  Count = ");
    Serial.println(count);
  }
}
