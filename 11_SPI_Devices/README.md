# 11. SPI Devices

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

기준일 2026-09-20. 예제 폴더 14개, 외부 라이브러리 1개, 회로도 보유 4개, `Project Backups` 백업본 5개.

| 폴더 | 소스 | Proteus 회로도 |
|---|---|---|
| `AFE4490` | `AFE4490.ino` | — |
| `Comm_SPI` | `Comm_SPI.ino` | `AVR328P_Basic.pdsprj` (백업 1) |
| `DigitalPot` | `DigitalPot.ino` | — |
| `MAX7219` | `MAX7219.ino` | `AVR328P_MAX7219.pdsprj` (백업 1) |
| `MCP3208` | `MCP3208.ino` | — |
| `MCP410x` | `MCP410x.ino` | `AVR328P_MCP410x.pdsprj` (백업 2) |
| `MCP41xx` | `MCP41xx.ino` | — |
| `Matrix` | `MatrixMathExample.ino` | — |
| `RF22_client` | `RF22_client.ino` | — |
| `SPI_5206` | `SPI_5206.ino` | `AVR328P_Basic.pdsprj` (백업 1) |
| `SdFat-master` | 132개 파일 · 외부 라이브러리 | — |
| `TTL74595` | — | — |
| `ad5162` | `ad5162.ino` | — |
| `mcp4161` | `mcp4161.ino` | — |
| `rf22_server` | `rf22_server.ino` | — |

<!-- AUTO-INDEX:END -->
