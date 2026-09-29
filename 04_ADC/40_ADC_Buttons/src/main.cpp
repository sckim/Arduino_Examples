/*=======================================================*/
// ADC_Buttons : ADC 한 채널로 버튼 다섯 개를 읽는다
//
// 교재 6장 실습 6-3. 디지털 입력은 0 과 1 만 구별한다. ADC 는 그 중간을 읽으므로
// 버튼마다 다른 전압을 만들어 두면 핀 하나로 여러 버튼을 가려낼 수 있다.
// GPIO 로 버튼 다섯 개를 읽으면 핀 다섯 개가 들지만 이 방법은 ADC 한 채널이면 된다.
//
// 연결 — 저항 사다리
//   5V --[ R_UP 10k ]--+--> A2 (ADC 입력)
//                      |
//                      +--[S1]-- GND                (0 옴)
//                      +--[330]--+--[S2]-- GND
//                                +--[620]--+--[S3]-- GND
//                                          +--[1k]--+--[S4]-- GND
//                                                   +--[3.3k]--[S5]-- GND
//
// 눌린 버튼에 따라 GND 까지의 저항이 달라지고, R_UP 과 전압 분배가 되어
// A2 의 전압이 달라진다. 아무 것도 안 누르면 회로가 열려 전류가 흐르지 않으므로
// A2 는 5V, 즉 1023 이 된다.
//
//   버튼    GND 까지 저항   전압      ADC
//   없음    열림            5.00 V    1023
//   S1      0 옴            0.00 V       0
//   S2      330             0.16 V      32
//   S3      950             0.43 V      88
//   S4      1,950           0.82 V     167
//   S5      5,250           1.72 V     352
//
// 경계값은 인접한 두 ADC 값의 중간으로 잡는다. 그렇게 하면 저항 오차와
// 노이즈에 견딘다. 예를 들어 S2(32)와 S3(88) 사이는 60 이다.
//
// 한계 : 두 개를 함께 누르면 GND 까지 저항이 낮은 쪽만 인식된다.
//        S1 과 S2 를 함께 누르면 S1 로 읽힌다. 한 번에 하나씩 누르는 용도다.
//
// 선행 학습 : 10_AnalogReadSerial      다음 단계 : 07_PWM
/*=======================================================*/
#include <Arduino.h>

const uint8_t KEYPAD = A2;

// 인접한 ADC 값의 중간값. 큰 것부터 비교한다.
const int TH_NONE = 687;   // (352 + 1023) / 2
const int TH_S5   = 259;   // (167 + 352) / 2
const int TH_S4   = 127;   // ( 88 + 167) / 2
const int TH_S3   =  60;   // ( 32 +  88) / 2
const int TH_S2   =  16;   // (  0 +  32) / 2

// 0 이면 안 눌린 것, 1~5 는 S1~S5
uint8_t readButton(int adc)
{
  if (adc > TH_NONE) return 0;
  if (adc > TH_S5)   return 5;
  if (adc > TH_S4)   return 4;
  if (adc > TH_S3)   return 3;
  if (adc > TH_S2)   return 2;
  return 1;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("ADC 한 채널로 버튼 다섯 개를 읽는다");
}

void loop()
{
  static uint8_t prev = 0;

  int adc = analogRead(KEYPAD);
  uint8_t btn = readButton(adc);

  if (btn != prev) {                 // 바뀐 때만 알린다
    if (btn == 0) {
      Serial.print("놓음        ADC = ");
      Serial.println(adc);
    } else {
      Serial.print("S");
      Serial.print(btn);
      Serial.print(" 눌림     ADC = ");
      Serial.println(adc);
    }
    prev = btn;
  }

  delay(20);                         // 채터링을 조금 눌러 준다
}
