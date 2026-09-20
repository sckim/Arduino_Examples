# 05. Interrupts

## 🎯 학습 목표
*   **인터럽트(Interrupt)**의 개념을 이해하고, 프로그램 실행 중 비동기적으로 발생하는 이벤트에 즉각 반응하는 법을 배웁니다.

## 💻 핵심 개념
*   **External Interrupt**: 특정 핀의 전압 변화(Falling/Rising Edge)에 반응
*   **PCINT (Pin Change Interrupt)**: 모든 핀에서 상태 변화를 감지하는 기법
*   **ISR (Interrupt Service Routine)**: 인터럽트 발생 시 실행되는 특별한 함수 작성법 및 주의사항

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-20. 예제 폴더 3개, 회로도 보유 3개, `Project Backups` 백업본 3개.

| 폴더 | 소스 | Proteus 회로도 |
|---|---|---|
| `PCINT` | `PCINT.ino` | `Arduino 328.pdsprj` (백업 2) |
| `PCIntSetup` | `PCIntSetup.ino` | `Arduino 328.pdsprj` (백업 1) |
| `PCInterrupt` | `PCInterrupt.ino` | `Arduino 328.pdsprj` |

<!-- AUTO-INDEX:END -->
