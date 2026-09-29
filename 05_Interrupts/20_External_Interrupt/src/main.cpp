/*
 * External_Interrupt
 * --------------------
 * ATmega328P의 두 가지 인터럽트 방식 중 더 기본적인 "외부 인터럽트"(External
 * Interrupt, INT0/INT1)를 다룬다.
 *
 *   - External Interrupt (INT0, INT1) : 딱 2, 3번 핀에서만 동작하지만,
 *     RISING/FALLING/CHANGE/LOW 등 트리거 방식을 자유롭게 고를 수 있다.
 *     `attachInterrupt()` 함수 하나로 간단히 설정 가능 -> 먼저 배우기 좋다.
 *   - Pin Change Interrupt (PCINT, 32_PCInterrupt_Count) : 거의 모든 핀에서
 *     동작하지만, 그룹 단위로만 켜지고 트리거 방식도 "값이 바뀌면"으로 고정.
 *
 * 배선: 2번 핀 - 버튼 - GND (INPUT_PULLUP 사용, 누르면 LOW로 떨어짐)
 *
 * 교재 5장 실습 5-1.
 * 선행 학습: 10_Volatile (아래 pressCount 가 왜 volatile 인지 이해하려면 필요)
 * 다음 단계: 22_Interrupt_Modes (모드를 바꿔 보고 loop 가 계속 도는 것을 확인)
 */
#include <Arduino.h>

const byte BUTTON_PIN = 2;   // INT0 는 Uno에서 2번 핀에 고정되어 있다

volatile unsigned long pressCount = 0;   // ISR과 loop()가 함께 쓰는 변수라 volatile 필수

void onButtonFalling() {
  // ISR(인터럽트 서비스 루틴) 안에서는 최대한 짧고 빠르게!
  // Serial.print()처럼 시간이 걸리는 함수는 ISR 안에서 쓰지 않는 것이 원칙이다.
  pressCount++;
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // attachInterrupt(인터럽트번호 또는 핀, 실행할함수, 트리거방식)
  // digitalPinToInterrupt(2) 는 "2번 핀에 연결된 인터럽트 번호(INT0)"를 찾아준다.
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonFalling, FALLING);

  Serial.println(F("=== External_Interrupt 시작 ==="));
  Serial.println(F("2번 핀 버튼을 눌러보세요. (FALLING: HIGH->LOW 순간에 반응)"));
}

void loop() {
  static unsigned long lastReported = 0;

  // loop()는 인터럽트와 무관하게 계속 자기 할 일(여기서는 카운트 출력)을 한다.
  // 버튼을 누르는 순간은 ISR이 즉시 처리하고, loop()는 나중에 그 결과(pressCount)를
  // 확인만 하면 된다 -> 이것이 "polling"(계속 확인)과 "interrupt"(알려줄 때만 반응)의 차이.
  if (pressCount != lastReported) {
    lastReported = pressCount;
    Serial.print(F("버튼 눌림 감지! 누적 횟수: "));
    Serial.println(pressCount);
  }
}
