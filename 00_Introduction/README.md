# Arduino & AVR MCU Learning Curriculum

이 커리큘럼은 아두이노(ATmega328P)를 이용한 임베디드 시스템 학습을 위해 `00~14`의 기본 교과와, 확장·응용 예제를 모아둔 `15_Projects`, `20_Applications`로 구성되었습니다. C 언어 기초에서 시작해 디지털 입출력, 통신 프로토콜, 인터럽트·타이머, 시스템 안정성(Watchdog/Bootloader)까지 순서대로 학습할 수 있습니다.

## 📚 학습 단계 안내

0.  **00_Introduction**: 개발 환경, 코딩 스타일, C 언어 기초 (본 폴더)
1.  **01_Digital_IO**: LED, 버튼 등 기초 디지털 입출력 (VS Code + PlatformIO 사용법 포함)
2.  **02_Segment_Display**: 7-세그먼트(FND) 숫자 표시
3.  **03_UART_Communication**: 시리얼 모니터 디버깅 및 PC 통신
4.  **04_ADC**: 아날로그 입력(ADC)
5.  **05_Interrupts**: `volatile`, 외부 인터럽트, 핀 변화 인터럽트
6.  **06_Timers_Counters**: 타이머/카운터를 이용한 정밀 시간 제어
7.  **07_PWM**: 밝기/전압 제어(PWM)
8.  **08_Motors**: 서보 및 스테핑 모터 제어
9.  **09_I2C_Communication**: SDA/SCL 방식의 I2C 통신 (LCD, RTC, 센서 등)
10. **10_SPI_Communication**: 고속 SPI 통신
11. **11_OneWire_Communication**: 단선 통신 센서 (DHT11, DS18B20)
12. **12_EEPROM**: 비휘발성 데이터 저장
13. **13_WatchDog_Sleep**: 워치독 타이머와 저전력 수면 모드
14. **14_Bootloader**: 부트로더 동작 원리 (리셋 원인, 퓨즈, optiboot)
15. **15_Projects**: 기본 교과에서 덜어낸 확장/심화/중복 예제 (`XX_..._Extended`, 챕터 번호와 대응)
20. **20_Applications**: 특정 제품·연구·센서 모듈 중심의 응용/완성 프로젝트 (순서 없음)

각 폴더 내부의 하위 예제 폴더는 `10_, 20_, 30_...` 번호로 선행 학습 순서를 표시합니다 (숫자가 작을수록 먼저 학습).

## 🧭 이 폴더의 예제 (C 언어 기초)

| 순서 | 폴더 | 내용 |
|---|---|---|
| 10 | `10_Data_Types` | 기본/고정폭 자료형(`uint8_t` 등), 크기와 오버플로우 관찰 |
| 20 | `20_Operators` | 산술·비교·논리 연산과 비트 연산자(레지스터 조작의 기초) |
| 30 | `30_Control_Flow` | `if`/`for`/`while`/`do-while`/`switch` |
| 40 | `40_Functions` | 매개변수·반환값, 오버로딩, `#define` 매크로의 함정 |
| 50 | `50_Arrays_Pointers` | 배열, 포인터(`&`, `*`), 배열과 포인터의 관계 |
| 60 | `60_String` | 자료형별 `sizeof`, `String` 클래스 |

참고 자료: `Template.ino`(스케치 기본 틀), `CodingStyle.md`(코딩 스타일), `.url` 링크 3개.

## 🚀 시작하기 전 주의사항

*   **하드웨어 연결:** 각 예제를 실행하기 전 회로도를 반드시 확인하세요.
*   **라이브러리:** 일부 예제는 외부 라이브러리 설치가 필요합니다. (`15_Projects`, `20_Applications`에 포함된 라이브러리 폴더/.zip 참조)
*   **디버깅:** 시리얼 모니터(`03_UART_Communication`)를 적극 활용하여 내부 값을 확인하는 습관을 들이세요.

---

<!-- AUTO-INDEX:BEGIN -->
<!-- gen_index.py가 만든다. 손으로 고치지 마세요. 기준일 2026-09-29 -->

### 📂 예제 (6개)

| 폴더 | 내용 | 소스 | 줄 | PlatformIO | 회로도 | Wokwi | README |
|---|---|---:|---:|:---:|:---:|:---:|:---:|
| `10_Data_Types` | C(아두이노)의 가장 기본적인 자료형을 정리한다. | 1 | 37 |  |  |  |  |
| `20_Operators` | C의 기본 연산자와, 임베디드에서 특히 중요한 "비트 연산자"를 다룬다. | 1 | 45 |  |  |  |  |
| `30_Control_Flow` | if/else, for, while, do-while, switch. | 1 | 72 |  |  |  |  |
| `40_Functions` | 함수의 기본 형태(매개변수, 반환값)와, 매크로(#define)와의 차이를 다룬다. | 1 | 51 |  |  |  |  |
| `50_Arrays_Pointers` | 배열과 포인터의 기초. | 1 | 48 |  |  |  |  |
| `60_String` | " + String(sizeof(bool))); | 1 | 21 |  | ✓ |  |  |

<!-- AUTO-INDEX:END -->
