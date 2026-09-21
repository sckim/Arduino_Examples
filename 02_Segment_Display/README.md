# 02. Segment Display

## 🎯 학습 목표
*   7개의 LED 조각(Segment)을 제어하여 숫자를 표시하는 원리를 이해합니다.
*   여러 개의 숫자를 표시하기 위한 멀티플렉싱(Multiplexing) 기법의 기초를 배웁니다.

## 🛠 주요 부품
*   7-Segment (FND), 저항

## 💻 핵심 개념
*   **Common Cathode/Anode**: 공통 단자의 연결 방식 차이 이해
*   **배열(Array) 활용**: 각 숫자에 대응하는 핀 상태를 배열로 관리하여 효율적으로 코딩하는 법

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-21. 예제 3개.

| 폴더 | 소스 | 회로도 |
|---|---|---|
| `10_7Segments` | `7Segments.ino` | 있음 (Proteus) |
| `20_BCD_4511` | `BCD_4511_Demo.ino` | 있음 (Proteus) |
| `30_Two_7Segments` | `Two_7Segments.ino` | 있음 (Proteus) + Wokwi |

> ℹ️ 중복인 `RawPattern`과 타이머+인터럽트를 결합한 `SegDisplayInt`는 `15_Projects/02_Segment_Display_Extended/`로 옮겼습니다. `SegDisplayInt`는 `05_Interrupts`, `06_Timers_Counters`를 먼저 학습한 뒤 시도하세요.

<!-- AUTO-INDEX:END -->
