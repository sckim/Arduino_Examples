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
<!-- gen_index.py가 만든다. 손으로 고치지 마세요. 기준일 2026-09-28 -->

### 📂 예제 (3개)

| 폴더 | 내용 | 소스 | 줄 | PlatformIO | 회로도 | Wokwi | README |
|---|---|---:|---:|:---:|:---:|:---:|:---:|
| `10_Comm_SPI` |  | 1 | 53 |  | ✓ |  |  |
| `40_DigitalPot` |  | 1 | 26 |  |  |  |  |
| `50_MCP3208` |  | 1 | 51 |  |  |  |  |

<!-- AUTO-INDEX:END -->
