#include <Arduino.h>
/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 3
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, HKNU!");
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("HKNU");

  Serial.begin(9600);
}

void loop() {
  int val;

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):

  // print the number of seconds since reset:
  val = analogRead(A0);

  lcd.setCursor(0, 1);
  lcd.print("ADC = ");
  lcd.print((val));
  lcd.print(", ");
  lcd.print(map(val, 0, 1023, 0, 5000)/1000.0, 2);

  Serial.println(val);
  Serial.println(map(val, 0, 1023, 0, 5000)/1000.0, 2);
  delay(500);
  lcd.print("                   ");
}
