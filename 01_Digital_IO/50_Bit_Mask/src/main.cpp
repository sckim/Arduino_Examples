/*=======================================================*/
// Bit_Mask : 바이트 하나의 비트를 꺼내 LED 8개로 내보낸다
//
// 교재 3장 실습 3-2. 세트·클리어·토글·검사 네 가지 비트 관용구를
// 눈으로 확인하는 것이 목적이다. 가변저항과 ADC 는 쓰지 않는다(7장).
//
// 연결 (LED 는 저항 220옴을 거쳐 GND 로, 즉 HIGH 에서 켜진다)
//   LED0, LED1 : 8, 9번 핀   (PB0, PB1)
//   LED2~LED7  : 2~7번 핀    (PD2~PD7)
//   30_LED_bar 와 같은 배선이므로 브레드보드를 그대로 쓸 수 있다.
//   0·1번 핀은 시리얼(UART)에 쓰이므로 비운다.
//
// 16장에서는 같은 일을 포트 두 개에 나누어 쓴다. 건드리지 않을 비트를
// 지우고(~마스크 AND) 새 값을 얹는(OR) 3.4절의 조합이 그대로 나온다.
//   PORTB = (PORTB & ~0x03) | (value & 0x03);
//   PORTD = (PORTD & ~0xFC) | (value & 0xFC);
//
// 선행 학습 : 22_Button_Serial      다음 단계 : 02_Segment_Display
/*=======================================================*/
#include <Arduino.h>

// 비트 i 가 나가는 핀. 비트 0·1 은 포트 B, 비트 2~7 은 포트 D 다.
const uint8_t LED_pins[8] = {8, 9, 2, 3, 4, 5, 6, 7};

const uint8_t patterns[] = {
  0b00000001, 0b00000011, 0b00000111, 0b00001111,
  0b00011111, 0b00111111, 0b01111111, 0b11111111,
};

// value 의 비트 0~7 을 LED_pins 의 순서대로 내보낸다
void writeByte(uint8_t value) {
  for (uint8_t i = 0; i < 8; i++) {
    if (value & (1 << i)) {
      digitalWrite(LED_pins[i], HIGH);
    } else {
      digitalWrite(LED_pins[i], LOW);
    }
  }
}

void setup() {
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(LED_pins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (uint8_t n = 0; n < 8; n++) {
    writeByte(patterns[n]);
    Serial.println(patterns[n], BIN);
    delay(300);
  }
}
