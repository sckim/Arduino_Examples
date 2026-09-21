/* AFE4300
 by: Soochan Kim
 date: April 20, 2016

 This example code shows how you could use the Arduino SPI
 library to interface with a AFE4300.

 Circuit:a
 UNO ICSP-------------- AFE4300 EVM (J103)
 5V   -------------------- VCC,
 GND  -------------------- GND, 4 or 10 or 18
 11   -------------------- MOSI, 11
 12   -------------------- MISO, 13
 13   -------------------- SCLK, 3
 10   -------------------- STE1, 1

 8   -------------------- RDY, 15
 3   -------------------- RESET_MCU,
 9  -------------------- CLK_MCU, 17, 1MHz from Function Gen
 */
#include <SPI.h> // Include the Arduino SPI library

#define cPrecision    6
#define cScale        1
#define cOffset       0.0
/***************************
 AFE4300 register address definitions
 ****************************/
#define ADC_DATA_RESULT         0x00
#define ADC_CONTROL_REGISTER1   0x01
/*
 ADC_CONV_MODE[15:15]
 This bit determines the operational status of the device. This bit can only be written when in the ADC power-down mode. When read the bit gives the status report of the conversion.

 For Write:
 0 = No effect (default)
 1 = Single shot conversion mode

 For Read status (only in single shot conversion mode)
 0 = Device is currently performing a conversion
 1 = Device is not currently performing a conversion

 This bit is used in conjunction with ADC_PDN (bit 7). Pls refer to the description of ADC_PD bit.
 --------------------
 ADC_MEAS_MODE[13:11]
 These bits set the ADC measurements to either be single ended or differential.
 000= AI1, AI2 (Differential, default)
 001= AI1, AVSS (Singe Ended)
 010= AI2, AVSS (Single Ended)
 --------------------
 RESERVED[8:8]
 NA
 --------------------
 ADC_PD[7:7]
 ADC Powerdown
 This bit powers down the ADC_PGA and the ADC.
 0 = Continuous conversion mode;
 1 = Shutdown mode (default);
 --------------------
 COMP_MODE[3:3]
 No description available.
 --------------------
 COMP_LATCH[2:2]
 No description available.
 --------------------
 COMP_QUE[1:0]
 No Description available.
 --------------------
 ADC_DATA_RATE[6:4]
 Conversion rate select bits.
 These bits select one of eight different conversion rates of the ADC. The data rates in the table assume a master clock of 1MHz.

 000= 8
 001= 16
 010= 32
 011= 64
 100= (default) 128
 101= 250
 110= 475
 111= 860
 */

#define ADC_CONV_MODE			1 << 15
#define ADC_MEAS_MODE			11
#define ADC_MEAS_Diff			0b000 << ADC_MEAS_MODE
#define ADC_MEAS_AI1			0b001 << ADC_MEAS_MODE
#define ADC_MEAS_AI2			0b010 << ADC_MEAS_MODE
#define ADC_ShutDown			1 << 7
#define ADC_DATA_RATE			4
#define ADC_DATA_RATE_8         0x00<<4   // bit 6:4
#define ADC_DATA_RATE_16        0x01<<4
#define ADC_DATA_RATE_32        0x02<<4
#define ADC_DATA_RATE_64        0x03<<4
#define ADC_DATA_RATE_128       0x04<<4
#define ADC_DATA_RATE_250       0x05<<4
#define ADC_DATA_RATE_475       0x06<<4
#define ADC_DATA_RATE_860       0x07<<4

#define MISC_REGISTER1          0x02
#define MISC_REGISTER2          0x03

#define DEVICE_CONTROL1        	0x09
/*
 DAC_PD[3:3]
 Powerdown DAC:
 This bit powers down the WS front end offset correction DAC and the BCM front end current source DAC.
 0: power up DAC (default)
 1: power down DAC.
 --------------------
 PDB[2:2]
 Chip power down:
 This bit in conjunction with other power down bits determines the powe state of the chip.
 0: Power down (default)
 1: Power up of front end.
 --------------------
 BCM_PDB[1:1]
 Body composition meter front end power down bit.
 0: Power down body composition front end (default)
 1: Power up body composition front end
 --------------------
 WS_PDB[0:0]
 Weigh scale front end power down bit .
 0: Power down weight scale front end (default)
 1: Power up weight scale front end.
 */
#define DAC_PD					3
#define Chip_PD					2
#define BCM_PDB					1		// Body composition meter front end power down bit.
#define WS_PDB					0			// Weigh scale front end power down bit

#define ISW_MUX		            0x0A
/*
 IOUTPx[15:10]
 These bits close the switches routing IOUTPx to the postive input of the I-V amplifier
 0 : Switch is open (default)
 1 : Switch is closed

 000001: Selects IOUT0
 000010: Selects IOUT1
 000100: Selects IOUT2
 001000: Selects IOUT3
 010000: Selects IOUT4
 100000: Selects IOUT5
 --------------------
 RPx[9:8]
 These bits close the switches routing the calibration signal to the postive input of the I-V amplifier
 0 : Switch is open (default)
 1 : Switch is closed

 01: Selects RP0
 10: Selects RP1
 --------------------
 IOUTNx[7:2]
 These bits close the switches routing IOUTPx to the negative input of the I-V amplifier
 0 : Switch is open (default)
 1 : Switch is closed

 000001: Selects IOUT0
 000010: Selects IOUT1
 000100: Selects IOUT2
 001000: Selects IOUT3
 010000: Selects IOUT4
 100000: Selects IOUT5
 --------------------
 RNx[1:0]
 These bits close the switches routing the calibration signal to the negative input of the I-V amplifier
 0 : Switch is open (default)
 1 : Switch is closed

 01: Selects RM0
 10: Selects RM1
 */
#define RN0						0
#define RN1						1
#define IOUT0					2
#define IOUT1					3
#define IOUT2					4
#define IOUT3					5
#define IOUT4					6
#define IOUT5					7

#define RP0						8
#define RP1						9

#define VSENSE_MUX              0x0B
/*
 VSENSEPx[15:10]
 These bits close the swtiches routing VSENSPx to the postive input of the receive amplifier
 0 : Switch is open (default)
 1 : Switch is closed

 000001: Selects VSENS0
 000010: Selects VSENS1
 000100: Selects VSENS2
 001000: Selects VSENS3
 010000: Selects VSENS4
 100000: Selects VSENS5
 --------------------
 VSENSERPx[9:8]
 These bits close the swtiches routing the calibration signal to the postive input of the receive amplifier
 0 : Switch is open (default)
 1 : Switch is closed

 01: Selects VSENSP_R0
 10: Selects VSENSP_R1
 --------------------
 VSENSENx[7:2]
 These bits close the switches routing VSENSNx to the negative input of the receive amplifier
 0 : Switch is open (default)
 1 : Switch is closed

 000001: Selects VSENS0
 000010: Selects VSENS1
 000100: Selects VSENS2
 001000: Selects VSENS3
 010000: Selects VSENS4
 100000: Selects VSENS5
 --------------------
 VSENSERNx[1:0]
 These bits close the switches routing the calibration signal to the negative input of the receive amplifier
 0 : Switch is open (default)
 1 : Switch is closed

 01: Selects VSENSM_R0
 10: Selects VSENSM_R1
 */

#define VSENSN_R0				0
#define VSENSN_R1				1
#define VSENS0					2
#define VSENS1					3
#define VSENS2					4
#define VSENS3					5
#define VSENS4					6
#define VSENS5					7

#define VSENSP_R0				8
#define VSENSP_R1				9

#define IQ_MODE_ENABLE          0x0C
/*
 IQ_MODE_ENABLE[11:11]
 Enable the I/Q demodulator
 0 : Full wave rectifier mode (default)
 1 : I/Q Demodulator mode

 This bit turns sets the impedece measurement mode to be either the full-wave rectifier mode or the I/Q demodulator mode. Appropriate bits needs to be set in the XXXXX register and the YYYY register to route the output of the impedance measurement block to the ADC. For the I/Q Demodulator mode the IQ_DEMOD_CLK bit and the IQ_DEMOD_CLK_DIV_FAC bits of the ZZZ register need to be set appropriately. Refer to the respective register section for more details.
 */
#define IQ_MODE_ENABLE_Bit		11

#define WEIGHT_SCALE_CONTROL    0x0D
/*
 WS_PGA_GAIN[14:13]
 Sets the second stage gain of weigh scale front end:
 00: Gain=1;(default)
 01: Gain=2;
 10: Gain=3;
 11: Gain=4;
 --------------------
 OFFSET_DAC_VALUE[5:0]
 Offset Correction DAC setting:
 These bits sets the value for the DAC used to correct the input offset of the weigh scale front end. The correction is done at the 2nd stage. The offset correction at the output of the first stage is given by OFFSET_DAC_VALUE*31.2mV. Notice that OFFSET_DAC_VALUE is a number from -32 to 31, in 2占쏙옙s complement. Default is all 占쏙옙0占쏙옙s.
 */
#define WS_Offset				0
#define WS_PGA_1				0 << 13
#define WS_PGA_2				1 << 13
#define WS_PGA_3				2 << 13
#define WS_PGA_4				3 << 13

#define BCM_DAC_FREQ            0x0E
/*
 DAC_FREQ[9:0]
 Sets the frequency of the BCM excitation current source
 The DAC output frequency is given by DAC<9:0> x fclk/1024, where fclk is the frequency of the device input clock (pin 79).

 For example, for fclk=1MHz:
 1. DAC=0x00FF -->  255 KHz.
 2. DAC=0x0001 -->  1 KHz.
 */
#define DEVICE_CONTROL2        	0x0F
/*
 IQ_DEMOD_CLK_DIV_FAC[13:11]
 Sets the I/Q Demodulator clock frequency
 The clock for the IQ demodulator (IQ_DEMOD_CLK signal) is internally generated from the device input clock(fclk) by a divider controlled by this register. Note that the IQ_DEMOD_CLK should be 4 times the BCM_DAC_FREQ, so, that it can generate the phases for the mixers. I.e., IQ_DEMOD_CLK = Fclk/(IQ_DEMOD_CLK_DIV_FAC) = BCM_DAC_FREQ * 4.

 000: div by 1 (default);
 001: div by 2;
 010: div by 4;
 011: div by 8;
 100: div by 16;
 Others: div by 32;
 --------------------
 BAT_MON_EN1[7:7]
 This bit along with BAT_MON_EN0 (Bit[0]) enables battery monitoring
 When disabled the battery monitoring block is powered down to save power.
 See the description of Bit[0]
 --------------------
 BRIDGE_SEL[2:1]
 Selects one of the 4 input pairs to be routed to the weigh scale front end.

 00:  bridge 1 (INP1, INM1) connected to the weigh scale front end (default)
 01:  bridge 2 (INP2, INM2) connected to the weigh scale front end
 10:  bridge 3 (INP3, INM3) connected to the weigh scale front end
 11:  bridge 4 (INP4, INM4) connected to the weigh scale front end.
 --------------------
 BAT_MON_EN0[0:0]
 This bit along with BAT_MON_EN1 (Bit[7]) enables battery monitoring
 [BAT_MON_EN1, BAT_MON_EN0]
 00: Monitor disabled (default)
 11: Monitor enabled (AVDD/3)
 */
#define ADC_CONTROL_REGISTER2  	0x10
/*
 ADC_REF_SEL[6:5]
 Selects the reference for the ADC
 00:  ADCREF connected to VLDO, and VREF- to GND. To be used for ratiometric weight scale  measurement. (default)
 01:  Unused
 10:  Unused
 11:  ADCREF connected to VREF (internal voltage reference generator). To be used for impedance measurement.
 --------------------
 PERIPHERAL_SEL[4:0]
 Peripheral select
 00000: Connect weight scale instrumentation amplifier outputs (outp/outm) to ADC mux inputs AI1/AI2.
 00011: Connect body composition meter outputs OUTP_FILT/OUTM_FILT to ADC mux inputs AI1/AI2.
 00101: Connect body composition meter outputs OUTP_Q_FILT/OUTM_Q_FILT to ADC mux inputs AI1/AI2.
 01001: Connect AAUX1 to ADC mux input AI1. ADC mux input AI2 is unknown (floating).. Choose appropriate option in ADC_INPUT_MUX_SEL<3:0> = 0100 or 1001 to convert AI1 with respect to GND.
 10001: Connect AAUX2 to ADC mux input AI2. ADC mux input AI1 is unknown (floating). Choose appropriate option in ADC_INPUT_MUX_SEL<3:0> = 0101 or 1010 to convert AI2 with respect to GND.
 11001: Connect AAUX1 to ADC mux input AI1 and AAUX2 to ADC mux input AI2.
 */
#define ADC_REF_WS			0
#define ADC_REF_Internal	3 <<5

#define MISC_REGISTER3          0x1A

//#define Debug 1
#define cMaxChannels		6

// Define the SS pin
//  This is the only pin we can move around to any available
//  digital pin.
const int ssPin = 10; // output
const int ReadyPin = 8; //input
const int ResetMcuPin = 3;

// Scaling
const float y1 = 700;   // RN0 ~ RP1
const float y2 = 952;   // RN1 ~ RP1
const float x1 = 0.48045;
const float x2 = 0.65104;

int buffer[20];

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimalsSPI(byte decimals) {
	digitalWrite(ssPin, LOW);
	SPI.transfer(0x77);
	SPI.transfer(decimals);
	digitalWrite(ssPin, HIGH);
}

int GetRegisterValue(unsigned char address) {
	int intTemp;

	intTemp = readRegister(address);
	//writeRegister(address, intTemp);

	return intTemp;
}

// write 3 bytes
// address MSB-byte LSB-byte
void writeRegister(unsigned char address, unsigned int data) {
	digitalWrite(ssPin, LOW);

	unsigned char firstByte = (unsigned char) (data >> 8);
	unsigned char secondByte = (unsigned char) data;

	SPI.transfer(address);
	//Send 2 bytes to be written
	SPI.transfer(firstByte);
	SPI.transfer(secondByte);

	//SPI.transfer(firstByte,SPI_CONTINUE);
	//SPI.transfer(secondByte,SPI_LAST);

	digitalWrite(ssPin, HIGH);
}

int readRegister(unsigned char address) {
	int spiReceive = 0;
	unsigned char spiReceiveFirst = 0;
	unsigned char spiReceiveSecond = 0;
	address = address & 0x1F; //Last 5 bits specify address
	address = address | 0x20; //First 3 bits need to be 001 for read opcode

	digitalWrite(ssPin, LOW);
	SPI.transfer(address);
	spiReceiveFirst = SPI.transfer(0x00);
	spiReceiveSecond = SPI.transfer(0x00);
	digitalWrite(ssPin, HIGH);

	//Combine the two received bytes into a signed int
	spiReceive = (spiReceiveFirst << 8);
	spiReceive |= spiReceiveSecond;
	return spiReceive;
}

void Reset_AFE4300(void) {
	digitalWrite(ResetMcuPin, LOW);
	delay(1); //0.7ms
	digitalWrite(ResetMcuPin, HIGH);
}

void SetBCM_DAC_Freq(int freq) {
	// DAC[8:0] * fclk / 1024;
	writeRegister(BCM_DAC_FREQ, freq);
	delay(1);
#ifdef Debug
	Serial.print("BCM_DAC_FREQ :");
	Serial.println(BCM_DAC_FREQ, HEX);
	Serial.println(freq, HEX);
#endif
}

void Calibrate(void) {
	int temp;

#ifdef Debug
	Serial.println("Calibration Start");
#endif

	writeRegister(DEVICE_CONTROL1, 0x0006);
	delay(1);

	writeRegister(ADC_CONTROL_REGISTER1, 0x4130);
	delay(1);

	writeRegister(IQ_MODE_ENABLE, 0x0000);
	delay(1);

	writeRegister(VSENSE_MUX, 0x0201);	//VSENSEP_R1, VSENSEM_R0
	delay(1);

	writeRegister(ISW_MUX, 0x0201);		//RP1, RN0
	delay(1);

	writeRegister(MISC_REGISTER1, 0x0000);	//must by manual
	delay(1);

	writeRegister(MISC_REGISTER2, 0xffff);	//must by manual
	delay(1);

	writeRegister(ADC_CONTROL_REGISTER2, 0x0063);
	delay(1);

	SetBCM_DAC_Freq(50);	//50kHz

	delay(500);
	for (int i = 0; i < 40; i++) {
		while (digitalRead(ReadyPin) > 0)
			;
		delay(1);
		temp = ReadImpedanceValue();
		Serial.println(temp);
	}
	delay(1000);

	writeRegister(VSENSE_MUX, 0x0202);	//VSENSEP_R1, VSENSEM_R1
	delay(1);

	writeRegister(ISW_MUX, 0x0202);		// RP1, RN1
	delay(1);

	SetBCM_DAC_Freq(0x0032);		//50kHz

	delay(500);
	for (int i = 0; i < 40; i++) {
		while (digitalRead(ReadyPin) > 0)
			;
		temp = ReadImpedanceValue();
		Serial.println(temp);
	}
	delay(1000);

#ifdef Debug
	Serial.println("Calibration has done.");
#endif
}

// MCU占쏙옙 Reset占싹곤옙, 占쏙옙占쏙옙占쏙옙 占쏙옙占승몌옙 占싻억옙 占승댐옙.
// 占쏙옙占쏙옙 占쏙옙占쏙옙占싹댐옙 占쏙옙占쏙옙占� 占쏙옙占쏙옙.
void AFE4300_Reset(void) {
	int intTemp;

	Reset_AFE4300();

	intTemp = GetRegisterValue(0x00);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x01);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x02);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x03);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x09);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x0a);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x0b);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x0c);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x0d);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x0e);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x0f);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x10);
	Serial.println(intTemp, HEX);

	intTemp = GetRegisterValue(0x1a);
	Serial.println(intTemp, HEX);
}

void SetADC_SamplingRate(int intTemp) {

	// 0x4100 : A1 A2 = differential
	// 0x4900 : A1, AVSS = single-ended
	// 0x5100 : A2, AVSS = single-ended  <= EVM
	unsigned int uintTemp = 0x5100;

	switch (intTemp) {
	case 8:
		uintTemp |= ADC_DATA_RATE_8;
		break;
	case 16:
		uintTemp |= ADC_DATA_RATE_16;
		break;
	case 32:
		uintTemp |= ADC_DATA_RATE_32;
		break;
	case 64:
		uintTemp |= ADC_DATA_RATE_64;
		break;
	case 128:
		uintTemp |= ADC_DATA_RATE_128;
		break;
	case 250:
		uintTemp |= ADC_DATA_RATE_250;
		break;
	case 475:
		uintTemp |= ADC_DATA_RATE_475;
		break;
	default:
		uintTemp |= ADC_DATA_RATE_860;
	}
	writeRegister(ADC_CONTROL_REGISTER1, uintTemp);
#ifdef Debug
	Serial.print("ADC_CONTROL_REGISTER1: ");
	Serial.println(ADC_CONTROL_REGISTER1, HEX);
	Serial.println(uintTemp, HEX);
#endif
}

// afe4300 program占쏙옙占쏙옙 launch
// Global setting >> Reset to EVM Defaults
//
// 7占쏙옙占쏙옙 commands sequence
void Init_AFE4300(void) {
	unsigned int uintTemp;

	uintTemp = 0x4100;
	uintTemp |= 0b010 << ADC_MEAS_MODE; // A2, AVSS = single-ended
	uintTemp |= ADC_DATA_RATE_128;	// 860 SPS
	writeRegister(ADC_CONTROL_REGISTER1, uintTemp);
	delay(1);
#ifdef Debug
	Serial.print("ADC_CONTROL_REGISTER1 :");
	Serial.println(ADC_CONTROL_REGISTER1, HEX);
	Serial.println(uintTemp, HEX);
#endif

	writeRegister(MISC_REGISTER1, 0x0000);
	delay(1);
#ifdef Debug
	Serial.print("MISC_REGISTER1 :");
	Serial.println(MISC_REGISTER1, HEX);
	Serial.println(0x0000, HEX);
#endif

	writeRegister(MISC_REGISTER2, 0xFFFF);
	delay(1);
#ifdef Debug
	Serial.print("MISC_REGISTER2 :");
	Serial.println(MISC_REGISTER2, HEX);
	Serial.println(0xFFFF, HEX);
#endif

	uintTemp = 0x6000;
	uintTemp |= _BV(BCM_PDB);
	writeRegister(DEVICE_CONTROL1, uintTemp); //Power down both signal chains
	delay(1);
#ifdef Debug
	Serial.print("DEVICE_CONTROL1 :");
	Serial.println(DEVICE_CONTROL1, HEX);
	Serial.println(uintTemp, HEX);
#endif

	SetBCM_DAC_Freq(64);  //64kHz

	uintTemp = 0x0011;
	writeRegister(ADC_CONTROL_REGISTER2, uintTemp);
	delay(1);
#ifdef Debug
	Serial.print("ADC_CONTROL_REGISTER2 :");
	Serial.println(ADC_CONTROL_REGISTER2, HEX);
	Serial.println(uintTemp, HEX);
#endif

	uintTemp = 0x0030;
	writeRegister(MISC_REGISTER3, uintTemp);
	delay(1);
#ifdef Debug
	Serial.print("MISC_REGISTER3 :");
	Serial.println(MISC_REGISTER3, HEX);
	Serial.println(uintTemp, HEX);
#endif
}

float ReadImpedanceValue(void) {
  int adc_temp;
  float voltage;

  adc_temp = GetRegisterValue(ADC_DATA_RESULT);

  voltage = (float)adc_temp * (1.7/32767.0) ;
  voltage = ((y2-y1)/(x2-x1))*(voltage-x1)+y1;
//  return voltage ;
  return adc_temp;
//	return (float)adc_temp * (3.3/32767.0) ;
}

void Current_MUX(int ioutp, int ioutn) {
	unsigned int uintTemp;

	uintTemp = 0;

	if (ioutp == RP0 || ioutp == RP1)
		uintTemp |= (1 << ioutp);
	else
		uintTemp |= 1 << ioutp << RP0;

	uintTemp |= 1 << ioutn;
	writeRegister(ISW_MUX, uintTemp);

#ifdef Debug
	Serial.print("ISW_MUX :");
	Serial.println(ISW_MUX, HEX);
	Serial.println(uintTemp, HEX);
#endif
}

void Voltage_MUX(int vsensep, int vsensen) {
	unsigned int uintTemp;

	uintTemp = 0;

	if (vsensep == VSENSP_R0 || vsensep == VSENSP_R1)
		uintTemp |= (1 << vsensep);
	else
		uintTemp |= 1 << vsensep << VSENSP_R0;

	uintTemp |= 1 << vsensen;
	writeRegister(VSENSE_MUX, uintTemp);
#ifdef Debug
	Serial.print("VSENSE_MUX :");
	Serial.println(VSENSE_MUX, HEX);
	Serial.println(uintTemp, HEX);
#endif
}

void plot3(int data1, int data2, int data3) {
	int pktSize;

	buffer[0] = 0xCDAB;  //SimPlot packet header. Indicates start of data packet
	buffer[1] = 3 * sizeof(int); //Size of data in bytes. Does not include the header and size fields
	buffer[2] = data1;
	buffer[3] = data2;
	buffer[4] = data3;

	pktSize = 2 + 2 + (3 * sizeof(int)); //Header bytes + size field bytes + data

	//IMPORTANT: Change to serial port that is connected to PC
	Serial.write((uint8_t *) buffer, pktSize);
	Serial.println("");
}

float adc_values[cMaxChannels];

void setup() {
//	unsigned int uintTemp;

	delay(500);
	pinMode(11, OUTPUT);  // Set the SS pin as an output
	digitalWrite(11, HIGH);  // Set the SS pin HIGH
	delay(500);

	for (int i = 0; i < cMaxChannels; i++)
		adc_values[i] = 0;

	Serial.begin(115200);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	// -------- SPI initialization
	pinMode(ssPin, OUTPUT);  // Set the SS pin as an output
	pinMode(ResetMcuPin, OUTPUT);
	pinMode(ReadyPin, INPUT);

	digitalWrite(ResetMcuPin, HIGH);

	// 1MHz generator
	DDRB = _BV(DDB1);  //set OC1A/PB1 as output (Arduino pin D9, DIP pin 15)
	TCCR1A = _BV(COM1A0);              //toggle OC1A on compare match
	OCR1A = 7;                         //top value for counter
	TCCR1B = _BV(WGM12) | _BV(CS10);   //CTC mode, prescaler clock/1

	digitalWrite(ssPin, HIGH);  // Set the SS pin HIGH
	SPI.begin();  // Begin SPI hardware
	SPI.setClockDivider(SPI_CLOCK_DIV8);  // Slow down SPI clock as 2MHz
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE1);  // falling edge

	//delay(1000);
	//AFE4300_Reset();
	//delay(2000);
	Serial.println("Reset to EVM Defaults");
	Init_AFE4300();

	delay(1000);
	Calibrate();

	//Current_MUX(0, 4);
	//Voltage_MUX(0, 4);
	//writeRegister(VSENSE_MUX, 0x0201);
	//writeRegister(ISW_MUX, 0x0201);

	//writeRegister(VSENSE_MUX, 0x0201);	//VSENSEP_R1, VSENSEM_R0
	//writeRegister(ISW_MUX, 0x0201);		//RP1, RN0
	//SetADC_SamplingRate(250);
	//Current_MUX(3, 2);
	//Voltage_MUX(3, 2);

	//SetBCM_DAC_Freq(0x32);

	//writeRegister(0x0B, 0x0202);
	//uintTemp = GetRegisterValue(0x0B);
	//Serial.println(uintTemp, HEX);

}

char tempString [10];  // Will be used with sprintf to create strings
int iteration = 0;

void loop() {
//	int intTemp = 0x42;
//	unsigned int uintTemp;

	Voltage_MUX(VSENS0, VSENS1);
	Current_MUX(IOUT0, IOUT1);
	while (digitalRead(ReadyPin) > 0)
		;

	adc_values[0] = ReadImpedanceValue();
/*
	Voltage_MUX(VSENS1, VSENS0);
	Current_MUX(IOUT1, IOUT0);
	while (digitalRead(ReadyPin) > 0)
		;
*/
	adc_values[1] = ReadImpedanceValue();
	adc_values[2]=adc_values[1];

	Serial.print(adc_values[0], cPrecision);
	Serial.print(',');
  Serial.print(adc_values[1], cPrecision);
  Serial.print(',');
	Serial.println(adc_values[2], cPrecision);

	//	Serial.print(", ");
	//	Serial.println(adc_values[0]&0xFF, HEX);
	//plot3(adc_values[0], adc_values[1], adc_values[2]);
	/*
	 Voltage_MUX(3, 2);
	 while(digitalRead(ReadyPin)>0);
	 adc_values[1] = ReadImpedanceValue();
	 Serial.println(adc_values[1], DEC);
	 _delay_ms(100);
	 plot4(adc_values[0], adc_values[1], adc_values[2], adc_values[3]);
	 iteration++;
	 #ifdef Debug
	 Serial.println(intTemp);
	 #endif


	 sprintf(tempString, "%4d %4d", intTemp, intTemp + 100);
	 Serial.println(tempString);

	 delay(10);  // This will make the display update at 100Hz.
	 */
}

