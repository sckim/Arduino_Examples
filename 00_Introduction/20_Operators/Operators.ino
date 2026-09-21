/*
 * Operators
 * ----------
 * C의 기본 연산자와, 임베디드에서 특히 중요한 "비트 연산자"를 다룬다.
 *
 * 나중에 레지스터를 직접 다루는 예제들(예: 06_Timers_Counters, 07_PWM)에서
 * `TCCR0A |= (1 << WGM01);` 같은 코드를 보게 되는데, 이건 결국 여기서
 * 배우는 비트 연산자 조합일 뿐이다. 지금 이 문법을 확실히 익혀두면
 * 나중에 레지스터 코드가 훨씬 쉽게 읽힌다.
 *
 * 선행 학습: 10_Data_Types
 * 다음 단계: 30_Control_Flow
 */

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println(F("=== 산술/비교/논리 연산자 (기본) ==="));
  int a = 7, b = 2;
  Serial.print(F("a=7, b=2 -> a+b=")); Serial.print(a + b);
  Serial.print(F(", a-b="));  Serial.print(a - b);
  Serial.print(F(", a*b="));  Serial.print(a * b);
  Serial.print(F(", a/b="));  Serial.print(a / b);   // 정수 나눗셈: 소수점 버림 -> 3
  Serial.print(F(", a%b="));  Serial.println(a % b);  // 나머지 -> 1

  Serial.println();
  Serial.println(F("=== 비트 연산자 (임베디드의 핵심!) ==="));
  uint8_t reg = 0b00000000;  // 8개의 핀 상태를 흉내낸 가상의 "레지스터"
  Serial.print(F("초기값        : 0b")); Serial.println(reg, BIN);

  // 1. OR( | )로 특정 비트를 1로 "켠다" (Set bit) - 다른 비트는 건드리지 않음
  reg = reg | (1 << 3);      // 3번 비트를 켠다
  Serial.print(F("3번 비트 SET  : 0b")); Serial.println(reg, BIN);

  // 2. AND(&)와 NOT(~)으로 특정 비트를 0으로 "끈다" (Clear bit)
  reg = reg & ~(1 << 3);      // 3번 비트를 끈다
  Serial.print(F("3번 비트 CLEAR: 0b")); Serial.println(reg, BIN);

  // 3. XOR(^)로 특정 비트를 "토글"한다 (Toggle bit) - 켜져있으면 끄고, 꺼져있으면 켠다
  reg = reg ^ (1 << 5);
  Serial.print(F("5번 비트 TOGGLE(1st): 0b")); Serial.println(reg, BIN);
  reg = reg ^ (1 << 5);
  Serial.print(F("5번 비트 TOGGLE(2nd): 0b")); Serial.println(reg, BIN);

  // 4. Shift(<<, >>)로 자리를 이동한다. "1 << n" 은 "n번 비트만 1인 값"을 만드는 관용구.
  Serial.print(F("1 << 4        : 0b")); Serial.println(1 << 4, BIN);
  Serial.print(F("0b10000 >> 2  : 0b")); Serial.println(0b10000 >> 2, BIN);

  Serial.println();
  Serial.println(F("=== 특정 비트가 켜져있는지 확인하기 ==="));
  reg = 0b00101000;
  Serial.print(F("reg = 0b00101000, 3번 비트가 켜져있나? -> "));
  Serial.println((reg & (1 << 3)) ? F("켜짐(1)") : F("꺼짐(0)"));
}

void loop() {
}
