# 05. Interrupts

## 🎯 학습 목표
*   **인터럽트(Interrupt)**의 개념을 이해하고, 프로그램 실행 중 비동기적으로 발생하는 이벤트에 즉각 반응하는 법을 배웁니다.

## 💻 핵심 개념
*   **volatile**: 인터럽트에서 변경되는 변수를 컴파일러 최적화로부터 보호하는 키워드 (`10_Volatile`) — PCINT류를 배우기 전에 먼저 확인하세요.
*   **External Interrupt**: 특정 핀의 전압 변화(Falling/Rising Edge)에 반응
*   **PCINT (Pin Change Interrupt)**: 모든 핀에서 상태 변화를 감지하는 기법
*   **ISR (Interrupt Service Routine)**: 인터럽트 발생 시 실행되는 특별한 함수 작성법 및 주의사항

## 📁 학습 순서
1.  `10_Volatile` — ISR과 안전하게 공유할 변수 선언법
2.  `20_External_Interrupt` — `attachInterrupt()`로 INT0(2번 핀) 외부 인터럽트 사용
3.  `30_PCInterrupt` — 더 많은 핀에서 쓸 수 있는 핀 변화 인터럽트(PCINT) 설정

---

<!-- AUTO-INDEX:BEGIN -->
<!-- gen_index.py가 만든다. 손으로 고치지 마세요. 기준일 2026-09-28 -->

### 📂 예제 (3개)

| 폴더 | 내용 | 소스 | 줄 | PlatformIO | 회로도 | Wokwi | README |
|---|---|---:|---:|:---:|:---:|:---:|:---:|
| `10_Volatile` |  | 1 | 16 |  | ✓ |  |  |
| `20_External_Interrupt` | ATmega328P의 두 가지 인터럽트 방식 중 더 기본적인 "외부 인터럽트"(External | 1 | 37 |  |  |  |  |
| `30_PCInterrupt` |  | 1 | 33 |  | ✓ |  |  |

<!-- AUTO-INDEX:END -->
