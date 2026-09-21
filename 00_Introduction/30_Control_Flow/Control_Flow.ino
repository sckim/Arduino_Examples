/*
 * Control_Flow
 * -------------
 * C의 기본 제어문: if/else, for, while, do-while, switch.
 *
 * 아두이노의 loop() 함수 자체가 사실 "무한 while문" 하나라는 것을 기억하면
 * 이후 모든 예제(01_Digital_IO ~)가 결국 이 제어문들의 조합이라는 걸 알 수 있다.
 *
 * 선행 학습: 20_Operators (for문의 비교/증감에 비트연산이 섞여 나올 수 있음)
 * 다음 단계: 40_Functions
 */

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println(F("=== if / else if / else ==="));
  for (int score = 0; score <= 100; score += 40) {
    Serial.print(F("score=")); Serial.print(score); Serial.print(F(" -> "));
    if (score >= 90) {
      Serial.println(F("A"));
    } else if (score >= 70) {
      Serial.println(F("B"));
    } else {
      Serial.println(F("C"));
    }
  }

  Serial.println();
  Serial.println(F("=== for문: 0부터 4까지 ==="));
  for (int i = 0; i < 5; i++) {
    Serial.print(i);
    Serial.print(' ');
  }
  Serial.println();

  Serial.println();
  Serial.println(F("=== while문: 조건이 참인 동안 반복 (2의 거듭제곱, 100 넘으면 종료) ==="));
  int v = 1;
  while (v <= 100) {
    Serial.print(v);
    Serial.print(' ');
    v *= 2;
  }
  Serial.println();

  Serial.println();
  Serial.println(F("=== do-while문: 최소 한 번은 실행됨 ==="));
  int n = 0;
  do {
    Serial.print(F("실행됨 (n="));
    Serial.print(n);
    Serial.println(F(")"));
    n++;
  } while (n < 3);

  Serial.println();
  Serial.println(F("=== switch-case: 여러 경우를 값으로 분기 ==="));
  for (int mode = 0; mode < 4; mode++) {
    Serial.print(F("mode=")); Serial.print(mode); Serial.print(F(" -> "));
    switch (mode) {
      case 0:
        Serial.println(F("정지"));
        break;
      case 1:
        Serial.println(F("느림"));
        break;
      case 2:
        Serial.println(F("보통"));
        break;
      default:              // case에 없는 나머지 모든 값
        Serial.println(F("빠름"));
        break;              // break를 빼먹으면 아래 case까지 계속 실행되니 주의!
    }
  }
}

void loop() {
}
