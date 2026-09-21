#include <SPI.h>

const int slaveSelectPin = 10;


//#define Sender

#ifdef Sender
void setup (void)
{
  Serial.begin (9600);   // debugging

  pinMode(slaveSelectPin, OUTPUT);
  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);

}  // end of setup

void loop (void)
{

  char c;

  // enable Slave Select
  digitalWrite(slaveSelectPin, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "Hello, world 123!\n" ; c = *p; p++)
    SPI.transfer (c);

  Serial.println("Hello, world 123!\n");

  delay(100);
  // disable Slave Select
  digitalWrite(slaveSelectPin, HIGH);

  delay (1000);  // 1 seconds delay
}
#else
#include <SPI.h>

char buf[100];
volatile byte pos;
volatile bool process_it;

void setup(void) {
	Serial.begin(9600);   // debugging

	// turn on SPI in slave mode
	SPCR |= bit(SPE);

	pinMode(SS, INPUT);
	// have to send on master in, *slave out*
	pinMode(MISO, OUTPUT);

    SPI.setClockDivider(SPI_CLOCK_DIV8);

	// get ready for an interrupt
	pos = 0;   // buffer empty
	process_it = false;

	// now turn on interrupts
	SPI.attachInterrupt();

}  // end of setup

// SPI interrupt routine
ISR (SPI_STC_vect) {
	byte c = SPDR;  // grab byte from SPI Data Register

	// add to buffer if room
	if (pos < sizeof buf) {
		buf[pos++] = c;

		// example: newline means time to process buffer
		if (c == '\n')
			process_it = true;

	}  // end of room available
}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop(void) {
	if (process_it) {
		buf[pos] = 0;
		Serial.println(buf);
		pos = 0;
		process_it = false;
	}  // end of flag set

}  // end of loop
#endif
