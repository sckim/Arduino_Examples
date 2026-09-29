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
<!-- gen_index.py가 만든다. 손으로 고치지 마세요. 기준일 2026-09-29 -->

### 📂 예제 (8개)

| 폴더 | 내용 | 소스 | 줄 | PlatformIO | 회로도 | Wokwi | README |
|---|---|---:|---:|:---:|:---:|:---:|:---:|
| `10_i2c_scanner` |  | 2 | 89 | ✓ | ✓ |  |  |
| `20_I2C_write` |  | 1 | 46 |  |  |  |  |
| `30_LCD_I2Cm` |  | 2 | 27 | ✓ | ✓ |  |  |
| `40_DS1307` |  | 1 | 38 |  |  |  |  |
| `50_LM75` | you can redistribute it and/or modify | 2 | 122 |  |  |  |  |
| `60_PCF8574` | PCF8574.cpp | 2 | 184 |  | ✓ |  |  |
| `70_MAX30105` | Output all the raw Red/IR/Green readings | 15 | 1570 |  |  |  |  |
| `80_ADXL345` | :ADXL345(){ | 1 | 144 |  |  |  |  |

<!-- AUTO-INDEX:END -->
