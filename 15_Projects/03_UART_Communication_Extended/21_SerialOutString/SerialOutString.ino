#define Arduino
int cLED = 13;
int index = 0;
int incomingByte = 0; // for incoming serial data

void setup()
{
#ifdef Arduino
  	pinMode(cLED, OUTPUT);
  	pinMode(8, INPUT);
  	Serial.begin(9600);
#else
  	DDRB |= (1<<PB5);
  	DDRB &= ~(1<<PB0);
#endif
}

void loop()
{
#ifdef Arduino
  String str = Serial.readString();
  str.toUpperCase();
  if ( str.equals("ON"))
     	digitalWrite(cLED, HIGH);
  else if ( str.equals("OFF") )
     	digitalWrite(cLED, LOW);
  else if (str.equals(""))
  		str="";
  else
    	Serial.println("Wrong command");

  Serial.print("Index = ");
  Serial.print(index, DEC);
  Serial.print(", Status = ");
  Serial.println(incomingByte, DEC);

  delay(100);
#else
  if ( PINB & (1<<PB0) )
  //if( bit_is_set(PINB, PB0) )
     PORTB |= (1<<PB5);
  else
     PORTB &= ~(1<<PB5);
#endif

  index++;
}

/*
if (Serial.available() > 0) {
  // read the incoming byte:
  	incomingByte = Serial.read();
	if ( incomingByte=='1' )
     	digitalWrite(cLED, HIGH);
  	else
     	digitalWrite(cLED, LOW);
  }
*/
