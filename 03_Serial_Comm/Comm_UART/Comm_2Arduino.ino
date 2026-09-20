//#define Sender

#ifdef Sender
#define cntSpeed		A0

void setup() {
  Serial.begin(9600);
}

void loop(){
  int val = analogRead(A0);

  Serial.print("Speed = ");
  Serial.println(val);
  //Serial.write(val);
  //Serial.println("");

  delay(100);
}

#else
void setup() {
  Serial.begin(9600);
}

void loop(){
	 if( Serial.available()> 0) {
		char a = Serial.read();// read the incoming data as string
		Serial.print(a);
	}
//	String str = Serial.readString();
//	Serial.print(str);
}
#endif
