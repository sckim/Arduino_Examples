/*
 * Watchdog_Basic
 * --------------
 * wdt_enable() / wdt_reset() 를 이용한 워치독 타이머(Watchdog Timer, WDT) 기초 예제.
 *
 * 개념:
 *   - wdt_enable(timeout) 로 워치독을 켜면, 그 시간(timeout) 안에 wdt_reset() 이
 *     한 번도 호출되지 않으면 MCU가 스스로 리셋(재부팅)된다.
 *   - 즉, 코드가 무한루프에 빠지거나 멈춰버려도(hang) WDT가 강제로 되살려준다.
 *   - loop() 안에서 주기적으로 wdt_reset() 을 호출해 "나는 살아있다"고 계속
 *     알려주는 것이 핵심이다.
 *
 * 동작 방법:
 *   1. 평상시에는 LED(13번)가 정상적으로 깜빡인다 (살아있다는 표시).
 *   2. 버튼(2번 핀)을 누르고 있으면 loop()가 delay(5000)에서 "멈춘 것처럼" 동작한다.
 *      - 이때 wdt_reset()이 2초 넘게 호출되지 않으므로 WDT 타임아웃이 발생한다.
 *      - MCU가 자동으로 리셋되고, 시리얼 모니터에 "정상 시작"이 다시 출력되며
 *        LED 깜빡임도 처음부터 다시 시작된다. => 리셋이 실제로 일어났다는 증거.
 *   3. 버튼을 누르지 않으면 정상적으로 계속 동작한다 (wdt_reset()이 계속 호출됨).
 *
 * 배선:
 *   - LED: 13번 핀 (Uno 보드 내장 LED로도 충분)
 *   - 버튼: 2번 핀 - GND (INPUT_PULLUP 사용, 누르면 LOW)
 *
 * 선행 학습: 05_Interrupts(volatile), 01_Digital_IO(Button) 를 먼저 보면 이해가 쉽다.
 * 다음 단계: 20_Sleep_delay, 30_SleepTest1 (Sleep 모드와 결합한 저전력 응용)
 */

#include <avr/wdt.h>

#define LED_PIN     13
#define BUTTON_PIN  2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println(F("정상 시작: Watchdog_Basic 실행"));

  // 워치독 타이머를 2초로 설정하여 켠다.
  // 이후 2초 안에 wdt_reset()이 호출되지 않으면 MCU가 리셋된다.
  wdt_enable(WDTO_2S);
}

void loop() {
  // "나는 살아있다"는 신호. 이 호출이 2초 이상 끊기면 리셋된다.
  wdt_reset();

  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);

  if (digitalRead(BUTTON_PIN) == LOW) {
    // 버튼을 누르면 일부러 5초간 멈춘 것처럼 동작시킨다.
    // 이 delay() 동안 wdt_reset()이 호출되지 않으므로,
    // 2초 뒤 워치독이 타임아웃되어 MCU가 스스로 리셋된다.
    Serial.println(F("정지 시뮬레이션 시작 (5초 대기, 2초 후 WDT 리셋 예상)"));
    delay(5000);
    // 이 줄은 실행되지 않는다 (그 전에 리셋됨) - 참고용
    Serial.println(F("여기까지 도달했다면 워치독이 리셋을 못한 것"));
  }
}
