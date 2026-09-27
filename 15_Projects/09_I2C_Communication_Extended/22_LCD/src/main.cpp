/*=======================================================*/
// 22_LCD : HD44780 병렬 4비트 문자 LCD 에 ADC 값을 전압으로 표시한다
//
// 교재 13장 실습 13-1.  원천: 12주차B §7~8, 13주차A §1
// 검증 : PIO 6.2.0 / avr-gcc 7.3.0 / Flash 5016 B / RAM 284 B
//        가변저항 가운데에서 ADC 512, 2.50 V 표시
//
// 원리 : LCD 안에 HD44780 컨트롤러가 들어 있어 문자 코드를 보내면
//        글자 모양(CGROM)을 찾아 화면(DDRAM)에 띄운다.
//        RS 로 명령과 데이터를 가르고, E 의 하강 에지에서 값을 가져간다.
//        데이터선은 상위 4개만 써서 한 바이트를 두 번에 나눠 보낸다(4비트 모드).
//
// 연결 : RS = 2, E = 3, D4~D7 = 4~7   (LiquidCrystal 생성자의 인자 순서와 같다)
//        R/W = GND  — 읽을 일이 없으므로 쓰기로 고정해 핀 하나를 아낀다
//        VSS = GND, VDD = 5V
//        VEE(V0) = 대비 조정 단자. 10kΩ 가변저항의 가운데를 물리거나
//                  시뮬레이터에서는 GND 에 붙여 대비를 최대로 둔다
//        측정용 가변저항 : 양끝을 GND·5V 에, 가운데를 A0 에
//
// 참고 : AVR 의 sprintf 는 기본 설정에서 %f 를 링크하지 않는다.
//        여기서는 Print 클래스의 소수 자릿수 인자(아래 2)를 써서 피했다.
//        sprintf 로 직접 만들려면 dtostrf 로 먼저 문자열로 바꾼다.
//
// 다음 단계 : 09_I2C_Communication/30_LCD_I2Cm  (같은 화면을 두 가닥으로)
/*=======================================================*/
#include <Arduino.h>
#include <LiquidCrystal.h>

// 생성자 인자 순서 : RS, E, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);                 // 16글자 x 2줄
  lcd.print("Hello, HKNU!");        // 첫째 줄
  lcd.setCursor(0, 1);              // 열 0, 둘째 줄 (행 번호는 0 부터다)
  lcd.print("HKNU");

  Serial.begin(9600);               // 같은 값을 터미널로도 내보낸다
}

void loop() {
  int val;

  val = analogRead(A0);             // 10비트 : 0 ~ 1023

  lcd.setCursor(0, 1);
  lcd.print("ADC = ");
  lcd.print((val));
  lcd.print(", ");
  lcd.print(map(val, 0, 1023, 0, 5000)/1000.0, 2);   // mV 로 환산해 V 로, 소수 2자리

  Serial.println(val);
  Serial.println(map(val, 0, 1023, 0, 5000)/1000.0, 2);
  delay(500);
  lcd.print("                   "); // 자릿수가 줄 때 이전 글자가 남지 않게 지운다
}
