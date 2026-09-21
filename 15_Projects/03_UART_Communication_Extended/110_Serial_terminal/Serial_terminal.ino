#include <Adafruit_TinyUSB.h>

#define SERIAL_PRINT  Serial
#define SERIAL_UART   Serial1

void setup() {
  // 하드웨어 시리얼 통신 초기화 (기본 RX:0, TX:1 핀 사용)
  SERIAL_UART.begin(115200);  // 통신 속도 설정
  SERIAL_PRINT.begin(115200);  // 통신 속도 설정
}

void loop() {
  // Arduino IDE로 입력
  if (SERIAL_PRINT.available()) {
    char receivedChar = SERIAL_PRINT.read();

    // Tx 핀으로 출력
    SERIAL_UART.write(receivedChar);
  }

  // Rx 핀으로 수신
  if (SERIAL_UART.available()) {
    char receivedChar = SERIAL_UART.read();
  
    // Arduino IDE로 출력
    SERIAL_PRINT.write(receivedChar);
  }
}