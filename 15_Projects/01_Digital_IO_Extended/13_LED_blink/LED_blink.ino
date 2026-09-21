#include <arduino.h>

#define LED 13

//LED는 디지털 13번 핀에 연결되어 있음
void setup(){
  // 디지털핀(13)을 출력으로 설정

	pinMode(LED, OUTPUT);
}

void loop() {
  //LED를 켠다.
  digitalWrite(LED,HIGH);  
  //1초 대기
  delay(100);

  //LED를 끈다.
  digitalWrite(LED,LOW);   
  //1초 대기
  delay(100);
}

