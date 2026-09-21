void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  Serial.println("bool : " + String(sizeof(bool)));
  Serial.println("boolean : " + String(sizeof(boolean)));
  Serial.println("char : " + String(sizeof(char)));
  Serial.println("byte : " + String(sizeof(byte)));
  Serial.println("int : " + String(sizeof(int)));
  Serial.println("short : " + String(sizeof(short)));
  Serial.println("long : " + String(sizeof(long)));
  Serial.println("float : " + String(sizeof(float)));
  Serial.println("double : " + String(sizeof(double)));
  Serial.println("word : " + String(sizeof(word)));
  Serial.println("size_t : " + String(sizeof(size_t)));
  Serial.println("void : " + String(sizeof(void)));

  // do nothing while true:
  while (true);
}
