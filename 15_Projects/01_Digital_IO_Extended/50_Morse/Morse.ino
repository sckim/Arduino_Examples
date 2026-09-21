#include "Arduino.h"
#define speakerPin	3
#define ledPin		13

#define dotDelay	200

/* morse codes of the 26 letters */
char *morse[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
		".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...",
		"-", "..-", "...-", ".--", "-..-", "-.--", "--.." };

char *numbers[] = { "-----", ".----", "..---", "...--", "....-", ".....",
		"-....", "--...", "---..", "----." };

void DotOrDash(char dotOrdash) {
	digitalWrite(ledPin, HIGH);
	if (dotOrdash == '.') {
		tone(speakerPin, 1000, dotDelay);
		delay(dotDelay);
	} else {
		tone(speakerPin, 1000, dotDelay * 3);
		delay(dotDelay * 3);
	}
	digitalWrite(ledPin, LOW);
	delay(dotDelay);
}

void printMOS(char *mos) {
	int i = 0;

	while (mos[i] != NULL) {
//		Serial.print(mos[i]);
		DotOrDash(mos[i]);
		i++;
	}
	delay(dotDelay * 5);
}

void Char2Morse(char ch) {
	if (isAlpha(ch)) {
		Serial.write(toupper(ch));
		Serial.print("  " + String(morse[toupper(ch) - 'A']));
		printMOS(morse[toupper(ch) - 'A']);
	} else if (isDigit(ch)) {
		Serial.write(ch);
		Serial.print("  " + String(numbers[ch - '0']));
		printMOS(numbers[ch - '0']);
	} else {
		Serial.println("Error: This is not a character or a number.");
	}
}

void SendMorseMsg(char *str) {
	int i = 0;

	while (str[i] != NULL) {
		Char2Morse(str[i]);
		i++;
	}
	Serial.println();
}

void setup() {
	//tone할 수를 사용할때는 출력으로 설정하지 않더라도 됨.
	pinMode(speakerPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
	Serial.begin(9600);

	SendMorseMsg("SOS");
}

void loop() {
	unsigned char ch;

	if (Serial.available() > 0) {
		ch = Serial.read();
		Char2Morse(ch);
		Serial.println();
	}
}
