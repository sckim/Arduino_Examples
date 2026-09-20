# 01. Digital IO

## 🎯 학습 목표
*   아두이노의 디지털 핀을 사용하여 외부 장치(LED)를 제어하고 입력(Button)을 읽는 방법을 배웁니다.
*   디지털 신호의 High(5V/3.3V)와 Low(0V) 개념을 이해합니다.

## 🛠 주요 부품
*   LED, 저항(220~330Ω), 택트 스위치(Button)

## 💻 주요 함수
*   `pinMode(pin, mode)`: 핀을 입력 또는 출력으로 설정
*   `digitalWrite(pin, value)`: 디지털 핀에 High/Low 출력
*   `digitalRead(pin)`: 디지털 핀의 상태(High/Low)를 읽음
*   `delay(ms)`: 지정된 시간(밀리초) 동안 대기
