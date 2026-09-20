# 06. Timers & Counters

## 🎯 학습 목표
*   아두이노 내부의 **Timer/Counter** 하드웨어를 직접 제어하여 정밀한 시간을 다루는 법을 배웁니다.

## 💻 핵심 개념
*   **Prescaler**: 시스템 클록을 나누어 타이머 속도를 조절하는 원리
*   **CTC Mode**: 특정 값에 도달하면 타이머를 초기화하여 주기적인 동작 수행
*   **Overflow**: 타이머가 최대치에 도달했을 때 발생하는 이벤트 이해

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-20. 예제 폴더 6개, 회로도 보유 4개, `Project Backups` 백업본 4개.

| 폴더 | 소스 | Proteus 회로도 |
|---|---|---|
| `Clock1MHz` | `Clock1MHz.ino` | `LED with UNO.DSN` |
| `Osc1MHz` | `Osc1MHz.ino` | — |
| `Timer0_CTC` | `Timer0_CTC.ino` | `Arduino 328.pdsprj` (백업 2) |
| `Timer_CTC` | `Timer.ino` | `Arduino 328.pdsprj` (백업 1) |
| `Timer_Overflow` | `Timer_Overflow.ino` | `Arduino 328.pdsprj` (백업 1) |
| `_2MHz` | `_1MHz.ino` | — |

<!-- AUTO-INDEX:END -->
