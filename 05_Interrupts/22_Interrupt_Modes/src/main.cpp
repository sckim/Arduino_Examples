/*=======================================================*/
// Interrupt_Modes : 트리거 모드를 바꿔 보고, loop 가 멈추지 않는 것을 확인한다
//
// 교재 5장 실습 5-2. 두 가지를 눈으로 본다.
//   ① CHANGE / RISING / FALLING 이 각각 언제 걸리는가
//   ② 인터럽트가 걸리는 동안에도 loop 는 자기 일을 계속한다
//
// 연결 (버튼은 INPUT_PULLUP 이므로 누르면 LOW)
//   2번 핀(INT0) - 버튼 - GND      ->  12번 LED 를 토글한다
//   3번 핀(INT1) - 버튼 - GND      ->  11번 LED 를 토글한다
//   13번 LED                       ->  loop 가 500 ms 마다 토글한다 (보드 내장 LED)
//
// 13번 LED 가 계속 깜빡이는 것이 핵심이다. 버튼을 눌러 인터럽트가 걸려도
// 깜빡임이 멈추지 않는다. ISR 이 짧게 끝나고 곧 원래 자리로 돌아오기 때문이다.
//
// MODE 를 CHANGE -> RISING -> FALLING 으로 바꿔 올려 보면서 비교한다.
//   CHANGE  : 누를 때와 놓을 때 모두 (한 번 눌렀다 떼면 두 번 바뀐다)
//   FALLING : HIGH -> LOW,  즉 누를 때만
//   RISING  : LOW -> HIGH,  즉 놓을 때만
//
// 선행 학습 : 20_External_Interrupt      다음 단계 : 32_PCInterrupt_Count
/*=======================================================*/
#include <Arduino.h>

const byte BTN_A = 2;        // INT0
const byte BTN_B = 3;        // INT1
const byte LED_A = 12;
const byte LED_B = 11;

const int MODE = CHANGE;     // CHANGE / RISING / FALLING 으로 바꿔 본다

// ISR 과 loop 가 함께 쓰는 변수이므로 volatile 이 필요하다
volatile bool stateA = false;
volatile bool stateB = false;

// 쓰는 곳보다 위에 선언해 둔다. .cpp 는 프로토타입을 자동으로 만들어 주지 않는다.
void onA();
void onB();

void setup() {
  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_A), onA, MODE);
  attachInterrupt(digitalPinToInterrupt(BTN_B), onB, MODE);
}

void loop() {
  // 인터럽트와 상관없이 loop 는 자기 일을 계속한다
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  digitalWrite(LED_A, stateA ? HIGH : LOW);
  digitalWrite(LED_B, stateB ? HIGH : LOW);
}

void onA() { stateA = !stateA; }    // 짧게 끝낸다. 여기서 delay 나 Serial 을 쓰지 않는다
void onB() { stateB = !stateB; }
