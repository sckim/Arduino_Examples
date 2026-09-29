/*=======================================================*/
// LED_bar : 가변저항 값을 LED 8개의 막대 그래프로 표시한다
//
// 교재 6장 실습 6-2. 3장 실습 3-2(50_Bit_Mask)에서 만든 LED 막대를 그대로 쓴다.
// 그때는 정해진 패턴을 내보냈고, 이번에는 ADC 로 읽은 값을 내보낸다.
//
// 연결 (LED 는 저항 220옴을 거쳐 GND 로, 즉 HIGH 에서 켜진다)
//   LED0, LED1 : 8, 9번 핀   (PB0, PB1)
//   LED2~LED7  : 2~7번 핀    (PD2~PD7)
//   가변저항   : 양 끝을 5V·GND, 와이퍼를 A0
//   50_Bit_Mask 와 같은 배선이므로 브레드보드를 그대로 쓸 수 있다.
//
// 막대 값 level(0~8)을 하위 level 비트만 1 인 마스크로 만들어 내보낸다.
//   level = 3  ->  0b00000111
// 같은 일을 레지스터로 쓴 것이 02_AVR_C_Development/01_Digital_IO/30_LED_bar 다.
//
// 선행 학습 : 50_Bit_Mask, 04_ADC/10_AnalogReadSerial
/*=======================================================*/
#include <Arduino.h>

// 비트 i 가 나가는 핀. 50_Bit_Mask 와 같은 배선이다.
const uint8_t LED_pins[] = {8, 9, 2, 3, 4, 5, 6, 7};
const uint8_t LED_COUNT = sizeof(LED_pins) / sizeof(LED_pins[0]);   // 요소 크기로 나눈다

const uint8_t POT = A0;

void showBar(uint8_t level)            // level : 0 ~ 8
{
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_pins[i], (i < level) ? HIGH : LOW);
  }
}

void setup()
{
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    pinMode(LED_pins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  static int prevLevel = -1;           // 처음에는 어떤 level 과도 다르다

  int adc = analogRead(POT);
  int level = map(adc, 0, 1023, 0, 8); // 0~1023 을 0~8 로 옮긴다

  if (level != prevLevel) {            // 값이 바뀐 때만 갱신한다
    showBar(level);
    Serial.print("ADC = ");
    Serial.print(adc);
    Serial.print("   level = ");
    Serial.println(level);
    prevLevel = level;
  }
}
