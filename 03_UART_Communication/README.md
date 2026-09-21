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

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-21. 예제 5개.

| 폴더 | 소스 | 회로도 |
|---|---|---|
| `10_Serial` | `Serial.ino` | — |
| `20_Print` | `ASCIITable.ino` | — |
| `30_Serial_Input` | `Serial_Input.ino` | — |
| `40_SerialEvent` | `SerialEvent.ino` | — |
| `50_Comm_UART` | `Comm_2Arduino.ino` | 있음 (Proteus) |

> ℹ️ 다중기기 통신·커스텀 프로토콜·SD 로깅 등 응용/중복 예제 12개는 `15_Projects/03_UART_Communication_Extended/`로 옮겼습니다.

<!-- AUTO-INDEX:END -->
