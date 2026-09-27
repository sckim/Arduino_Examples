#include <Wire.h>
#include "MAX30105.h"

#define nPPG	50
#define nEEG	100

#define nSamplingRate	400
#define nSampleAverage	8    // 실제 샘플링 주파수는 400/8하여 50Hz가 된다.

long startTime;
long samplesTaken = 0; //Counter for calculating the Hz or read rate

MAX30105 particleSensor;

typedef struct {
	uint8_t EEG_State;
	uint32_t EEG[2][nEEG];  //24bits
	uint32_t PPG[nPPG];    // 18bits
	uint16_t ACC_X[5];
	uint16_t ACC_Y[5];
	uint16_t ACC_Z[5];
	uint16_t GYRO_X[5];
	uint16_t GYRO_Y[5];
	uint16_t GYRO_Z[5];
	uint16_t HR;
	uint8_t SpO2;
	uint8_t VBAT;
} EEG_t;

EEG_t EEGData;
EEG_t *pData = &EEGData;

void setup() {
	Serial.begin(115200);

	if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
		Serial.println(
				"MAX30105 was not found. Please check your wiring/power.");
		while (1)
			;
	}
	byte ledBrightness = 60; // 0 to 255
	byte sampleAverage = nSampleAverage;  // Options: 1, 2, 4, 8, 16, 32
	byte ledMode = 2; // Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
	int sampleRate = nSamplingRate;   // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
	int pulseWidth = 411;    // Options: 69, 118, 215, 411
	int adcRange = 4096;     // Options: 2048, 4096, 8192, 16384

	particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate,
			pulseWidth, adcRange);
	particleSensor.enableAFULL(); //Enable the almost full interrupt (default is 32 samples)
	particleSensor.setFIFOAlmostFull(3); //Set almost full int to fire at 29 samples

	Serial.println();
	Serial.print("EEG data size : ");
	Serial.println(sizeof(pData->EEG[0]));
	Serial.print("PPG buffer size : ");
	Serial.println(sizeof(pData->PPG));

	startTime = millis();
}

void dispData(uint32_t *data, uint8_t num) {
	for (uint8_t i = 0; i < num; i++) {
		Serial.println(data[i]);
		//Serial.print(", ");
	}
//	Serial.println();
}

uint32_t irRED;

void loop() {
	particleSensor.check(); //Check the sensor, read up to 3 samples
	while (particleSensor.available()) //do we have new data?
	{
		irRED = particleSensor.getFIFOIR();
		pData->PPG[samplesTaken++] = irRED;
		particleSensor.nextSample(); //We're finished with this sample so move to next sample
		if (samplesTaken >= nPPG) {
			dispData(pData->PPG, nPPG);
//			Serial.write((uint8_t *)pDdata, 512);
//			Serial.println(
//					(float) samplesTaken / ((millis() - startTime) / 1000.0),
//					2);
			startTime = millis();
			samplesTaken = 0;
		}
	}
}

