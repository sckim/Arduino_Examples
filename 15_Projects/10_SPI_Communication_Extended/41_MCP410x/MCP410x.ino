//The setup function is called once at startup of the sketch
#include <SPI.h>
const int slaveSelectPin  = 10;
#define MAX_POT	5000.0

void setup()
{
  Serial.begin(9600);
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  pinMode(MOSI, OUTPUT); //SDI
  pinMode(SCK, OUTPUT);
  //SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.beginTransaction(SPISettings(10000000,MSBFIRST,SPI_MODE0));
  // initialize SPI:
  SPI.begin();

  pinMode(4, OUTPUT);
  Serial.println("Welcome");
}

int iPot=0;

void loop()
{
	int adc=0;
	float voltage;
//	static char disp[7];

	// change the resistance on this channel from min to max:

    digitalPotWrite(iPot+=1);
    //digitalPotWrite(255);
    delay(1); // Slave Select period, 10ms
//    // wait a second at the top:
//    // change the resistance on this channel from max to min:
    if( iPot> 255)
    	iPot=0;
    Serial.print(iPot);
    Serial.print(", ");
    Serial.print(MAX_POT*(iPot/255.0));
    Serial.print(", ");

    adc = analogRead(A0);
    //voltage = map(adc, 0, 1023, 0.0, 5.0);
//    dtostrf(voltage, 5,3,disp);
    voltage = adc * 5.0/1023.0;
    Serial.println(voltage);
}

void digitalPotWrite(int value)
{
  // take the SS pin low to select the chip:

  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  // MCP41xxx send 0x11
  // 4161-xxxx send 0x00
  SPI.transfer(0);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}
