#define Arduino

int cLED = 13;

void setup()
{
#ifdef Arduino
 	pinMode(cLED, OUTPUT);
#else
    DDRB = (1 << PB1);
#endif
}


void loop()
{
#ifdef Arduino
  digitalWrite(cLED, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(cLED, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
#else
  PORTB |= (1<<PB1);
  delay(1000);
  PORTB &= ~(1<<PB1);
  delay(1000);
#endif
}
