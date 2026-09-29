/*=======================================================*/
// PWM_ADC : 가변저항으로 LED 밝기를 조절한다
//
// 교재 7장 실습 7-2. 6장에서 읽은 ADC 값을 7장의 PWM 으로 내보낸다.
// 아날로그 입력 -> 숫자 -> 아날로그 출력 흉내. 1부의 두 장이 여기서 만난다.
//
// 연결
//   가변저항 와이퍼 : A0   (양 끝은 5V 와 GND)
//   LED + 저항 220옴 : 10번 핀 - GND
//
// 10비트를 8비트로 줄여야 한다. analogRead 는 0~1023, analogWrite 는 0~255 다.
//   adc / 4    와  adc >> 2    는 같은 값이다.
// 2 의 거듭제곱으로 나눌 때는 시프트가 유리하다. AVR 에는 나눗셈 명령이 없어서
// / 4 는 컴파일러가 시프트로 바꿔 주지만, 뜻을 분명히 하려고 >> 2 로 쓴다.
//
// 값이 바뀔 때만 analogWrite 를 부른다. 같은 값을 다시 쓰는 것은 낭비다.
// 6장 30_LED_bar 에서 쓴 것과 같은 구조다.
//
// 선행 학습 : 12_AnalogWrite_LED, 04_ADC/10_AnalogReadSerial
// 다음 단계 : 08_Motors/12_Servo_Bitbang
/*=======================================================*/
#include <Arduino.h>

const uint8_t POT = A0;
const uint8_t LED = 10;

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  static int prevDuty = -1;            // 처음에는 어떤 값과도 다르다

  int adc = analogRead(POT);           // 0 ~ 1023  (10비트)
  int duty = adc >> 2;                 // 0 ~ 255   ( 8비트)

  if (duty != prevDuty) {              // 바뀔 때만 갱신한다
    analogWrite(LED, duty);

    Serial.print("ADC = ");
    Serial.print(adc);
    Serial.print("   duty = ");
    Serial.println(duty);

    prevDuty = duty;
  }
}
