#include <TimerOne.h>

#define pwmRegister OCR1A
const int  outPin = 9;

long period = 1;     // the period in microseconds
long pulseWidth = 0.5; // width of a pulse in microseconds

int prescale[] = {0,1,8,64,256,1024}; // range of prescale values

void setup()
{
 Serial.begin(9600);
 pinMode(outPin, OUTPUT);
 Timer1.initialize(period);  //initialize timer1, 1000 microsec
 setPulseWidth(pulseWidth);
}

void loop()
{
}

bool setPulseWidth(long microseconds)
{
 bool ret = false;
 
 int prescaleValue = prescale[Timer1.clockSelectBits];
 long precision = (F_CPU / 128000) * prescaleValue  ;
 period = precision * ICR1 / 1000;
 if( microseconds < period)
   {
     int duty = map(microseconds, 0, period, 0, 1024);
     if(duty < 1)
       duty = 1;
     if( microseconds > 0 && duty < RESOLUTION)
     {
       Timer1.pwm(outPin, duty);
       ret = true;
     }
   }
   return ret;
}
