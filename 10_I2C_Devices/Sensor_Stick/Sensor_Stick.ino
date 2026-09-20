/* Hardware version - v13
	
	ATMega328@3.3V w/ external 8MHz resonator
	High Fuse DA
  Low Fuse FF
	
	ADXL345: Accelerometer
	HMC5843: Magnetometer
*/

#include <Wire.h>

#define STATUS_LED 13 
#define GRAVITY 248  //this equivalent to 1G in the raw data coming from the accelerometer 

#define Switch  5  
int ACC[3];          //array that store the accelerometers data
int SENSOR_SIGN[9] = {-1,1,1,-1,1,1,-1,-1,-1};  //Correct directions x,y,z - gyros, accels, magnetormeter

long timer=0;   //general purpuse timer
long timer_old;
unsigned int counter=0;

int accel_x;
int accel_y;
int accel_z;
int magnetom_x;
int magnetom_y;
int magnetom_z;
int gyro_x;
int gyro_y;
int gyro_z;

int  toggle = 0;

void setup()
{ 
  Serial.begin(9600);
  pinMode (STATUS_LED,OUTPUT);  // Status LED

  digitalWrite(STATUS_LED,HIGH);
  I2C_Init();
  Accel_Init();
  Read_Accel();

  // Magnetometer initialization
  Compass_Init();
  Gyro_Init();

  delay(2000);
  digitalWrite(STATUS_LED,LOW);
  delay(100);
  digitalWrite(STATUS_LED,HIGH);
    
  //Read_adc_raw();     // ADC initialization
  timer=millis();
  delay(20);
  counter=0;
  digitalWrite(STATUS_LED,LOW);
}

void loop() //Main Loop
{
  if((millis()-timer)>=20)  // Main loop runs at 50Hz
  {
    counter++;
    timer_old = timer;
    timer=millis();

    // Data adquisition
    Read_Accel();     // Read I2C accelerometer
    Read_Gyro();
//    nStatus = digitalRead(Switch);

    if (counter > 5)  // Read compass data at 10Hz... (5 loop runs)
      {
      counter=0;
      Read_Compass();    // Read I2C magnetometer
      }
    printdata();

    digitalWrite(STATUS_LED,toggle^=1);
  }
}
