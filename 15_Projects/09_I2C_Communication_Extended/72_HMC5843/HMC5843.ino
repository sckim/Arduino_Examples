/* Hardware version - v13
	
	ATMega328@3.3V w/ external 8MHz resonator
	High Fuse DA
  Low Fuse FF
	
	HMC5843: Magnetometer
*/

#include <Wire.h>

#define STATUS_LED 13 
#define GRAVITY 248  //this equivalent to 1G in the raw data coming from the accelerometer 
#define Switch  5  
//#define cDelay  19900
//#define cDelay  19900/4
#define cDelay  100

int ACC[3];          //array that store the accelerometers data
int SENSOR_SIGN[9] = {-1,1,1,-1,1,1,-1,-1,-1};  //Correct directions x,y,z - gyros, accels, magnetormeter
long int index=0;
int  toggle=0;

long timer=0;   //general purpuse timer
long timer_old;

/* global variable for text of 9 DOF data */
int accel_x;
int accel_y;
int accel_z;
int magnetom_x;
int magnetom_y;
int magnetom_z;
int gyro_x;
int gyro_y;
int gyro_z;

/* global variable for binary of 9 DOF data */
byte Accel[6];
byte Gyro[6];
byte Magneto[6];
byte Button_pressed[2];

void setup()
{ 
  int temp;
	
  Serial.begin(9600);
  pinMode (STATUS_LED,OUTPUT);  // Status LED

  digitalWrite(STATUS_LED,HIGH);
  I2C_Init();
  Compass_Init();

  digitalWrite(STATUS_LED,LOW);
  delay(1000);
   
  digitalWrite(STATUS_LED, 1);

  Button_pressed[1] = 0;
  Button_pressed[0] = digitalRead(Switch);
  digitalWrite(STATUS_LED, 0);
}

void loop() //Main Loop
{
  if((millis()-timer)>=cDelay)  // Main loop runs at 50Hz
  {
    timer_old = timer;
    timer=millis();

    // Data adquisition
    Read_Compass();
//    Mouse.move(-gyro_x/100,0);
//    Mouse.move(0,-gyro_y/100);
    Button_pressed[0] = digitalRead(Switch);

    printdata();
    digitalWrite(STATUS_LED, toggle^=1);   
    index++;
  }
}
