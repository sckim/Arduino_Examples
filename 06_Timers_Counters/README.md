# 06. Timers & Counters

## 🎯 학습 목표
*   아두이노 내부의 **Timer/Counter** 하드웨어를 직접 제어하여 정밀한 시간을 다루는 법을 배웁니다.

## 💻 핵심 개념
*   **Prescaler**: 시스템 클록을 나누어 타이머 속도를 조절하는 원리
*   **CTC Mode**: 특정 값에 도달하면 타이머를 초기화하여 주기적인 동작 수행
*   **Overflow**: 타이머가 최대치에 도달했을 때 발생하는 이벤트 이해

---

<!-- AUTO-INDEX:BEGIN -->
<!-- gen_index.py가 만든다. 손으로 고치지 마세요. 기준일 2026-09-29 -->

### 📂 예제 (3개)

| 폴더 | 내용 | 소스 | 줄 | PlatformIO | 회로도 | Wokwi | README |
|---|---|---:|---:|:---:|:---:|:---:|:---:|
| `10_Timer_Overflow` |  | 1 | 21 |  | ✓ |  |  |
| `20_Timer_CTC` | Timer0을 이용하여 1초마다 overflow | 1 | 59 |  | ✓ |  |  |
| `40_Osc1MHz` |  | 1 | 35 |  |  |  |  |

<!-- AUTO-INDEX:END -->
