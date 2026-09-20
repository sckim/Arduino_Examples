# 10. I2C Devices

## 🎯 학습 목표
*   **I2C (Inter-Integrated Circuit)** 통신 프로토콜의 원리를 배우고, SDA/SCL 두 선으로 여러 장치를 연결하는 법을 익힙니다.

## 🛠 주요 장치
*   **LCD (I2C 모듈)**: 16x2 또는 20x4 캐릭터 LCD
*   **RTC (DS1307)**: 실시간 시계 모듈
*   **가속도/자이로 센서 (MPU9150/IMU)**: 칩 내부 레지스터 데이터 읽기

## 💻 주요 라이브러리/함수
*   `Wire.h`: 아두이노 표준 I2C 라이브러리
*   **I2C Scanner**: 연결된 장치의 주소(Address)를 찾는 법
