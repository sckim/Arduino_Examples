/* ******************************************************* */
/* I2C code for ADXL345 accelerometer                      */
/* and HMC5843 magnetometer                                */
/* ******************************************************* */

//This is a list of registers in the ITG-3200. Registers are parameters that determine how the sensor will behave, or they can hold data that represent the
//sensors current status.
//To learn more about the registers on the ITG-3200, download and read the datasheet.
char WHO_AM_I = 0x00;
char SMPLRT_DIV= 0x15;
char DLPF_FS = 0x16;
char GYRO_XOUT_H = 0x1D;
char GYRO_XOUT_L = 0x1E;
char GYRO_YOUT_H = 0x1F;
char GYRO_YOUT_L = 0x20;
char GYRO_ZOUT_H = 0x21;
char GYRO_ZOUT_L = 0x22;

//This is a list of settings that can be loaded into the registers.
//DLPF, Full Scale Register Bits
//FS_SEL must be set to 3 for proper operation
//Set DLPF_CFG to 3 for 1kHz Fint and 42 Hz Low Pass Filter
char DLPF_CFG_0 = 1<<0;
char DLPF_CFG_1 = 1<<1;
char DLPF_CFG_2 = 1<<2;
char DLPF_FS_SEL_0 = 1<<3;
char DLPF_FS_SEL_1 = 1<<4;

//I2C devices each have an address. The address is defined in the datasheet for the device. The ITG-3200 breakout board can have different address depending on how
//the jumper on top of the board is configured. By default, the jumper is connected to the VDD pin. When the jumper is connected to the VDD pin the I2C address
//is 0x69.

// ADXL345 Sensitivity(from datasheet) => 4mg/LSB   1G => 1000mg/4mg = 256 steps
// Tested value : 248
#define GRAVITY 248  //this equivalent to 1G in the raw data coming from the accelerometer 
#define Accel_Scale(x) x*(GRAVITY/9.81)//Scaling the raw data of the accel to actual acceleration in meters for seconds square

int AccelAddress = 0x53;
int CompassAddress = 0x1E;  //0x3C //0x3D;  //(0x42>>1);
int GyroAddress = 0x68;

void I2C_Init()
{
  Wire.begin();
}

void Accel_Init()
{
  Wire.beginTransmission(AccelAddress);
  Wire.send(0x2D);  // power register
  Wire.send(0x08);  // measurement mode
  Wire.endTransmission();
  delay(5);
  Wire.beginTransmission(AccelAddress);
  Wire.send(0x31);  // Data format register
  Wire.send(0x08);  // set to full resolution
  Wire.endTransmission();
  delay(5);	
  // Because our main loop runs at 50Hz we adjust the output data rate to 50Hz (25Hz bandwidth)
  Wire.beginTransmission(AccelAddress);
  Wire.send(0x2C);  // Rate
  Wire.send(0x09);  // set to 50Hz, normal operation
  Wire.endTransmission();
  delay(5);
}

// Reads x,y and z accelerometer registers
void Read_Accel()
{
  int i = 0;
  byte buff[6];
  
  Wire.beginTransmission(AccelAddress); 
  Wire.send(0x32);        //sends address to read from
  Wire.endTransmission(); //end transmission
  
  Wire.beginTransmission(AccelAddress); //start transmission to device
  Wire.requestFrom(AccelAddress, 6);    // request 6 bytes from device
  
  while(Wire.available())   // ((Wire.available())&&(i<6))
  { 
    buff[i] = Wire.receive();  // receive one byte
    i++;
  }
  Wire.endTransmission(); //end transmission
  
  if (i==6)  // All bytes received?
    {
    ACC[1] = (((int)buff[1]) << 8) | buff[0];    // Y axis (internal sensor x axis)
    ACC[0] = (((int)buff[3]) << 8) | buff[2];    // X axis (internal sensor y axis)
    ACC[2] = (((int)buff[5]) << 8) | buff[4];    // Z axis
//    ACC[1] = Accel_Scale(ACC[1]);
//    ACC[0] = Accel_Scale(ACC[0]);
//    ACC[2] = Accel_Scale(ACC[2]);
//    accel_x = SENSOR_SIGN[3]*(ACC[0]-AN_OFFSET[3]);
//    accel_y = SENSOR_SIGN[4]*(ACC[1]-AN_OFFSET[4]);
//    accel_z = SENSOR_SIGN[5]*(ACC[2]-AN_OFFSET[5]);
    
    accel_x = SENSOR_SIGN[0]*ACC[1];    //256 is 1g
    accel_y = SENSOR_SIGN[1]*ACC[0];
    accel_z = SENSOR_SIGN[2]*ACC[2];

    }
  else
    Serial.println("!ERR: Acc data");
}

void Compass_Init()
{
  Wire.beginTransmission(CompassAddress);
  Wire.send(0x02); 
  Wire.send(0x00);   // Set continouos mode (default to 10Hz)
  Wire.endTransmission(); //end transmission
}

void Read_Compass()
{
  int i = 0;
  byte buff[6];
 
  Wire.beginTransmission(CompassAddress); 
  Wire.send(0x03);        //sends address to read from
  Wire.endTransmission(); //end transmission
  
  //Wire.beginTransmission(CompassAddress); 
  Wire.requestFrom(CompassAddress, 6);    // request 6 bytes from device
  while(Wire.available())   // ((Wire.available())&&(i<6))
  { 
    buff[i] = Wire.receive();  // receive one byte
    i++;
  }
  Wire.endTransmission(); //end transmission
  
  if (i==6)  // All bytes received?
    {
    // MSB byte first, then LSB, X,Y,Z
    magnetom_x = SENSOR_SIGN[6]*((((int)buff[2]) << 8) | buff[3]);    // X axis (internal sensor y axis)
    magnetom_y = SENSOR_SIGN[7]*((((int)buff[0]) << 8) | buff[1]);    // Y axis (internal sensor x axis)
    magnetom_z = SENSOR_SIGN[8]*((((int)buff[4]) << 8) | buff[5]);    // Z axis
    }
  else
    Serial.println("!ERR: Mag data");
}

		//This function will write a value to a register on the itg-3200.
//Parameters:
//  char address: The I2C address of the sensor. For the ITG-3200 breakout the address is 0x69.
//  char registerAddress: The address of the register on the sensor that should be written to.
//  char data: The value to be written to the specified register.
void itgWrite(char address, char registerAddress, char data)
{
  //Initiate a communication sequence with the desired i2c device
  Wire.beginTransmission(address);
  //Tell the I2C address which register we are writing to
  Wire.send(registerAddress);
  //Send the value to write to the specified register
  Wire.send(data);
  //End the communication sequence
  Wire.endTransmission();
}

//This function will read the data from a specified register on the ITG-3200 and return the value.
//Parameters:
//  char address: The I2C address of the sensor. For the ITG-3200 breakout the address is 0x69.
//  char registerAddress: The address of the register on the sensor that should be read
//Return:
//  unsigned char: The value currently residing in the specified register
unsigned char itgRead(char address, char registerAddress)
{
  //This variable will hold the contents read from the i2c device.
  unsigned char data=0;
  
  //Send the register address to be read.
  Wire.beginTransmission(address);
  //Send the Register Address
  Wire.send(registerAddress);
  //End the communication sequence.
  Wire.endTransmission();
  
  //Ask the I2C device for data
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 1);
  
  //Wait for a response from the I2C device
  if(Wire.available()){
    //Save the data sent from the I2C device
    data = Wire.receive();
  }
  
  //End the communication sequence.
  Wire.endTransmission();
  
  //Return the data read during the operation
  return data;
}

//This function is used to read the X-Axis rate of the gyroscope. The function returns the ADC value from the Gyroscope
//NOTE: This value is NOT in degrees per second. 
//Usage: int xRate = readX();
int readX(void)
{
  int data=0;
  data = itgRead(GyroAddress, GYRO_XOUT_H)<<8;
  data |= itgRead(GyroAddress, GYRO_XOUT_L);  
  
  return data;
}

//This function is used to read the Y-Axis rate of the gyroscope. The function returns the ADC value from the Gyroscope
//NOTE: This value is NOT in degrees per second. 
//Usage: int yRate = readY();
int readY(void)
{
  int data=0;
  data = itgRead(GyroAddress, GYRO_YOUT_H)<<8;
  data |= itgRead(GyroAddress, GYRO_YOUT_L);  
  
  return data;
}

//This function is used to read the Z-Axis rate of the gyroscope. The function returns the ADC value from the Gyroscope
//NOTE: This value is NOT in degrees per second. 
//Usage: int zRate = readZ();
int readZ(void)
{
  int data=0;
  data = itgRead(GyroAddress, GYRO_ZOUT_H)<<8;
  data |= itgRead(GyroAddress, GYRO_ZOUT_L);  
  
  return data;
}

void Gyro_Init()
{
/*
  Wire.beginTransmission(GyroAddress);
  Wire.send(0x3E); 
  Wire.send(0x80);
  Wire.endTransmission(); //end transmission
  delay(10);
  
  //  itgWrite(itgAddress, DLPF_FS, (DLPF_FS_SEL_0|DLPF_FS_SEL_1|DLPF_CFG_0));
  Wire.beginTransmission(GyroAddress);
  Wire.send(DLPF_FS); 
  Wire.send(DLPF_FS_SEL_0 | DLPF_FS_SEL_1 | DLPF_CFG_0);   // Set continouos mode (default to 10Hz)
  Wire.endTransmission(); //end transmission
  delay(10);
  
  Wire.beginTransmission(0xD1);
  Wire.send(0x3E); 
  Wire.send(0x00);
  Wire.endTransmission(); //end transmission
  delay(10);
  */
  itgRead(GyroAddress, 0x00);  
   //Configure the gyroscope
  //Set the gyroscope scale for the outputs to +/-2000 degrees per second
  itgWrite(GyroAddress, DLPF_FS, (DLPF_FS_SEL_0|DLPF_FS_SEL_1|DLPF_CFG_0));
  //Set the sample rate to 100 hz
  itgWrite(GyroAddress, SMPLRT_DIV, 9);
}

void Read_Gyro()
{

  gyro_x = SENSOR_SIGN[3]*readX();
  gyro_y = SENSOR_SIGN[4]*readY();
  gyro_z = SENSOR_SIGN[5]*readZ();
/*
  int i = 0;
  byte buff[6];
 
  Wire.beginTransmission(GyroAddress); 
  Wire.send(GYRO_XOUT_H);        //sends address to read from
  Wire.endTransmission(); //end transmission
  
  Wire.beginTransmission(GyroAddress); 
  Wire.requestFrom(GyroAddress, 6);    // request 6 bytes from device
  while(Wire.available())   // ((Wire.available())&&(i<6))
  { 
    buff[i] = Wire.receive();  // receive one byte
    i++;
  }
  Wire.endTransmission(); //end transmission
  
  if (i==6)  // All bytes received?
    {
    // MSB byte first, then LSB, X,Y,Z
    gyro_x = SENSOR_SIGN[0]*((((int)buff[2]) << 8) | buff[3]);    // X axis (internal sensor y axis)
    gyro_y = SENSOR_SIGN[1]*((((int)buff[0]) << 8) | buff[1]);    // Y axis (internal sensor x axis)
    gyro_z = SENSOR_SIGN[2]*((((int)buff[4]) << 8) | buff[5]);    // Z axis
    }
  else
    Serial.println("!ERR: Gyro data");   
*/
}
