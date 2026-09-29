/*=======================================================*/
// AnalogReadSerial : 가변저항 전압을 읽어 숫자와 전압으로 본다
//
// 교재 6장 실습 6-1. ADC 의 기본이다. 지금까지 읽은 입력은 HIGH 아니면 LOW
// 였는데, 여기서 처음 그 중간 값을 읽는다.
//
// 연결
//   가변저항 양 끝  : 5V 와 GND
//   가변저항 와이퍼 : A0
//
// analogRead 는 0~1023 을 돌려준다. 10비트이므로 1024 단계다.
// 반환값을 int 로 받는다. byte(0~255)로는 1023 을 담을 수 없다.
//
// 전압으로 바꾸는 식은 데이터시트에서 온다.
//   데이터시트 : ADC = Vin × 1024 / Vref
//   따라서      : Vin = ADC × Vref / 1024
// 아두이노 예제들은 관습적으로 1023 으로 나눈다. 5V 기준에서 두 값의 차이는
// 5 mV 아래라 실용상 문제가 없지만, 이 책은 데이터시트를 따라 1024 로 나눈다.
//
// 선행 학습 : 03_UART_Communication/10_Serial      다음 단계 : 40_ADC_Buttons
/*=======================================================*/
#include <Arduino.h>

const uint8_t POT = A0;
const float VREF = 5.0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int adc = analogRead(POT);            // 0 ~ 1023
  float voltage = adc * VREF / 1024.0;  // 실수로 나눈다. 정수 나눗셈은 버림이 된다

  Serial.print("ADC = ");
  Serial.print(adc);
  Serial.print("   V = ");
  Serial.println(voltage, 3);           // 소수 셋째 자리까지

  delay(200);
}
