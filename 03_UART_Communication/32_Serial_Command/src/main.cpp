/*=======================================================*/
// Serial_Command : PC 가 보낸 글자를 받아 동작을 바꾼다
//
// 교재 4장 실습 4-3. 지금까지는 보내기만 했다. UART 는 전이중이므로
// 받는 쪽(RX)도 동시에 쓸 수 있다. 그것을 확인하는 것이 목적이다.
//
// 명령
//   '1' -> 13번 LED 를 켠다
//   '0' -> 13번 LED 를 끈다
//   '?' -> 현재 상태를 돌려준다
//
// Serial.available() 은 받아 둔 바이트 수다. 0 이면 아직 안 왔다는 뜻이므로
// 먼저 확인하고 나서 read() 를 불러야 한다. 확인 없이 read() 를 부르면
// 받은 것이 없을 때 -1 이 돌아온다.
//
// loop 안에 delay 를 두지 않는다. 사람이 글자를 보내는 시점을 알 수 없으므로
// 계속 돌면서 확인해야 한다. 이것이 폴링이다. 5장의 인터럽트와 비교해 볼 것.
//
// 연결 없음. 시리얼 모니터를 9600 bps 로 열고 보내는 칸에 글자를 넣는다.
//
// 선행 학습 : 12_UART_Scope      다음 단계 : 04_ADC/10_ADC
/*=======================================================*/
#include <Arduino.h>

const uint8_t LED = 13;
bool ledOn = false;

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("ready. send 1, 0, or ?");
}

void loop()
{
  if (Serial.available() > 0) {      // 받아 둔 바이트가 있는지 먼저 본다
    char c = Serial.read();

    if (c == '1') {
      ledOn = true;
      Serial.println("LED on");
    } else if (c == '0') {
      ledOn = false;
      Serial.println("LED off");
    } else if (c == '?') {
      Serial.print("LED is ");
      Serial.println(ledOn ? "on" : "off");
    }
    // 줄바꿈 문자(\r, \n)는 무시된다. 어느 조건에도 걸리지 않기 때문이다.

    digitalWrite(LED, ledOn ? HIGH : LOW);
  }
}
