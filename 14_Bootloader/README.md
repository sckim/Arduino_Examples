# 14. Bootloader

## 🎯 학습 목표
*   스케치가 업로드되기 전, MCU가 켜질 때 가장 먼저 실행되는 **부트로더**의 동작 원리를 이해합니다.
*   부트로더가 있어야 USB/시리얼만으로 스케치를 업로드할 수 있다는 것과, 부트로더가 없거나 손상되면 ISP(In-System Programming) 프로그래머가 필요하다는 점을 배웁니다.

## 💻 주요 주제
*   **리셋 원인 확인**: MCUSR 레지스터로 방금 리셋이 왜 일어났는지(전원/외부/워치독) 확인 — 부트로더가 "부트로더로 들어갈지 스케치로 갈지"를 판단하는 근거와 같은 원리
*   **퓨즈 비트(Fuse Bits)**: BOOTRST/BOOTSZ 등, 부트로더의 존재와 크기를 결정하는 하드웨어 설정을 읽기 전용으로 확인
*   **optiboot**: 아두이노 Uno 등에서 널리 쓰이는 경량 오픈소스 부트로더 실제 소스. 소스(`optiboot.c`)와 각 칩(atmega8/168/328)용 컴파일된 `.hex` 파일을 포함합니다.
*   부트로더를 직접 굽거나 복구하려면 ISP 프로그래머(ArduinoISP 등)와 함께 학습하면 좋습니다.

## 📁 학습 순서
1.  `10_MCUSR_ResetReason` — 리셋 원인 레지스터 읽기 (13_WatchDog_Sleep과 개념적으로 연결됨)
2.  `20_Read_Signature_Fuses` — 칩 시그니처/퓨즈 비트 읽기 (읽기 전용, 안전)
3.  `30_optiboot` — 실제 부트로더 소스코드 분석 (가장 advanced)

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-21. 예제 3개.

| 폴더 | 소스 | 회로도 |
|---|---|---|
| `10_MCUSR_ResetReason` | `MCUSR_ResetReason.ino` | — |
| `20_Read_Signature_Fuses` | `Read_Signature_Fuses.ino` | — |
| `30_optiboot` | `optiboot.c` | — |

<!-- AUTO-INDEX:END -->
