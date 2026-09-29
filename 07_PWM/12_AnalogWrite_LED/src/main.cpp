/*=======================================================*/
// AnalogWrite_LED : 디지털 핀으로 아날로그 출력을 흉내 낸다
//
// 교재 7장 실습 7-1. ATmega328P 에는 DAC 가 없다. 핀은 0 V 아니면 5 V 만 낼 수 있다.
// 그런데 아주 빠르게 켜고 끄면서 켜 있는 시간의 비율을 바꾸면, LED 는 그 평균만큼
// 밝아 보인다. 주기는 고정하고 High 폭만 바꾸는 것이 PWM 이다.
//
// analogWrite(pin, value) 의 value 는 0~255 다. 8비트다.
// ADC(analogRead)는 0~1023 으로 10비트였다. 둘을 섞지 않도록 주의한다.
//
// 연결
//   LED + 저항 220옴 : 10번 핀 - GND
//   파형을 보려면 10번 핀을 계측기에 물린다 (4장 §4.5 의 두 경로 그대로)
//
// 눈여겨볼 것 : loop 가 비어 있어도 파형이 계속 나온다.
// analogWrite 는 타이머 하드웨어를 설정해 두는 것이고, 그 뒤로는 CPU 가
// 아무것도 하지 않아도 회로가 파형을 만든다. 이것이 하드웨어 PWM 이다.
//
// 주기는 약 2 ms(약 490 Hz)로 고정이다. analogWrite 로는 바꿀 수 없다.
// 주기를 바꾸려면 타이머 레지스터를 직접 다뤄야 한다(17장).
//
// 선행 학습 : 01_Digital_IO/10_Blink      다음 단계 : 16_PWM_ADC
/*=======================================================*/
#include <Arduino.h>

const uint8_t LED = 10;

// 듀티를 눈에 보이게 바꿔 가며 보여 준다
const uint8_t steps[] = {0, 25, 128, 205, 255};
const uint8_t STEP_COUNT = sizeof(steps) / sizeof(steps[0]);

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  for (uint8_t i = 0; i < STEP_COUNT; i++) {
    analogWrite(LED, steps[i]);

    Serial.print("value = ");
    Serial.print(steps[i]);
    Serial.print("   duty = ");
    // 정수로 계산한다. 실수를 쓰면 변환 코드가 끌려 들어와 커진다(6장)
    Serial.print(steps[i] * 100L / 255);
    Serial.println(" %");

    delay(2000);
  }
}
