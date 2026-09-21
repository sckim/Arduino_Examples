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
#define cDelay  19900

int ACC[3];          //array that store the accelerometers data
int SENSOR_SIGN[9] = {-1,-1,1,1,1,1,-1,-1,-1};  //Correct directions x,y,z - gyros, accels, magnetormeter

int  toggle=0;

long timer=0;   //general purpuse timer
long now;

int accel_x;
int accel_y;
int accel_z;
int magnetom_x;
int magnetom_y;
int magnetom_z;
int gyro_x;
int gyro_y;
int gyro_z;

int Button_pressed;

void setup()
{ 
  int temp;
	
  Serial.begin(115200);
  pinMode (STATUS_LED,OUTPUT);  // Status LED

  digitalWrite(STATUS_LED,HIGH);
  I2C_Init();
  Accel_Init();
  Read_Accel();

  // Magnetometer initialization
  Compass_Init();
  Gyro_Init();

  digitalWrite(STATUS_LED,LOW);
  delay(1000);
    
  //Read_adc_raw();     // ADC initialization
  temp = 0;
  
  digitalWrite(STATUS_LED, 1);
  /*
  while (temp<10000)  {
    Read_Gyro();
    temp = gyro_x;
  }
*/
  Button_pressed = digitalRead(Switch);
  digitalWrite(STATUS_LED, 0);
  timer=micros();
}

void loop() //Main Loop
{
  now = micros();
  if( (now-timer)>=cDelay )  // Main loop runs at 50Hz
  {
    timer = now;
    // Data adquisition
    Read_Accel();     // Read I2C accelerometer
    Read_Gyro();
    Button_pressed = digitalRead(Switch);

    printdata();
   // digitalWrite(STATUS_LED, toggle^=1);
  }
}
