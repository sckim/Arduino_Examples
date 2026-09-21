/*
 * Power_Management
 * -----------------
 * 앞의 두 개념, Watchdog Timer(안정성)와 Sleep Mode(절전)를 결합해서
 * "실전 저전력 설계"의 기본 패턴을 보여준다.
 *
 * 개념:
 *   - 10_Watchdog_Basic에서는 WDT를 "리셋"용으로 썼다 (wdt_reset()을 못하면 재부팅).
 *   - 여기서는 WDT를 정반대 목적, 즉 "잠든 MCU를 주기적으로 깨우는 알람 타이머"로
 *     사용한다. WDIE(인터럽트 모드)를 켜면, 타임아웃 시 리셋 대신 인터럽트만
 *     발생시키고 MCU는 그 다음 줄부터 계속 실행된다.
 *   - 즉, "Power-down Sleep으로 대부분의 시간을 절전 상태로 보내다가,
 *     WDT 인터럽트로 깨어나서 짧게 일할 일을 하고 다시 잠든다"는
 *     배터리 구동 센서 노드의 기본 동작 패턴이다.
 *
 * 동작:
 *   - 약 8초(WDTO_8S)마다 깨어나서 LED를 한 번 깜빡이고 "깨어남" 메시지를
 *     출력한 뒤, 다시 Power-down Sleep으로 들어간다.
 *   - 평균 소비 전류는 "8초 중 아주 짧은 순간만 켜져있는" 수준으로 줄어든다.
 *
 * 선행 학습: 10_Watchdog_Basic, 20_Sleep_delay, 30_SleepTest1
 * 참고: 20_Sleep_delay는 WDT를 보정된 "딜레이 시계"로 쓰지만, 이 예제는
 *       WDT를 순수한 "깨우기 알람"으로만 쓰는 더 단순한 버전이다.
 */

#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>

#define LED_PIN 13

volatile bool wdtWokeUp = false;

// WDT 인터럽트 모드 설정: 리셋하지 않고 인터럽트만 발생시킨다.
void setupWatchdogInterrupt() {
  cli();
  wdt_reset();
  MCUSR &= ~(1 << WDRF);
  WDTCSR |= (1 << WDCE) | (1 << WDE);      // 설정 변경을 위한 타이밍 시퀀스 시작
  WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); // 인터럽트 모드, 약 8초
  sei();
}

// WDT 타임아웃 -> 리셋 대신 이 인터럽트만 발생하고 MCU가 깨어난다.
ISR(WDT_vect) {
  wdtWokeUp = true;
}

void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  ADCSRA &= ~(1 << ADEN);   // ADC 끄기 (절전)
  power_all_disable();     // 사용하지 않는 주변장치 클럭 끄기 (절전)

  sleep_enable();
  sleep_bod_disable();      // BOD(전압 감시) 잠깐 끄기 - 소비전류 추가 절감
  sleep_cpu();               // 여기서 실제로 잠든다 (WDT 인터럽트가 깨울 때까지)
  sleep_disable();

  power_all_enable();
  ADCSRA |= (1 << ADEN);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  delay(200);
  Serial.println(F("=== Power_Management 시작 ==="));
  Serial.println(F("8초마다 깨어나서 LED를 한 번 깜빡입니다."));

  setupWatchdogInterrupt();
}

void loop() {
  goToSleep();

  // 여기부터는 WDT 인터럽트로 깨어난 뒤 실행되는 코드
  if (wdtWokeUp) {
    wdtWokeUp = false;
    Serial.println(F("깨어남! (WDT 인터럽트)"));
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
  }
  // 다시 loop()로 돌아가 goToSleep()이 호출되며 곧바로 다시 잠든다.
}
