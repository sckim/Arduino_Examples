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

기준일 2026-09-21. 예제 3개.

| 폴더 | 소스 | 회로도 |
|---|---|---|
| `10_Timer_Overflow` | `Timer_Overflow.ino` | 있음 (Proteus) |
| `20_Timer_CTC` | `Timer.ino` | 있음 (Proteus) |
| `40_Osc1MHz` | `Osc1MHz.ino` | — |

> ℹ️ `Timer0_CTC`, `1MHz`, `2MHz`, `Clock1MHz`(세그먼트 결합·중복 변형·수동 레지스터 클럭 생성)는 `15_Projects/06_Timers_Counters_Extended/`로 옮겼습니다.

<!-- AUTO-INDEX:END -->
