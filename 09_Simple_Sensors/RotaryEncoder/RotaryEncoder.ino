/* Author: Danny van den Brande, Arduinosensors.nl
 This is a example on how to use the KY-040 Rotary encoder.
 Its very basic but if your new to arduino or could not find
 any code, then you have something to start with.
 because there is little documentation about the KY sensor kit.
 */
int PinA = 2;  // Pin 2 to clk on encoder
int PinB = 3;  // Pin 3 to DT on encoder

int RotPosition = 0;
int pinA_Last;
int pinA_Current;

boolean bCW;
void setup() {
	Serial.begin(9600);
	pinMode(PinA, INPUT);
	pinMode(PinB, INPUT);

	pinA_Last = digitalRead(PinA);
}
void loop() {
	pinA_Current = digitalRead(PinA);

	if (pinA_Current != pinA_Last) { // we use the DT pin to find out which way we turning.
		// CLK is changed ?
		if (digitalRead(PinB) != pinA_Current) {  // Clockwise
			RotPosition++;
			bCW = true;
		} else { //Counterclockwise
			RotPosition--;
			bCW = false;
		}
		if (bCW) { // turning right will turn on red led.
			Serial.println("clockwise");
		} else {        // turning left will turn on green led.
			Serial.println("counterclockwise");
		}
		Serial.print("Encoder RotPosition: ");
		Serial.println(RotPosition);
	}
	pinA_Last = pinA_Current;
}
