#include <avr/sleep.h>
#include <avr/wdt.h>

long timeSleep = 0;  // total time due to sleep
float calibv = 0.93; // ratio of real clock with WDT clock
volatile byte isrcalled = 0;  // WDT vector flag

// Internal function: Start watchdog timer
// byte psVal - Prescale mask
void WDT_On (byte psVal)
{
  // prepare timed sequence first
  byte ps = (psVal | (1<<WDIE)) & ~(1<<WDE);
  cli();
  wdt_reset();
  /* Clear WDRF in MCUSR */
  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = ps;
  sei();
}

// Internal function.  Stop watchdog timer
void WDT_Off() {
  cli();
  wdt_reset();
  /* Clear WDRF in MCUSR */
  MCUSR &= ~(1<<WDRF);
  /* Write logical one to WDCE and WDE */
  /* Keep old prescaler setting to prevent unintentional time-out */
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  /* Turn off WDT */
  WDTCSR = 0x00;
  sei();
}

// Calibrate watchdog timer with millis() timer(timer0)
void calibrate() {
  // timer0 continues to run in idle sleep mode
  set_sleep_mode(SLEEP_MODE_IDLE); 
  long tt1=millis();
  doSleep(256);
  long tt2=millis();
  calibv = 256.0/(tt2-tt1);
}

// Estimated millis is real clock + calibrated sleep time
long estMillis() {
  return millis()+timeSleep;
}

// Delay function
void sleepCPU_delay(long sleepTime) {
  ADCSRA &= ~(1<<ADEN);  // adc off
  PRR = 0xEF; // modules off

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  int trem = doSleep(sleepTime*calibv);
  timeSleep += (sleepTime-trem);

  PRR = 0x00; //modules on
  ADCSRA |= (1<<ADEN);  // adc on
}

// internal function.  
int doSleep(long timeRem) {
#if defined(WDP3)
  byte WDTps = 9;  // WDT Prescaler value, 9 = 8192ms
#else
  byte WDTps = 7;  // WDT Prescaler value, 7 = 2048ms
#endif

  isrcalled = 0;
  sleep_enable();
  while(timeRem > 0) {
    //work out next prescale unit to use
    while ((0x10<<WDTps) > timeRem && WDTps > 0) {
      WDTps--;
    }
    // send prescaler mask to WDT_On
    WDT_On((WDTps & 0x08 ? (1<<WDP3) : 0x00) | (WDTps & 0x07));
    isrcalled=0;
    while (isrcalled==0) {
      // turn bod off
      MCUCR |= (1<<BODS) | (1<<BODSE);
      MCUCR &= ~(1<<BODSE);  // must be done right before sleep
      sleep_cpu();  // sleep here
    }
    // calculate remaining time
    timeRem -= (0x10<<WDTps);
  }
  sleep_disable();
  return timeRem;
}

// wdt int service routine
ISR(WDT_vect) {
  WDT_Off();
  isrcalled=1;
}

int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  sleepCPU_delay(1000);
  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  sleepCPU_delay(1000);
}
