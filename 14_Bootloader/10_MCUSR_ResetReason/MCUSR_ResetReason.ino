/*
 * MCUSR_ResetReason
 * -----------------
 * 부트로더는 스케치가 시작되기 전에 "MCU가 왜 리셋됐는가"를 확인해서
 * 동작을 결정한다 (예: 워치독 리셋이면 부트로더 진입, 전원 리셋이면 바로 스케치 실행 등).
 * 이 정보는 MCUSR(MCU Status Register) 레지스터에 담겨 있다.
 *
 * 주의: 부트로더(또는 Arduino의 core 초기화 코드)가 시작되자마자 MCUSR을
 *       읽고 지워버리기 때문에, 스케치의 setup()에서 MCUSR을 직접 읽으면
 *       이미 0으로 지워져 있을 수 있다. 그래서 이 예제는 부트로더보다
 *       먼저 실행되는 초기화 함수(.init3 섹션)에서 값을 미리 저장해둔다.
 *
 * 관찰 방법:
 *   1. 시리얼 모니터(9600bps)를 열고 리셋 버튼을 눌러본다  -> External Reset
 *   2. 전원을 껐다 켜본다                                 -> Power-on Reset
 *   3. 15_WatchDog/10_Watchdog_Basic 예제를 올려서 워치독이
 *      타임아웃되게 만들어본다                             -> Watchdog Reset
 *   각 상황마다 아래 출력이 달라지는 것을 확인한다.
 *
 * 선행 학습: 15_WatchDog/10_Watchdog_Basic
 * 다음 단계: 20_Read_Signature_Fuses, 30_optiboot
 */

#include <avr/wdt.h>

// 부트로더가 MCUSR을 지우기 전에 값을 가로채 저장한다.
uint8_t resetFlags __attribute__((section(".noinit")));

void getResetFlags(void) __attribute__((naked)) __attribute__((used)) __attribute__((section(".init0")));
void getResetFlags(void) {
  __asm__ __volatile__ ("mov %0, r2\n" : "=r" (resetFlags) :);
}

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println(F("=== MCUSR Reset Reason ==="));
  Serial.print(F("MCUSR raw = 0b"));
  Serial.println(resetFlags, BIN);

  if (resetFlags & (1 << WDRF))  Serial.println(F("-> Watchdog Reset (WDRF)"));
  if (resetFlags & (1 << BORF))  Serial.println(F("-> Brown-out Reset (BORF)"));
  if (resetFlags & (1 << EXTRF)) Serial.println(F("-> External Reset (리셋 버튼/EXTRF)"));
  if (resetFlags & (1 << PORF))  Serial.println(F("-> Power-on Reset (PORF)"));
  if (resetFlags == 0)           Serial.println(F("-> (플래그 없음: 이미 다른 코드에서 지워졌을 수 있음)"));
}

void loop() {
  // 관찰용 예제이므로 loop에서는 아무 것도 하지 않는다.
}
