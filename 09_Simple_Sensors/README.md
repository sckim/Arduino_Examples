# 09. Simple Sensors

## 🎯 학습 목표
*   통신 프로토콜 없이 단순한 신호(아날로그 전압, 펄스 폭 등)로 데이터를 전송하는 센서들을 제어합니다.

## 🛠 주요 센서 및 모듈
*   **초음파 센서(HC-SR04)**: 펄스의 시간을 측정하여 거리 계산
*   **네오픽셀(WS2812B)**: 전용 타이밍 신호로 여러 LED 개별 제어
*   **매트릭스 키패드**: 행/열 스캔을 통한 버튼 입력 확인
*   **적외선 리모컨(IR)**: 적외선 신호 코드 수신

## 💻 주요 함수
*   `pulseIn(pin, state)`: 신호의 길이를 마이크로초 단위로 측정

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-20. 예제 폴더 14개, 외부 라이브러리 1개, 회로도 보유 1개, `Project Backups` 백업본 2개.

| 폴더 | 소스 | Proteus 회로도 |
|---|---|---|
| `ColorSensor` | `ColorSensor.ino` | — |
| `Encoder` | `Encoder.ino` | `AVR328P_Encoder.pdsprj` (백업 2) |
| `Fire` | 1개 파일 | — |
| `FlexiForce` | `press.pde` | — |
| `HC_SR04` | `HC_SR04.ino` | — |
| `Joystick` | `Joystick.ino` | — |
| `Keypad` | `Keypad.ino` | — |
| `PS2Keyboard` | 6개 파일 · 외부 라이브러리 | — |
| `Pusein` | `Pusein.ino` | — |
| `RF433_Receiver` | `Receiver.ino` | — |
| `RF433_Transmitter` | `Transmitter.ino` | — |
| `RotaryEncoder` | `RotaryEncoder.ino` | — |
| `SFR05` | `SFR05.ino` | — |
| `ShowDistance` | `ShowDistance.ino` | — |
| `Ultrasound` | `Ultrasound.ino` | — |

<!-- AUTO-INDEX:END -->
