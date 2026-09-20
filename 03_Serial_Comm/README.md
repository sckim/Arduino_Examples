# 03. Serial Communication

## 🎯 학습 목표
*   아두이노와 PC 간에 데이터를 주고받는 방법을 배웁니다.
*   시리얼 모니터를 사용하여 센서 값을 확인하고 프로그램을 디버깅하는 능력을 기릅니다.

## 💻 주요 함수
*   `Serial.begin(baudrate)`: 시리얼 통신 초기화 (보통 9600 사용)
*   `Serial.print(value)` / `Serial.println(value)`: 데이터를 PC로 전송
*   `Serial.available()`: 수신된 데이터가 있는지 확인
*   `Serial.read()`: 수신된 데이터를 읽음

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-20. 예제 폴더 15개, 외부 라이브러리 1개, 회로도 보유 3개, `Project Backups` 백업본 4개.

| 폴더 | 소스 | Proteus 회로도 |
|---|---|---|
| `ASCIITable` | `ASCIITable.ino` | — |
| `Autoscroll` | 1개 파일 | — |
| `ColorLED` | `ColorLED.ino` | — |
| `Comm_2Arduino` | `Comm_2Arduino.ino` | `AVR328P_Basic.pdsprj` (백업 3) |
| `Comm_UART` | `Comm_2Arduino.ino` | `AVR328P_Basic.pdsprj` |
| `GetSerial` | `ReadASCIIString.ino` | — |
| `OpenLog-master` | 125개 파일 · 외부 라이브러리 | — |
| `Print` | `ASCIITable.ino` | — |
| `Serial` | `Serial.ino` | — |
| `SerialEvent` | `SerialEvent.ino` | — |
| `SerialOutString` | `SerialOutString.ino` | `AVR328P_Basic.pdsprj` (백업 1) |
| `Serial_Input` | `Serial_Input.ino` | — |
| `Serial_Output` | `Serial_Output.ino` | — |
| `Serial_terminal` | `Serial_terminal.ino` | — |
| `Two_SerialComm` | `Two_SerialComm.ino` | — |
| `arduino_multibyte_serial_example_3` | `arduino_multibyte_serial_example_3.ino` | — |

<!-- AUTO-INDEX:END -->
