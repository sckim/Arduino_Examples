# 01. Digital IO

## 🎯 학습 목표
*   아두이노의 디지털 핀을 사용하여 외부 장치(LED)를 제어하고 입력(Button)을 읽는 방법을 배웁니다.
*   디지털 신호의 High(5V/3.3V)와 Low(0V) 개념을 이해합니다.

## 🛠 주요 부품
*   LED, 저항(220~330Ω), 택트 스위치(Button)

## 💻 주요 함수
*   `pinMode(pin, mode)`: 핀을 입력 또는 출력으로 설정
*   `digitalWrite(pin, value)`: 디지털 핀에 High/Low 출력
*   `digitalRead(pin)`: 디지털 핀의 상태(High/Low)를 읽음
*   `delay(ms)`: 지정된 시간(밀리초) 동안 대기

---

## 🧩 VS Code + PlatformIO로 예제 실행하기

이 저장소의 예제는 대부분 `.ino` 파일 하나로만 되어 있어서, Arduino IDE에서는 그 파일을 바로 열면 됩니다. 하지만 **VS Code에서 PlatformIO로 빌드/업로드하려면 PlatformIO가 요구하는 프로젝트 구조**(`platformio.ini`, `src/` 폴더 등)가 필요합니다. `10_Blink` 폴더가 바로 그 구조를 갖춘 **템플릿**이니, 이후 예제(`.ino` 파일만 있는 폴더)를 VS Code에서 진행하고 싶다면 이 템플릿을 재사용하세요.

### 1. PlatformIO 설치 (최초 1회)
1.  VS Code 왼쪽 사이드바의 확장(Extensions) 아이콘 클릭
2.  "PlatformIO IDE" 검색 후 설치, VS Code 재시작

### 2. `10_Blink` 템플릿 구조 살펴보기
```
10_Blink/
├── platformio.ini   <- 어떤 보드(Uno)/프레임워크(arduino)를 쓸지 정의
├── src/
│   └── main.cpp      <- 실제 코드가 들어가는 파일 (.ino 대신 .cpp 사용)
├── include/, lib/, test/  <- PlatformIO가 요구하는 표준 폴더 (지금은 안 써도 됨)
```

### 3. 다른 예제를 PlatformIO로 돌리는 방법
1.  `10_Blink` 폴더를 통째로 복사해서, 원하는 예제 이름으로 붙여넣기 (예: `20_Button_pio`)
2.  복사한 폴더의 `src/main.cpp`를 열어서, 진행하려는 예제의 `.ino` 파일 내용으로 전부 교체
    *   `.ino` 파일은 맨 위에 `#include <Arduino.h>` 가 없어도 되지만, `main.cpp`에서는 **반드시 첫 줄에 `#include <Arduino.h>` 를 추가**해야 합니다.
3.  VS Code에서 `File > Open Folder`로 복사한 폴더를 엶
4.  하단 상태 표시줄의 체크(✓) 아이콘: 빌드, 오른쪽 화살표(→) 아이콘: 업로드
5.  `platformio.ini` 안의 `board = uno` 부분은 실제 사용하는 보드에 맞게 필요시 수정

### 4. 더 간단한 대안
매번 템플릿을 복사하기 번거롭다면, 그냥 **Arduino IDE**에서 `.ino` 파일을 직접 여는 방법이 훨씬 빠릅니다. PlatformIO는 여러 파일/라이브러리로 커지는 프로젝트나, Git 연동·자동완성이 중요한 경우에 유리합니다.

---

<!-- AUTO-INDEX:BEGIN -->
<!-- gen_index.py가 만든다. 손으로 고치지 마세요. 기준일 2026-09-29 -->

### 📂 예제 (6개)

| 폴더 | 내용 | 소스 | 줄 | PlatformIO | 회로도 | Wokwi | README |
|---|---|---:|---:|:---:|:---:|:---:|:---:|
| `10_Blink` |  | 1 | 10 | ✓ | ✓ |  |  |
| `20_Button` |  | 1 | 15 |  | ✓ |  |  |
| `22_Button_Serial` | 버튼을 digitalRead 로 읽고 그 값을 시리얼로 본다 | 1 | 20 | ✓ |  |  |  |
| `30_LED_bar` | 가변저항 값을 LED 8개의 막대 그래프로 표시한다 | 2 | 57 | ✓ |  |  |  |
| `40_ShiftOut` | shiftOutCode, Hello World | 1 | 19 |  | ✓ |  |  |
| `50_Bit_Mask` | 바이트 하나의 비트를 꺼내 LED 8개로 내보낸다 | 1 | 30 | ✓ |  |  |  |

<!-- AUTO-INDEX:END -->
