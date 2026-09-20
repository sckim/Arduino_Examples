

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "inv_imu_defs.h"

typedef struct
{
  int16_t accel_x; /*!< Accelerometer X axis */
  int16_t accel_y; /*!< Accelerometer Y axis */
  int16_t accel_z; /*!< Accelerometer Z axis */
  int16_t gyro_x;  /*!< Gyroscope X axis */
  int16_t gyro_y;  /*!< Gyroscope Y axis */
  int16_t gyro_z;  /*!< Gyroscope Z axis */
  int16_t temp;    /*!< Temperature */
} icm42670_raw_t;

typedef struct
{
  uint8_t EEG_State;
  uint16_t EEG_0[64];
  uint16_t EEG_1[64];
  uint16_t PPG[64];
  icm42670_raw_t imu[5];
  uint16_t HR;
  uint8_t SpO2;
  uint8_t VBAT;
} EEG_t;

EEG_t EEG_data;
EEG_t *pEEG_data = &EEG_data;

#define ICM42670P_I2C_SPEED 1000000
#define ICM2670P_ADDRESS 0x69

#define get_real_temperature(raw) ((raw / 128.0) + 25.0)
#define get_real_accel(raw) (raw / 2048.0)
#define get_real_gyro(raw) (raw / 16.4)

static uint8_t readRegister8(uint8_t reg) {
  Wire.beginTransmission(ICM2670P_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(ICM2670P_ADDRESS, 1, true);
  if (Wire.available()) {
    return (Wire.read());
  }

  return (0);  // Fail
}

static void writeRegister8(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(ICM2670P_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission(true);
}

static uint8_t icm42670p_get_raw_data(icm42670_raw_t *raw_data) {
  Wire.beginTransmission(ICM2670P_ADDRESS);
  Wire.write(0x09);
  Wire.endTransmission(false);

  Wire.requestFrom(ICM2670P_ADDRESS, 14, true);


  uint8_t data[14] = { 0 };
  for (uint8_t i = 0; i < 14; i++) {
    data[i] = Wire.read();
  }

  raw_data->temp = (int16_t)(data[0] << 8 | data[1]);
  raw_data->accel_x = (int16_t)(data[2] << 8 | data[3]);
  raw_data->accel_y = (int16_t)(data[4] << 8 | data[5]);
  raw_data->accel_z = (int16_t)(data[6] << 8 | data[7]);
  raw_data->gyro_x = (int16_t)(data[8] << 8 | data[9]);
  raw_data->gyro_y = (int16_t)(data[10] << 8 | data[11]);
  raw_data->gyro_z = (int16_t)(data[12] << 8 | data[13]);
  return true;
}

static void icm42670p_init(void) {
  writeRegister8(0x1F, 0x0F);
  // startAccel(ACCEL_CONFIG0_ODR_100_HZ, ACCEL_CONFIG0_FS_SEL_16g);
  // startGyro(GYRO_CONFIG0_ODR_100_HZ, GYRO_CONFIG0_FS_SEL_2000dps);
}

void dispData(icm42670_raw_t data) {
  Serial.print(" ACC=(");
  Serial.print(get_real_accel(data.accel_x), 2);
  Serial.print(", ");
  Serial.print(get_real_accel(data.accel_y), 2);
  Serial.print(", ");
  Serial.print(get_real_accel(data.accel_z), 2);
  Serial.print("),  Gyro=(");
  Serial.print(get_real_gyro(data.gyro_x), 2);
  Serial.print(", ");
  Serial.print(get_real_gyro(data.gyro_y), 2);
  Serial.print(", ");
  Serial.print(get_real_gyro(data.gyro_z), 2);
  Serial.print("), Temp = ");
  Serial.print(get_real_temperature(data.temp), 1);

  // char str[80];

  // sprintf(str, " ACC f = (%3.2f, %3.2f, %3.2f), Gyro=(%3.2f, %3.2f, %3.2f), Temp = %3.2f\n\r",
  // 				get_real_accel(data.accel_x), get_real_accel(data.accel_y), get_real_accel(data.accel_z),
  // 				get_real_gyro(data.gyro_x), get_real_accel(data.gyro_y), get_real_accel(data.gyro_z),
  // 				get_real_temperature(data.temp));
  // Serial.print(str);
}

const byte RATE_SIZE = 4;  //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];     //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;  //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

icm42670_raw_t imu_data;
MAX30105 particleSensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  icm42670p_init();
  // startAccel(ACCEL_CONFIG0_ODR_100_HZ, ACCEL_CONFIG0_FS_SEL_16g);
  // startGyro(GYRO_CONFIG0_ODR_100_HZ, GYRO_CONFIG0_FS_SEL_2000dps);
  Serial.print("Who am I = ");
  Serial.println(readRegister8(0x75), HEX);

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))  //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1)
      ;
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup();                     //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);  //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0);   //Turn off Green LED
}

void loop() {
  unsigned long StartTime = millis();

  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true) {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;  //Store this reading in the array
      rateSpot %= RATE_SIZE;                     //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }
  icm42670p_get_raw_data(&imu_data);
  // /memcpy(pEEG_data, )

  if (1) {
    Serial.print("IR=");
    Serial.print(irValue);
    Serial.print(", BPM=");
    Serial.print(beatsPerMinute);
    Serial.print(", Avg BPM=");
    Serial.print(beatAvg);

    if (irValue < 50000)
      Serial.print(" No finger?");
    dispData(imu_data);
  }
  // Serial.println();
  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - StartTime;
  Serial.print("Estimation time = ");
  Serial.println(ElapsedTime);
}
