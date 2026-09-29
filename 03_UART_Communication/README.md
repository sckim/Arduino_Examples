# 03. UART Communication

## 🎯 학습 목표
*   아두이노와 PC 간에 데이터를 주고받는 방법을 배웁니다.
*   시리얼 모니터를 사용하여 센서 값을 확인하고 프로그램을 디버깅하는 능력을 기릅니다.

## 💻 주요 함수
*   `Serial.begin(baudrate)`: 시리얼 통신 초기화 (보통 9600 사용)
*   `Serial.print(value)` / `Serial.println(value)`: 데이터를 PC로 전송
*   `Serial.available()`: 수신된 데이터가 있는지 확인
*   `Serial.read()`: 수신된 데이터를 읽음
*   `serialEvent()`: 수신 이벤트 기반 처리

## 📁 학습 순서 (UART 기본기)
1.  `10_Serial` — 가장 기본적인 송수신
2.  `20_Print` — 다양한 형식으로 출력하기
3.  `30_Serial_Input` — PC로부터 입력 받기
4.  `40_SerialEvent` — 이벤트 기반 수신 처리
5.  `50_Comm_UART` — 레지스터 레벨에서 UART가 실제로 어떻게 동작하는지 이해



---

<!-- AUTO-INDEX:BEGIN -->
<!-- gen_index.py가 만든다. 손으로 고치지 마세요. 기준일 2026-09-29 -->

### 📂 예제 (7개)

| 폴더 | 내용 | 소스 | 줄 | PlatformIO | 회로도 | Wokwi | README |
|---|---|---:|---:|:---:|:---:|:---:|:---:|
| `10_Serial` | 시리얼로 PC 에 한 줄 보내기 | 2 | 20 | ✓ |  |  |  |
| `12_UART_Scope` | 계측기로 파형을 읽기 좋은 값을 내보낸다 | 1 | 15 | ✓ |  |  |  |
| `20_Print` | No external hardware needed. | 1 | 39 |  |  |  |  |
| `30_Serial_Input` | Serial port를 통해서 컴퓨터의 명령어를 받아서 이에 반응하는 프로그램 | 1 | 36 |  |  |  |  |
| `32_Serial_Command` | PC 가 보낸 글자를 받아 동작을 바꾼다 | 1 | 28 | ✓ |  |  |  |
| `40_SerialEvent` | The serialEvent() feature is not available on the Le | 1 | 40 |  |  |  |  |
| `50_Comm_UART` |  | 1 | 22 |  | ✓ |  |  |

<!-- AUTO-INDEX:END -->
