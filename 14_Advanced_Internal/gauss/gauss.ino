// Read magnetic field density from gauss meter
// Disply the values on the LCD

#include <LiquidCrystal.h>
#define CH0  0
#define CH1  1
#define CH2  2
#define cBaudRate  57600
LiquidCrystal lcd(12,11,10,7,6,5,4);

double Sensor[3];
double Voltage[3];
double Gauss[3];
double Tesla[3];

void setup(void){ 
   lcd.begin(20,4); 
   pinMode(CH0,INPUT);
   pinMode(CH1,INPUT);
   pinMode(CH2,INPUT);
   Serial.begin(cBaudRate);
}

void loop(void)
{
  int i;

  for(i=0;i<3;i++)
  {
    Sensor[i]=analogRead(i);
  }
  Gauss[0]=(map(Sensor[0],18,66,71,218))/10.0;
  Gauss[1]=(map(Sensor[0],18,66,71,218))/10.0;
  Gauss[2]=(map(Sensor[2],17,73,71,218))/10.0;
      
  Serial.print("X = ");
  Serial.print(Gauss[0]);
  Serial.print(", Y = ");
  Serial.print(Gauss[1]);
  Serial.print(", Z = ");
  Serial.println(Gauss[2]);
  
  lcd.setCursor(0,0);
  lcd.print("Gauss : ");
  lcd.print(Gauss[0]);
  delay(50);
  lcd.clear();
}
