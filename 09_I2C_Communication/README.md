# 09. I2C Communication

## 🎯 학습 목표
*   **I2C (Inter-Integrated Circuit)** 통신 프로토콜의 원리를 배우고, SDA/SCL 두 선으로 여러 장치를 연결하는 법을 익힙니다.

## 🛠 주요 장치
*   **LCD (I2C 모듈)**: 16x2 캐릭터 LCD (`30_LCD_I2Cm`)
*   **RTC (DS1307)**: 실시간 시계 모듈 (`40_DS1307`)
*   **온도(LM75), IO확장(PCF8574), 펄스옥시메터(MAX30105), 가속도계(ADXL345)**: 대표 센서/장치 하나씩

심화·중복 예제(IMU 캘리브레이션 시리즈, 특정 상용 모듈 등)는 `15_Projects/09_I2C_Communication_Extended/`에 있습니다.

## 💻 주요 라이브러리/함수
*   `Wire.h`: 아두이노 표준 I2C 라이브러리
*   **I2C Scanner**: 연결된 장치의 주소(Address)를 찾는 법

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-21. 예제 9개.

| 폴더 | 소스 | 회로도 |
|---|---|---|
| `10_i2c_scanner` | `i2c_scanner.ino` | 있음 (Proteus) |
| `20_I2C_write` | `I2C_write.ino` | — |
| `30_LCD_I2Cm` | `LCD_I2Cm.ino` | 있음 (Proteus) |
| `40_DS1307` | `DS1307.ino` | — |
| `41_RTC_TimeSet.ino` | 단일 파일 | — |
| `50_LM75` | `LM75_test.ino` | — |
| `60_PCF8574` | `PCF8574.ino` | 있음 (Proteus) |
| `70_MAX30105` | `MAX30105.ino` | — |
| `80_ADXL345` | `ADXL345.cpp` | — |

> ℹ️ 기기별 심화/중복 변형 31개(LCD 변형, 자력계·자이로, MPU9150 캘리브레이션 시리즈 등)는 `15_Projects/09_I2C_Communication_Extended/`로 옮겼습니다.

<!-- AUTO-INDEX:END -->
