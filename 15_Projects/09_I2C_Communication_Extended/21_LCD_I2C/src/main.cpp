#include <Arduino.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 20 chars and 4 line display

void setup()
{
  Serial.begin(9600);
  Serial.println("LCD...");

  // wait on Serial to be available on Leonardo
  while (!Serial)
    ;

  Serial.println("Probing for PCF8574 on address 0x27...");

  lcd.begin(16,2);
  lcd.setBacklight(HIGH); // initialize the lcd
  // Print a message to the LCD.
  lcd.home();  // set the cursor to (0,0)
  lcd.clear(); // clear the display
  lcd.print("Hello, world!");
  lcd.setCursor(2, 1);
  lcd.print("HKNU Univ.");
}

void loop()
{
}

// #include <Wire.h>

// void setup()
// {
//   Wire.begin();
//   Serial.begin(9600);
//   while (!Serial)
//     ; // 시리얼 모니터 대기
//   Serial.println("I2C Scanner");
// }

// void loop()
// {
//   byte error, address;
//   int nDevices = 0;

//   Serial.println("Scanning...");

//   for (address = 1; address < 127; address++)
//   {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address < 16)
//         Serial.print("0");
//       Serial.println(address, HEX);
//       nDevices++;
//     }
//     else if (error == 4)
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address < 16)
//         Serial.print("0");
//       Serial.println(address, HEX);
//     }
//   }

//   if (nDevices == 0)
//     Serial.println("No I2C devices found");
//   else
//     Serial.println("Done");

//   int adc_value;
//   int num;

//   adc_value = analogRead(A0);
//   num = map(adc_value, 0, 1023, 0, 9);
//   Serial.print("ADC[0] = ");
//   Serial.print(adc_value);
//   Serial.print(", ");
//   Serial.print(map(adc_value, 0, 1023, 0, 500) / 100.0, 2);
//   Serial.println("[V]");

//   delay(5000); // 5초 대기 후 재스캔
// }