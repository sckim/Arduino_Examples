/*=======================================================*/
// Servo_Bitbang : 서보 신호를 GPIO 로 직접 만든다
//
// 교재 7장 실습 7-3. 서보는 PWM 신호 자체를 입력으로 받는다. 그런데
// analogWrite 의 주기(약 2 ms)는 서보가 원하는 주기(15~25 ms)와 맞지 않는다.
// 그래서 여기서는 핀을 손으로 올리고 내려 펄스를 만든다.
//
// 핵심 : 받는 쪽은 그 펄스를 하드웨어가 만들었는지 GPIO 가 만들었는지 모른다.
// 규칙만 맞으면 된다. 그래서 analogWrite 가 되는 핀이 아니어도 상관없다.
//
// 서보 신호 규격
//   주기      : 15~25 ms (정밀하지 않다. 이 범위면 동작한다)
//   High 폭   : 약 0.5 ms -> 0도,  1.5 ms -> 90도,  2.5 ms -> 180도
//   제품에 따라 0.2~2.2 ms 인 것도 있다. 최소·최대 폭은 직접 찾아 보정한다.
//
// 연결
//   서보 빨강 : 5V     (전류가 크면 외부 전원을 쓴다)
//   서보 갈색 : GND
//   서보 노랑 : 9번 핀 (analogWrite 를 쓰지 않으므로 8번 같은 일반 핀도 된다)
//   가변저항 와이퍼 : A0
//
// 엄밀하게는 Low 시간 = 20 ms - High 시간이어야 주기가 고정된다. High 가 짧아
// 오차가 10 % 정도라서 이 예제는 Low 를 20 ms 로 고정했다. 그래도 동작한다.
// delayMicroseconds 는 약 16,383 µs 까지만 정확하므로 20 ms 대기는 delay(20) 을 쓴다.
//
// 선행 학습 : 07_PWM/16_PWM_ADC      다음 단계 : 10_Servo1 (라이브러리판)
/*=======================================================*/
#include <Arduino.h>

const uint8_t SERVO = 9;
const uint8_t POT   = A0;

// 이 제품의 최소·최대 펄스 폭. 각도가 안 맞으면 이 두 값을 보정한다.
const int PULSE_MIN = 200;    // µs, 0도
const int PULSE_MAX = 2200;   // µs, 180도

// 펄스 한 발을 내보낸다
void sendPulse(int widthUs)
{
  digitalWrite(SERVO, HIGH);
  delayMicroseconds(widthUs);
  digitalWrite(SERVO, LOW);
  delay(20);                  // 다음 펄스까지 약 20 ms 쉰다
}

void setup()
{
  pinMode(SERVO, OUTPUT);
  digitalWrite(SERVO, LOW);   // 출력을 정해진 상태로 시작한다
  Serial.begin(9600);

  // 0도에서 180도까지, 다시 0도로 한 번 쓸어 본다
  for (int w = PULSE_MIN; w <= PULSE_MAX; w += 10) sendPulse(w);
  for (int w = PULSE_MAX; w >= PULSE_MIN; w -= 10) sendPulse(w);
}

void loop()
{
  int adc = analogRead(POT);
  int width = map(adc, 0, 1023, PULSE_MIN, PULSE_MAX);

  sendPulse(width);

  static int prev = -1;
  if (abs(width - prev) > 20) {        // 조금 움직인 것은 찍지 않는다
    Serial.print("ADC = ");
    Serial.print(adc);
    Serial.print("   pulse = ");
    Serial.print(width);
    Serial.println(" us");
    prev = width;
  }
}
