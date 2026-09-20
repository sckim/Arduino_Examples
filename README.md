# 01. Arduino Projects (High-level Framework)

이 폴더는 ATmega328P 마이크로컨트롤러를 **아두이노 프레임워크(Arduino C++)**를 사용하여 빠르고 효율적으로 구현한 학습 예제 모음입니다. 복잡한 레지스터 설정을 추상화된 함수(`digitalWrite`, `analogRead` 등)로 처리하여 로직 구현에 집중할 수 있습니다.

## 🛠 개발 환경 (Development Environments)

이 프로젝트는 표준 아두이노 개발 환경과 현대적인 IDE 환경을 모두 지원합니다.

### 1. Arduino IDE (2.x 권장)
*   **특징**: 가장 대중적인 개발 환경, 간편한 보드 설정 및 시리얼 모니터 제공.
*   **사용법**: 각 폴더 내의 `.ino` 파일을 열어 보드(Arduino Uno)를 선택하고 업로드합니다.
*   **팁**: 라이브러리 매니저를 통해 필요한 외부 라이브러리를 쉽게 설치할 수 있습니다.

### 2. Visual Studio Code + Arduino Extension
*   **특징**: 강력한 코드 자동 완성, Git 통합, 전문적인 에디팅 환경.
*   **사용법**: VS Code에서 해당 폴더를 열고 하단 상태 표시줄에서 보드와 포트를 설정합니다.

---

## 📚 학습 커리큘럼 및 예제 안내 (15-Step Path)

아두이노의 생산성을 극대화하면서도 하드웨어의 원리를 놓치지 않도록 15단계로 구성되었습니다.
 
### 01. Digital I/O
*   기초 입출력 제어 (`Blink`, `Button`)
*   여러 개의 LED 제어 (`LED_bar`, `ShiftOut`)
 
### 02. Segment Display
*   7-세그먼트 표시 장치의 구동 원리 (`7Segments`, `Two_7Segments`)
*   타이머 인터럽트를 이용한 잔상 효과 구현 (`SegDisplayInt`)
 
### 03. Serial Comm
*   PC와의 데이터 송수신 기초 (`Serial`, `Serial_Input`)
*   다양한 데이터 형식 출력 (`ASCIITable`, `Print`)
 
### 04. ADC (Analog Input)
*   가변저항 등을 이용한 아날로그 전압 측정 (`AnalogReadSerial`, `ADC_multi`)
*   인터럽트 기반의 정밀한 ADC 샘플링 (`ADC_Int`)
 
### 05. Interrupts
*   외부 신호에 즉각 반응하는 외부 인터럽트 (`PCINT`, `PCInterrupt`)
*   인터럽트 서비스 루틴(ISR)의 작성 및 주의사항
 
### 06. Timers & Counters
*   하드웨어 타이머를 이용한 정확한 주기 생성 (`Timer_CTC`, `Timer_Overflow`)
*   고속 클록 출력 구현 (`Clock1MHz`, `Osc1MHz`)
 
### 07. PWM (Power Control)
*   LED 밝기 및 전압 제어 기초 (`AnalogWrite`)
*   타이머 레지스터를 직접 제어하는 고속 PWM (`Timer0_FastPWM`)
 
### 08. Motors
*   서보 모터의 각도 제어 (`RC_Servo`, `Servo1`)
*   스테핑 모터의 정밀 위치 제어 (`Stepper_motor`)
 
### 09. Simple Sensors
*   직접 신호 방식 센서 제어 (`HC_SR04` 초음파, `Joystick`, `Keypad`)
*   다양한 입력 장치 활용 (`RotaryEncoder`, `PS2Keyboard`)
 
### 10. I2C Devices
*   2선식 통신을 이용한 장치 제어 (`LCD_I2Cm`, `RTC_TimeSet`)
*   각종 I2C 센서 활용 (`ADXL345` 가속도, `MAX30105` 입자 센서)
 
### 11. SPI Devices
*   고속 통신 규격 SPI 기초 (`Comm_SPI`, `DigitalPot`)
*   대량의 데이터 처리 (`Matrix` 도트 매트릭스, `SdFat` SD카드)
 
### 12. OneWire Devices
*   단선 통신을 이용한 센서 제어 (`DHT11` 온습도, `DS18B20` 온도)
 
### 13. EEPROM Storage
*   전원이 꺼져도 유지되는 데이터 저장 (`EEPROM`, `eeprom_write`)
 
### 14. Advanced Internal
*   전력 절감을 위한 수면 모드 (`Sleep_delay`, `SleepTest1`)
*   코드 최적화 및 휘발성 변수 활용 (`Volatile`, `DigitalFilter`)
 
### 15. Integrated Projects
*   여러 기능을 통합한 시스템 구현 (`Balance` 밸런싱 로봇, `Datalog` 데이터 로거)

---
※ 각 폴더 내의 `README.md`에서 상세한 학습 목표와 하드웨어 연결 방법을 확인할 수 있습니다.

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-20. 예제 폴더 117개, 외부 라이브러리 7개, 회로도 보유 폴더 36개.

| 폴더 | 예제 | 회로도 보유 | 비고 |
|---|---|---|---|
| [`00_Introduction`](./00_Introduction/) | 0 | 0 | 파일만 보유 |
| [`01_Digital_IO`](./01_Digital_IO/) | 6 | 3 |  |
| [`02_Segment_Display`](./02_Segment_Display/) | 3 | 2 |  |
| [`03_Serial_Comm`](./03_Serial_Comm/) | 15 | 3 | 외부 라이브러리 1개 포함 |
| [`04_ADC`](./04_ADC/) | 3 | 2 |  |
| [`05_Interrupts`](./05_Interrupts/) | 3 | 3 |  |
| [`06_Timers_Counters`](./06_Timers_Counters/) | 6 | 4 |  |
| [`07_PWM`](./07_PWM/) | 3 | 3 |  |
| [`08_Motors`](./08_Motors/) | 3 | 2 |  |
| [`09_Simple_Sensors`](./09_Simple_Sensors/) | 14 | 1 | 외부 라이브러리 1개 포함 |
| [`10_I2C_Devices`](./10_I2C_Devices/) | 34 | 6 | 외부 라이브러리 4개 포함 |
| [`11_SPI_Devices`](./11_SPI_Devices/) | 14 | 4 | 외부 라이브러리 1개 포함 |
| [`12_OneWire_Devices`](./12_OneWire_Devices/) | 2 | 1 |  |
| [`13_EEPROM_Storage`](./13_EEPROM_Storage/) | 3 | 0 |  |
| [`14_Advanced_Internal`](./14_Advanced_Internal/) | 8 | 2 |  |

<!-- AUTO-INDEX:END -->
