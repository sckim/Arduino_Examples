#define SW_A	8
#define SW_B	9

unsigned char SEG[10] = { 0b11000000, 0b11111001, 0b10100100, 0b10110000,
		0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000 };

// 핀 하나하나를 개별적으로 제어하여 프로그램하는 예
void setup() {
	for (int i = 0; i < 8; i++) {
		pinMode(i, OUTPUT);  // pin의 입출력 상태 결정
		digitalWrite(i, HIGH); // 현재 pin 출력을 high
	}

	pinMode(SW_A, INPUT_PULLUP);
	pinMode(SW_B, INPUT_PULLUP);

	// enable interrupt for pin...
	pciSetup(SW_A);
	pciSetup(SW_B);
}

void dispSeg(unsigned char ch) {
	for (int i = 0; i < 8; i++)
		digitalWrite(i, SEG[ch] & (1 << i));
}

volatile char num = 0;
volatile char inc = 1;

// Install Pin change interrupt for a pin, can be called multiple times
void pciSetup(byte pin) {
	// enable interrupt for the group
	PCICR |= bit(digitalPinToPCICRbit(pin));
	// enable pin
	*digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));
	// clear any outstanding interrupt
	PCIFR |= bit(digitalPinToPCICRbit(pin));
}

// Use one Routine to handle each group
ISR (PCINT0_vect)// handle pin change interrupt for D8 to D13 here
{
	if( !digitalRead(SW_A) ) // Pushed
	num = 0;

	if( !digitalRead(SW_B) ) {
		if (inc > 0)
		inc = -1;
		else
		inc = 1;
	}
}

void loop() {
	dispSeg(num);
	num += inc;

	if (num > 9)
		num = 0;
	if (num < 0)
		num = 9;

	delay(1000);
}
