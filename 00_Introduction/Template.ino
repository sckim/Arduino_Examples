/*
 * Project Name: [이곳에 프로젝트 이름을 적으세요]
 * Description: [프로젝트의 기능과 목적을 간단히 설명하세요]
 * Author: [작성자 이름]
 * Date: 2026-03-29
 * 
 * Circuit:
 * - Pin [X]: [연결된 부품 및 설명]
 * - Pin [Y]: [연결된 부품 및 설명]
 */

// 1. 전처리기 및 매크로 정의 (Constants)
const int LED_PIN = 13; 

// 2. 전역 변수 (Global Variables)
int counter = 0;

void setup() {
  // 3. 초기화 (Initialization)
  Serial.begin(9600);    // 시리얼 통신 시작
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("System Ready!");
}

void loop() {
  // 4. 주 반복 루프 (Main Logic)
  
}

// 5. 사용자 정의 함수 (Helper Functions)
void blinkLED(int duration) {
  digitalWrite(LED_PIN, HIGH);
  delay(duration);
  digitalWrite(LED_PIN, LOW);
  delay(duration);
}
