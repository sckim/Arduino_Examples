# 10. SPI Communication

## 🎯 학습 목표
*   **SPI (Serial Peripheral Interface)** 통신의 고속 데이터 전송 원리를 배우고, 4선(MOSI, MISO, SCK, CS) 연결 방식을 익힙니다.

## 🛠 주요 장치
*   **SD 카드 모듈**: 파일 시스템(SdFat)을 통한 데이터 저장
*   **Dot Matrix (MAX7219)**: 대량의 LED 제어
*   **디지털 가변저항 (MCP 시리즈)**: SPI를 통한 저항값 정밀 조절

## 💻 주요 라이브러리/함수
*   `SPI.h`: 아두이노 표준 SPI 라이브러리
*   `CS(Chip Select)`: 여러 장치 중 통신할 대상을 선택하는 원리

---

<!-- AUTO-INDEX:BEGIN -->

## 🗂 폴더 현황 (자동 생성)

기준일 2026-09-21. 예제 3개.

| 폴더 | 소스 | 회로도 |
|---|---|---|
| `10_Comm_SPI` | `Comm_SPI.ino` | 있음 (Proteus) |
| `40_DigitalPot` | `DigitalPot.ino` | — |
| `50_MCP3208` | `MCP3208.ino` | — |

> ℹ️ `MAX7219`, 디지털 팟 변형, `AFE4490`, `SdFat`, `RF22` 등은 `15_Projects/10_SPI_Communication_Extended/`로 옮겼습니다. SPI와 무관한 행렬 수학 예제 `MatrixMath`는 `20_Applications/`에 있습니다.

<!-- AUTO-INDEX:END -->
