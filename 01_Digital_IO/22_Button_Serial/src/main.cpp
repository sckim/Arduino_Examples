/*=======================================================*/
// Button_Serial : 버튼을 digitalRead 로 읽고 그 값을 시리얼로 본다
//
// 교재 3장 실습 3-1. 풀업 없이 읽었을 때와 INPUT_PULLUP 으로 읽었을 때가
// 어떻게 다른지 시리얼 값으로 확인하는 것이 목적이다.
//
// 연결
//   푸시 버튼 : 2번 핀 <-> GND   (저항 없이)
//   LED       : 13번 핀 (보드 내장 LED 를 그대로 써도 된다)
//
// 실습 절차
//   1단계 : 아래 INPUT 그대로 올린다 -> 버튼을 떼면 값이 흔들린다(플로팅)
//   2단계 : INPUT 을 INPUT_PULLUP 으로 한 줄만 고친다 -> 떼면 1 로 고정
//   3단계 : INPUT 으로 되돌리고 2번 핀과 5V 사이에 10k 저항 (외부 풀업)
//   4단계 : 저항을 2번 핀과 GND 로, 버튼 반대쪽을 5V 로 (풀다운) -> 값이 반대
//
// 선행 학습 : 10_Blink      다음 단계 : 50_Bit_Mask
/*=======================================================*/
#include <Arduino.h>

const uint8_t BTN = 2;
const uint8_t LED = 13;

void setup() {
  pinMode(BTN, INPUT);        // 2단계에서 이 줄만 INPUT_PULLUP 으로 고친다
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int state = digitalRead(BTN);

  if (state == LOW) {         // 풀업 회로에서는 눌림이 LOW 다
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

  Serial.println(state);
  delay(200);
}
