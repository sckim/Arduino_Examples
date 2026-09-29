/*=======================================================*/
// PCInterrupt_Count : 핀 체인지 인터럽트로 2·3번 아닌 핀에서 인터럽트를 쓴다
//
// 교재 5장 실습 5-3. 외부 인터럽트는 2·3번 핀에서만 된다. 그 밖의 핀에서
// 인터럽트를 쓰려면 핀 체인지 인터럽트를 쓴다. 대가가 셋이다.
//   ① 포트(그룹) 단위로만 켜진다
//   ② 에지를 고를 수 없다. "값이 바뀌면" 뿐이다
//   ③ 어느 핀이 바뀌었는지 ISR 안에서 직접 확인해야 한다
//
// 아두이노가 이 기능에는 함수를 주지 않는다. 그래서 레지스터를 직접 쓴다.
//   PCMSK0/1/2 : 그룹 안에서 감시할 핀을 고르는 마스크
//   PCICR      : 그룹을 켠다 (PCIE0 = 포트 B, PCIE1 = 포트 C, PCIE2 = 포트 D)
//   PCIFR      : 플래그. 1 을 써서 지운다
//   SREG 의 I  : 전체 허용. 그룹 비트와 둘 다 1 이어야 걸린다 (아두이노가 이미 켜 둔다)
//
// 연결 (둘 다 INPUT_PULLUP 이므로 누르면 LOW)
//   8번 핀(PB0) - 버튼 - GND
//   9번 핀(PB1) - 버튼 - GND
// 8·9번은 둘 다 포트 B 이므로 PCINT0 벡터 하나를 공유한다.
// 그래서 ISR 안에서 어느 쪽이 바뀌었는지 읽어서 가려낸다.
//
// 선행 학습 : 22_Interrupt_Modes      다음 단계 : 06_Timers_Counters
/*=======================================================*/
#include <Arduino.h>

const byte BTN_A = 8;        // PB0
const byte BTN_B = 9;        // PB1

volatile unsigned long countA = 0;
volatile unsigned long countB = 0;
volatile byte prevB = 0;     // 직전 포트 B 값. 어느 핀이 바뀌었는지 가리는 데 쓴다

// 감시할 핀 하나를 핀 체인지 인터럽트에 등록한다. 여러 번 불러도 된다.
// digitalPinToPCMSK(pin) 은 그 핀이 속한 PCMSK 레지스터의 주소를 돌려준다.
// 레지스터가 메모리 번지이므로 * 로 역참조해 값을 쓴다.
void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));   // 핀을 마스크에 넣는다
  PCIFR |= bit(digitalPinToPCICRbit(pin));                     // 남아 있던 플래그를 지운다
  PCICR |= bit(digitalPinToPCICRbit(pin));                     // 그룹을 켠다
}

// 이름을 내가 고르는 것이 아니다. 벡터 테이블 이름에 맞춰 avr-gcc 가 정해 둔 이름이다.
// PCINT0_vect = 포트 B 그룹(D8~D13).
ISR(PCINT0_vect) {
  byte now = PINB;                 // 포트 B 여덟 핀을 한 번에 읽는다 (3장의 PINx)
  byte changed = now ^ prevB;      // 바뀐 비트만 1 이 된다 (3장의 XOR)
  prevB = now;

  if (changed & bit(PB0)) countA++;   // 8번이 바뀌었다
  if (changed & bit(PB1)) countB++;   // 9번이 바뀌었다
}

void setup() {
  Serial.begin(9600);
  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);

  prevB = PINB;                    // 시작 값을 기억해 둔다
  pciSetup(BTN_A);
  pciSetup(BTN_B);

  Serial.println(F("=== PCInterrupt_Count ==="));
  Serial.println(F("8번과 9번 버튼을 눌러 보세요. 한 벡터를 둘이 나눠 씁니다."));
}

void loop() {
  static unsigned long lastA = 0, lastB = 0;

  if (countA != lastA || countB != lastB) {
    lastA = countA;
    lastB = countB;
    Serial.print(F("8번 변화 "));
    Serial.print(countA);
    Serial.print(F(" / 9번 변화 "));
    Serial.println(countB);
  }
}
