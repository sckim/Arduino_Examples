# 03. Serial Communication

## 🎯 학습 목표
*   아두이노와 PC 간에 데이터를 주고받는 방법을 배웁니다.
*   시리얼 모니터를 사용하여 센서 값을 확인하고 프로그램을 디버깅하는 능력을 기릅니다.

## 💻 주요 함수
*   `Serial.begin(baudrate)`: 시리얼 통신 초기화 (보통 9600 사용)
*   `Serial.print(value)` / `Serial.println(value)`: 데이터를 PC로 전송
*   `Serial.available()`: 수신된 데이터가 있는지 확인
*   `Serial.read()`: 수신된 데이터를 읽음
