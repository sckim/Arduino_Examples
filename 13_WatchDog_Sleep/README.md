# 13. WatchDog & Sleep

## 🎯 학습 목표
*   MCU의 저전력 동작(Sleep)과, 시스템이 멈췄을 때 스스로 복구하는 워치독 타이머(Watchdog Timer, WDT)를 다룹니다.

## 💻 주요 주제
*   **Sleep Mode**: 전력 소모를 최소화하여 배터리로 구동하는 장치 개발 기초
*   **Watchdog Timer**: 정해진 시간 내에 리셋 신호(`wdt_reset()`)가 없으면 MCU를 자동으로 재부팅시켜 시스템 안정성을 높이는 기법
*   두 개념을 결합하면 "주기적으로 깨어나 확인하고 다시 잠드는" 초저전력 시스템을 만들 수 있습니다.

## 📁 학습 순서
1.  `10_Watchdog_Basic` — `wdt_enable()`/`wdt_reset()` 기초. 버튼을 눌러 loop()가 멈춘 상황을 흉내내면, 워치독이 타임아웃되어 MCU가 스스로 리셋되는 것을 관찰한다.
2.  `20_Sleep_delay` — 기본 Sleep 모드 진입/해제 (내부적으로 WDT를 타이머로 활용)
3.  `30_IDLE_Sleep_ExtInterrupt` — 가장 얕은 절전(IDLE) + 외부 인터럽트로 깨어남
4.  `40_Deep_Sleep_ExtInterrupt` — 가장 깊은 절전(PWR_DOWN) + 외부 인터럽트로 깨어남 (3번과 절전 깊이를 비교)
5.  `50_Power_Management` — WDT를 "깨우기 알람"으로 써서 Sleep과 결합한 실전 저전력 패턴

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-21. 예제 5개.

| 폴더 | 소스 | 회로도 |
|---|---|---|
| `10_Watchdog_Basic` | `Watchdog_Basic.ino` | — |
| `20_Sleep_delay` | `Sleep_delay.ino` | — |
| `30_IDLE_Sleep_ExtInterrupt` | `IDLE_Sleep_ExtInterrupt.ino` | — |
| `40_Deep_Sleep_ExtInterrupt` | `Deep_Sleep_ExtInterrupt.ino` | — |
| `50_Power_Management` | `Power_Management.ino` | — |

<!-- AUTO-INDEX:END -->
