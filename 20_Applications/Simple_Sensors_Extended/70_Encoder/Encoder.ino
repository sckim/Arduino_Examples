//The setup function is called once at startup of the sketch

//Encoder switch pins
// upper left SW
// upper right GND
// lower left A
// lower center GND
// lower right B

#define SW		3
#define PinA	A2
#define PinB	A1

int RotPosition = 0;
int pinA_Last, pinA_Current;

void setup() {
	// Add your initialization code here
	Serial.begin(9600);
	pinMode(PinA, INPUT);
	pinMode(PinB, INPUT);
	pinMode(SW, INPUT);

	digitalWrite(PinA, HIGH);  //pull up
	digitalWrite(PinB, HIGH);
	digitalWrite(SW, HIGH);

	pinA_Last = digitalRead(PinA);
}

// The loop function is called in an endless loop

void loop() {
	pinA_Current = digitalRead(PinA);

	if (pinA_Current != pinA_Last) {
		if (digitalRead(PinB) != pinA_Current) {
			RotPosition++;
			Serial.println("clockwise");
		} else {
			RotPosition--;
			Serial.println("countclockwise");
		}
		Serial.print("Encoder RotPosition: ");
		Serial.print(RotPosition);
		Serial.print(", SW status: ");
		Serial.println(digitalRead(SW));
	}
	pinA_Last = pinA_Current;
}
