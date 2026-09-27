#define LED 13
#define cInPin	9 //from P2.0 ..

#define cBaudRate 9600

#define cHeader	'!'
#define cCode	128
#define cDel	','
#define Firmware_Version	12

#define cID	1

//LED는 디지털 13번 핀에 연결되어 있음
void setup(){
	Serial.begin(cBaudRate);
	// 디지털핀(13)을 출력으로 설정
	
	pinMode(LED, OUTPUT);
	
	pinMode(cInPin, INPUT);
	pinMode(cInPin+1, INPUT);
	pinMode(cInPin+2, INPUT);	
}

byte getID(void)
{
	byte	id;
	
	id = digitalRead(cInPin);
	id += digitalRead(cInPin+1) << 1;
	id += digitalRead(cInPin+2) << 2;
	
	id=12;
	return id;
}

void loop() {
	unsigned char ch;
	
	//LED를 켠다.
	digitalWrite(LED,HIGH);
	//1초 대기
	delay(500);
	
	Serial.write(cHeader);
	Serial.write(cCode);
	Serial.write(cDel);
	Serial.write((byte)getID());
	Serial.write(cDel);
	Serial.write((byte)Firmware_Version);
	Serial.write('\n');

	//LED를 끈다.
	digitalWrite(LED,LOW);
	//1초 대기
	delay(500);
}

