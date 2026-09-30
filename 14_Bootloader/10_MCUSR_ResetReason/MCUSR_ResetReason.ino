/*
 * MCUSR_ResetReason
 * -----------------
 * MCU 가 "왜 리셋되었는지"를 MCUSR 레지스터로 확인한다.
 * MCUSR(MCU Status Register)에는 리셋 원인이 비트로 남는다. 부트로더도 이 값을 보고 할 일을 정한다. 우노의 Optiboot 4.4 는 외부 리셋(EXTRF)일 때만
 * 부트로더에 머물고, 나머지 리셋이면 곧바로 스케치로 넘어간다.
 *
 * 주의 1: 우노의 Optiboot 4.4 는 시작하자마자 MCUSR 을 읽고 0 으로 지운다. 넘겨 주지는 않는다.
 *         그래서 기본 우노에서는 스케치가 보는 MCUSR 이 늘 0 이다.
 *         Optiboot 4.6 부터는 지운 값을 레지스터 r2 에 넣어 넘겨 준다(그 판을 구운 보드에서만).
 * 주의 2: 리셋은 r0~r31 을 초기화한다는 보장이 없다. r2 를 채워 주는 부트로더가 없으면
 *         r2 에는 리셋 전 값이 남는다. 그래서 리셋 원인은 MCUSR 로만 판단하고 r2 는 참고로 찍는다.
 * 이 예제는 main() 보다 먼저 실행되는 .init0(r2), .init3(MCUSR) 에서 두 값을 저장해 둔다.
 *
 * 관찰 방법:
 *   1. 시리얼 모니터(9600bps)를 열고 리셋 버튼을 눌러본다  -> External Reset
 *   2. 전원을 껐다 켜본다                                 -> Power-on Reset
 *   3. 13_WatchDog_Sleep/10_Watchdog_Basic 예제를 올려서 워치독이
 *      타임아웃되게 만들어본다                             -> Watchdog Reset
 *   셋이 갈려 보이는 것은 ISP 로 올리고 BOOTRST 를 끈(High 퓨즈 0xDF) 보드다.
 *   기본 우노에서는 셋 다 "플래그 없음"이다. (교재 22장)
 *
 * 선행 학습: 13_WatchDog_Sleep/10_Watchdog_Basic
 * 다음 단계: 20_Read_Signature_Fuses, 30_optiboot
 */

#include <avr/wdt.h>

// .noinit : C 초기화 코드가 0 으로 지우지 않는 영역
uint8_t resetFlagsR2 __attribute__((section(".noinit")));
uint8_t resetFlags __attribute__((section(".noinit")));

// .init0 : 리셋 직후 가장 먼저 실행된다. r2 를 가로챈다 (Optiboot 4.6 이상에서만 리셋 원인이다).
void getResetFlagsR2(void) __attribute__((naked)) __attribute__((used)) __attribute__((section(".init0")));
void getResetFlagsR2(void) {
  __asm__ __volatile__ ("mov %0, r2\n" : "=r" (resetFlagsR2) :);
}

// .init3 : setup() 전. MCUSR 을 직접 읽고 지운다. 워치독 리셋 뒤의 끝없는 리셋도 막는다.
void getResetFlags(void) __attribute__((naked)) __attribute__((used)) __attribute__((section(".init3")));
void getResetFlags(void) {
  resetFlags = MCUSR;
  MCUSR = 0;
  wdt_disable();
}

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println(F("=== MCUSR Reset Reason ==="));
  Serial.print(F("MCUSR raw = 0b"));
  Serial.println(resetFlags, BIN);
  Serial.print(F("r2 (Optiboot 4.6 이상에서만 의미) = 0b"));
  Serial.println(resetFlagsR2, BIN);

  if (resetFlags & (1 << WDRF))  Serial.println(F("-> Watchdog Reset (WDRF)"));
  if (resetFlags & (1 << BORF))  Serial.println(F("-> Brown-out Reset (BORF)"));
  if (resetFlags & (1 << EXTRF)) Serial.println(F("-> External Reset (리셋 버튼/EXTRF)"));
  if (resetFlags & (1 << PORF))  Serial.println(F("-> Power-on Reset (PORF)"));
  if (resetFlags == 0)           Serial.println(F("-> (플래그 없음: 부트로더가 이미 지웠다. 우노의 Optiboot 4.4 가 그렇다)"));
}

void loop() {
  // 관찰용 예제이므로 loop에서는 아무 것도 하지 않는다.
}
