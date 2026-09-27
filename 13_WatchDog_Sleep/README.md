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
<!-- gen_index.py가 만든다. 손으로 고치지 마세요. 기준일 2026-09-28 -->

### 📂 예제 (5개)

| 폴더 | 내용 | 소스 | 줄 | PlatformIO | 회로도 | Wokwi | README |
|---|---|---:|---:|:---:|:---:|:---:|:---:|
| `10_Watchdog_Basic` | wdt_enable() / wdt_reset() 를 이용한 워치독 타이머(Watchdog Ti | 1 | 49 |  |  |  |  |
| `20_Sleep_delay` | Start watchdog timer | 1 | 85 |  |  |  |  |
| `30_IDLE_Sleep_ExtInterrupt` |  | 1 | 36 |  |  |  |  |
| `40_Deep_Sleep_ExtInterrupt` | when coming back from POWER-DOWN mode, it takes a bi | 1 | 131 |  |  |  |  |
| `50_Power_Management` | 앞의 두 개념, Watchdog Timer(안정성)와 Sleep Mode(절전)를 결합해서 | 1 | 69 |  |  |  |  |

<!-- AUTO-INDEX:END -->
