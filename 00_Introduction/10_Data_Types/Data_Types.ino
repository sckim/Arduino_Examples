/*
 * Data_Types
 * -----------
 * C(아두이노)의 가장 기본적인 자료형을 정리한다.
 *
 * 임베디드에서는 "몇 바이트를 쓰는지"가 매우 중요하다. MCU의 RAM/Flash가
 * 매우 작기 때문에(ATmega328P: RAM 2KB), int를 아무 데나 쓰면 메모리가
 * 금방 부족해진다. 그래서 "고정폭 정수형"(uint8_t 등, <stdint.h>)을
 * 상황에 맞게 골라 쓰는 습관이 중요하다.
 *
 * 다음 단계: 20_Operators (비트 연산으로 이 자료형들을 직접 다뤄본다)
 */

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println(F("=== 기본 자료형 크기(byte)와 표현 범위 ==="));

  Serial.print(F("bool     : ")); Serial.print(sizeof(bool));     Serial.println(F(" byte  (true/false)"));
  Serial.print(F("char     : ")); Serial.print(sizeof(char));     Serial.println(F(" byte  (-128 ~ 127)"));
  Serial.print(F("int      : ")); Serial.print(sizeof(int));      Serial.println(F(" byte  (-32768 ~ 32767, 8비트 AVR에서는 16비트!)"));
  Serial.print(F("long     : ")); Serial.print(sizeof(long));     Serial.println(F(" byte"));
  Serial.print(F("float    : ")); Serial.print(sizeof(float));    Serial.println(F(" byte"));

  Serial.println();
  Serial.println(F("=== 임베디드에서 즐겨 쓰는 고정폭 정수형 (<stdint.h>) ==="));
  Serial.print(F("uint8_t  : ")); Serial.print(sizeof(uint8_t));  Serial.println(F(" byte  (0 ~ 255)          <- 레지스터 1바이트와 동일"));
  Serial.print(F("int8_t   : ")); Serial.print(sizeof(int8_t));   Serial.println(F(" byte  (-128 ~ 127)"));
  Serial.print(F("uint16_t : ")); Serial.print(sizeof(uint16_t)); Serial.println(F(" byte  (0 ~ 65535)         <- 16비트 타이머 레지스터와 동일"));
  Serial.print(F("uint32_t : ")); Serial.print(sizeof(uint32_t)); Serial.println(F(" byte  (0 ~ 4294967295)"));

  Serial.println();
  Serial.println(F("=== 오버플로우(overflow) 관찰: uint8_t 는 255 다음에 무슨 값이 될까? ==="));
  uint8_t small = 255;
  Serial.print(F("uint8_t small = 255; small = small + 1; -> "));
  small = small + 1;
  Serial.println(small);  // 256이 아니라 0이 출력된다 (8비트를 넘는 자리는 그냥 잘려나감)
  Serial.println(F("(256이 아니라 0이 나온다 -> 자료형의 표현 범위를 넘으면 값이 '한바퀴 돌아' 처음으로 되돌아간다)"));
}

void loop() {
  // 관찰용 예제이므로 loop에서는 아무 것도 하지 않는다.
}
