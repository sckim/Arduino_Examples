# 01. Arduino Examples (High-level Framework)

이 폴더는 ATmega328P 마이크로컨트롤러를 **아두이노 프레임워크(Arduino C++)**를 사용하여 빠르고 효율적으로 구현한 학습 예제 모음입니다. 복잡한 레지스터 설정을 추상화된 함수(`digitalWrite`, `analogRead` 등)로 처리하여 로직 구현에 집중할 수 있습니다.

## 🛠 개발 환경 (Development Environments)

이 프로젝트는 표준 아두이노 개발 환경과 현대적인 IDE 환경을 모두 지원합니다.

### 1. Arduino IDE (2.x 권장)
*   **특징**: 가장 대중적인 개발 환경, 간편한 보드 설정 및 시리얼 모니터 제공.
*   **사용법**: 각 폴더 내의 `.ino` 파일을 열어 보드(Arduino Uno)를 선택하고 업로드합니다.
*   **팁**: 라이브러리 매니저를 통해 필요한 외부 라이브러리를 쉽게 설치할 수 있습니다.

### 2. Visual Studio Code + PlatformIO
*   **특징**: 강력한 코드 자동 완성, Git 통합, 전문적인 에디팅 환경.
*   **사용법**: `01_Digital_IO/README.md`의 "VS Code + PlatformIO로 예제 실행하기"를 참고하세요. `01_Digital_IO/10_Blink`가 PlatformIO 프로젝트 템플릿이며, 다른 예제(`.ino` 파일)는 이 템플릿의 `src/main.cpp`에 붙여 넣어 실행합니다.

---

## 📚 학습 커리큘럼 및 예제 안내

`00~14`는 기본 교과, `15_Projects`와 `20_Applications`는 기본 교과에서 덜어낸 확장·응용 예제 모음입니다. 각 폴더 내부의 예제는 `10_, 20_, 30_...` 번호로 선행 학습 순서를 나타냅니다 (숫자가 작을수록 먼저 학습).

> ℹ️ **편성 원칙**: 기본 교과의 각 폴더는 MCU/아두이노의 핵심 개념을 대표하는 예제만 소수로 유지합니다. 특정 상용 모듈, 연구성 캘리브레이션 변형, 서로 중복되는 예제 등은 `15_Projects`(챕터와 대응하는 `_Extended` 그룹)와 `20_Applications`(제품·모듈 중심 응용)로 모아둡니다.

### 00. Introduction
*   개발 환경, 코딩 스타일, 스케치 템플릿 (`Template.ino`, `CodingStyle.md`)
*   C 언어 기초: `10_Data_Types` → `20_Operators` → `30_Control_Flow` → `40_Functions` → `50_Arrays_Pointers` → `60_String`

### 01. Digital I/O
*   기초 입출력 제어 (`10_Blink`, `20_Button`)
*   여러 개의 LED 제어 (`30_LED_bar`, `40_ShiftOut`)
*   VS Code + PlatformIO로 예제 실행하는 방법 안내

### 02. Segment Display
*   7-세그먼트 표시 장치의 구동 원리 (`10_7Segments`, `20_BCD_4511`)
*   여러 자리 멀티플렉싱 (`30_Two_7Segments`)

### 03. UART Communication
*   PC와의 데이터 송수신 기초 (`10_Serial`, `30_Serial_Input`)
*   출력 형식/이벤트 기반 수신 (`20_Print`, `40_SerialEvent`)
*   레지스터 레벨 UART 이해 (`50_Comm_UART`)

### 04. ADC (Analog Input)
*   가변저항 등을 이용한 아날로그 전압 측정 (`10_AnalogReadSerial`, `20_ADC_multi`)
*   인터럽트 기반의 정밀한 ADC 샘플링 (`30_ADC_Int`)

### 05. Interrupts
*   `volatile` 키워드와 ISR 안전성 (`10_Volatile`)
*   외부 인터럽트 `attachInterrupt()` (`20_External_Interrupt`)
*   핀 변화 인터럽트 (`30_PCInterrupt`)

### 06. Timers & Counters
*   하드웨어 타이머를 이용한 정확한 주기 생성 (`10_Timer_Overflow`, `20_Timer_CTC`)
*   TimerOne 라이브러리로 고속 클록 출력 (`40_Osc1MHz`)

### 07. PWM (Power Control)
*   LED 밝기 및 전압 제어 기초 (`10_AnalogWrite`)
*   타이머 레지스터를 직접 제어하는 PWM (`20_Timer0_PWM`, `30_Timer0_FastPWM`)

### 08. Motors
*   서보 모터의 각도 제어 (`10_Servo1`)
*   스테핑 모터의 정밀 위치 제어 (`30_Stepper_motor`)

### 09. I2C Communication
*   I2C 장치 주소 찾기와 기본 쓰기 (`10_i2c_scanner`, `20_I2C_write`)
*   LCD·RTC (`30_LCD_I2Cm`, `40_DS1307`, `41_RTC_TimeSet.ino`)
*   대표 센서/장치 (`50_LM75`, `60_PCF8574`, `70_MAX30105`, `80_ADXL345`)

### 10. SPI Communication
*   고속 통신 규격 SPI 기초 (`10_Comm_SPI`)
*   디지털 팟과 SPI ADC (`40_DigitalPot`, `50_MCP3208`)

### 11. OneWire Communication
*   단선 통신을 이용한 센서 제어 (`10_DHT11` 온습도, `20_DS18B20` 온도)

### 12. EEPROM
*   전원이 꺼져도 유지되는 데이터 저장 (`10_EEPROM`, `20_eeprom_write`, `30_eeprom_24c02`)

### 13. WatchDog & Sleep
*   워치독 타이머로 시스템 안정성 확보 (`10_Watchdog_Basic`)
*   절전 모드: 시간 기반(`20_Sleep_delay`), 얕은 절전(`30_IDLE_Sleep_ExtInterrupt`), 깊은 절전(`40_Deep_Sleep_ExtInterrupt`)
*   워치독 + 슬립 결합 저전력 패턴 (`50_Power_Management`)

### 14. Bootloader
*   리셋 원인/퓨즈 비트 읽기로 부트로더 동작 원리 이해 (`10_MCUSR_ResetReason`, `20_Read_Signature_Fuses`)
*   실제 부트로더 소스 분석 (`30_optiboot`)

### 15. Projects (확장 예제)
*   기본 교과에서 덜어낸 확장/심화/중복 예제. 그룹 이름은 챕터 번호와 대응합니다 (예: `09_I2C_Communication_Extended`).

### 20. Applications (응용 예제)
*   필터링(`50_DigitalFilter`, `60_FIR_filter`), `Datalog`, `IRremote`, `AFE4300`, `Spal_9DOF_v4`, 센서 모듈 모음(`Simple_Sensors_Extended`) 등 순서 없는 응용/완성 프로젝트.

---
※ 각 폴더 내의 `README.md`에서 상세한 학습 목표와 예제 목록을 확인할 수 있습니다.

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-21. 기본 교과(`00~14`) 예제 57개, `15_Projects` 확장 예제 68개(그룹 8개), `20_Applications` 9개 항목.

| 폴더 | 예제 | 비고 |
|---|---|---|
| [`00_Introduction`](./00_Introduction/) | 6 | C 언어 기초 |
| [`01_Digital_IO`](./01_Digital_IO/) | 4 | PlatformIO 템플릿(`10_Blink`) 포함 |
| [`02_Segment_Display`](./02_Segment_Display/) | 3 |  |
| [`03_UART_Communication`](./03_UART_Communication/) | 5 |  |
| [`04_ADC`](./04_ADC/) | 3 |  |
| [`05_Interrupts`](./05_Interrupts/) | 3 |  |
| [`06_Timers_Counters`](./06_Timers_Counters/) | 3 |  |
| [`07_PWM`](./07_PWM/) | 3 |  |
| [`08_Motors`](./08_Motors/) | 2 |  |
| [`09_I2C_Communication`](./09_I2C_Communication/) | 9 |  |
| [`10_SPI_Communication`](./10_SPI_Communication/) | 3 |  |
| [`11_OneWire_Communication`](./11_OneWire_Communication/) | 2 |  |
| [`12_EEPROM`](./12_EEPROM/) | 3 |  |
| [`13_WatchDog_Sleep`](./13_WatchDog_Sleep/) | 5 |  |
| [`14_Bootloader`](./14_Bootloader/) | 3 |  |
| [`15_Projects`](./15_Projects/) | 68 | `_Extended` 그룹 8개 |
| [`20_Applications`](./20_Applications/) | 9 | 순서 없는 응용 프로젝트 |

<!-- AUTO-INDEX:END -->
