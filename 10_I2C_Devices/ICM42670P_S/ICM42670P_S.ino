// --------------------------------------
// i2c_scanner
//
// Modified from https://playground.arduino.cc/Main/I2cScanner/
// --------------------------------------

#include <Wire.h>

typedef struct
{
	int16_t accel_x; /*!< Accelerometer X axis */
	int16_t accel_y; /*!< Accelerometer Y axis */
	int16_t accel_z; /*!< Accelerometer Z axis */
	int16_t gyro_x;	 /*!< Gyroscope X axis */
	int16_t gyro_y;	 /*!< Gyroscope Y axis */
	int16_t gyro_z;	 /*!< Gyroscope Z axis */
	int16_t temp;	 /*!< Temperature */
} icm42670_raw_t;

#include "inv_imu_defs.h"

#define ICM42670P_I2C_SPEED 1000000
#define ICM2670P_ADDRESS 0x69

#define get_real_temperature(raw) ((raw / 128.0) + 25.0)
#define get_real_accel(raw) (raw / 2048.0)
#define get_real_gyro(raw) (raw / 16.4)

static uint8_t readRegister8(uint8_t reg)
{
	Wire.beginTransmission(ICM2670P_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission(false);

	Wire.requestFrom(ICM2670P_ADDRESS, 1, true);
	if (Wire.available())
	{
		return (Wire.read());
	}

	return (0); // Fail
}

static void writeRegister8(uint8_t reg, uint8_t value)
{
	Wire.beginTransmission(ICM2670P_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission(true);
}

static uint8_t icm42670p_get_raw_data(icm42670_raw_t *raw_data)
{
	Wire.beginTransmission(ICM2670P_ADDRESS);
	Wire.write(0x09);
	Wire.endTransmission(false);

	Wire.requestFrom(ICM2670P_ADDRESS, 14, true);


	uint8_t data[14] = {0};
	for (uint8_t i = 0; i < 14; i++)
	{
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

static void icm42670p_init(void)
{
	writeRegister8(0x1F, 0x0F);
	// startAccel(ACCEL_CONFIG0_ODR_100_HZ, ACCEL_CONFIG0_FS_SEL_16g);
	// startGyro(GYRO_CONFIG0_ODR_100_HZ, GYRO_CONFIG0_FS_SEL_2000dps);
}

void setup() {
  Wire.begin();
  icm42670p_init();
  // startAccel(ACCEL_CONFIG0_ODR_100_HZ, ACCEL_CONFIG0_FS_SEL_16g);
	// startGyro(GYRO_CONFIG0_ODR_100_HZ, GYRO_CONFIG0_FS_SEL_2000dps);

  Serial.begin(115200);
  while (!Serial)
     delay(10);

	Serial.print("Who am I = ");
  Serial.println(readRegister8(0x75), HEX);
}


void loop() {

	icm42670p_get_raw_data(&imu_data);
  dispData(imu_data);

  delay(10);           // wait 5 seconds for next scan
}