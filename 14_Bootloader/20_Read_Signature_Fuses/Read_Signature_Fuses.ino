/*
 * Read_Signature_Fuses
 * ---------------------
 * 부트로더가 어떻게 설치/동작하는지는 결국 칩의 "퓨즈 비트(Fuse Bits)"가
 * 결정한다. 특히 BOOTRST 퓨즈는 "리셋 후 부트로더로 점프할지, 스케치로 바로
 * 갈지"를 정하고, BOOTSZ 퓨즈는 "부트로더가 플래시의 몇 바이트를 차지할지"를
 * 정한다. 이 예제는 그 값을 안전하게(읽기 전용) 확인해본다.
 *
 * 읽기 전용이라 브릭(Brick) 위험이 없다. 절대 쓰기(SPM write)는 하지 않는다.
 *
 * 참고 - ATmega328P 기준:
 *   - Signature: 0x1E 0x95 0x0F  (device signature, 데이터시트로 칩 종류 확인)
 *   - Optiboot(30_optiboot)는 보통 BOOTSZ=512words(1KB)로 설정해서 사용한다.
 *
 * 선행 학습: 10_MCUSR_ResetReason
 * 다음 단계: 30_optiboot (실제 부트로더 소스 코드)
 */

#include <avr/boot.h>
#include <avr/io.h>

void printFuse(const char* name, uint8_t value) {
  Serial.print(name);
  Serial.print(F(" = 0x"));
  if (value < 0x10) Serial.print('0');
  Serial.println(value, HEX);
}

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println(F("=== Device Signature ==="));
  uint8_t sig0, sig1, sig2;
  cli();
  sig0 = boot_signature_byte_get(0x0000);
  sig1 = boot_signature_byte_get(0x0002);
  sig2 = boot_signature_byte_get(0x0004);
  sei();
  Serial.print(F("Signature = 0x"));
  Serial.print(sig0, HEX); Serial.print(' ');
  Serial.print(sig1, HEX); Serial.print(' ');
  Serial.println(sig2, HEX);
  Serial.println(F("(ATmega328P 정상값: 1E 95 0F)"));

  Serial.println();
  Serial.println(F("=== Fuse Bits ==="));
  cli();
  uint8_t lowFuse  = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
  uint8_t highFuse = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
  uint8_t extFuse   = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
  uint8_t lockBits  = boot_lock_fuse_bits_get(GET_LOCK_BITS);
  sei();

  printFuse("Low Fuse     ", lowFuse);
  printFuse("High Fuse    ", highFuse);
  printFuse("Extended Fuse", extFuse);
  printFuse("Lock Bits    ", lockBits);

  Serial.println();
  Serial.print(F("BOOTRST (부트로더로 시작하는지) = "));
  Serial.println((highFuse & 0x01) ? F("0 -> 스케치로 직접 시작 (bit=1)") : F("부트로더로 먼저 진입 (bit=0)"));
}

void loop() {
  // 읽기 전용 관찰 예제
}
