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

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-20. 예제 폴더 34개, 외부 라이브러리 4개, 회로도 보유 6개, `Project Backups` 백업본 8개.

| 폴더 | 소스 | Proteus 회로도 |
|---|---|---|
| `ADXL345` | 4개 파일 | — |
| `AccelCal9150` | `AccelCal9150.ino` | — |
| `AccelCal9150chooseSensorSingleAddr3sensors` | `AccelCal9150chooseSensorSingleAddr3sensors.ino` | — |
| `DS1307` | `DS1307.ino` | — |
| `ENS210-master` | 10개 파일 · 외부 라이브러리 | — |
| `Grove_LCD_RGB_Backlight-master` | 15개 파일 · 외부 라이브러리 | — |
| `HMC` | 3개 파일 · 외부 라이브러리 | — |
| `HMC5843` | `HMC5843.ino`, `I2C.ino` | — |
| `I2C_write` | 1개 파일 | — |
| `ICM42670P_MAX3010x` | `ICM42670P_MAX3010x.ino`, `License.ino` | — |
| `ICM42670P_S` | `ICM42670P_S.ino` | — |
| `ICM42760P` | `ICM42760P.ino` | — |
| `ITG3200_Basic_Example` | `ITG3200_Basic_Example.ino` | — |
| `LCD` | `LCD.ino` | `AVR328P_LCD_4bits.pdsprj`; `Arduino 328.pdsprj` |
| `LCD_I2Cm` | 2개 파일 | `AVR328P_LCD_4bits.pdsprj` (백업 3) |
| `LM75` | `LM75_test.ino` | — |
| `MAX30100` | `MAX30100.ino` | — |
| `MAX30105` | `MAX30105.ino` | — |
| `MPU9150` | 20개 파일 | — |
| `MPU9150_3chs` | `MPU9150_3chs.ino` | — |
| `MPU9150_3chs_AccCal` | `MPU9150_3chs_AccCal.ino` | — |
| `MPU9150_3chs_MagCal` | `MPU9150_3chs_MagCal.ino` | — |
| `MPU9150_DMP` | `MPU6050_DMP6.ino` | — |
| `Mag` | `Mag.ino` | — |
| `Mag3110` | `Mag3110.ino` | — |
| `MagCal9150` | `MagCal9150.ino` | — |
| `PCF8574` | `PCF8574.ino` | `AVR328P_PCF8574.pdsprj` (백업 1) |
| `PCF8575` | `PCF8575.ino` | `AVR328P_PCF8574.pdsprj` (백업 2) |
| `PCF8575_w` | `PCF8574.ino` | `AVR328P_PCF8574.pdsprj` (백업 1) |
| `Sensor_Stick` | `I2C.ino`, `Output.ino` | — |
| `Sensor_Stick_v1` | `I2C.pde`, `Output.pde` | — |
| `Sensor_Stick_v2` | `I2C.ino`, `Output.ino` | — |
| `TWI` | `DigitalPotControl.ino` | — |
| `Weather_shield` | `Weather_shield.ino` | — |
| `i2c_scanner` | 1개 파일 | `AVR328P_PCF8574.pdsprj` (백업 1) |
| `itg-3200` | 9개 파일 · 외부 라이브러리 | — |
| `mag13_02_02` | `mag13_02_02.ino` | — |
| `quat3sensors9150_waitToSend` | `quat3sensors9150_waitToSend.ino` | — |

<!-- AUTO-INDEX:END -->
