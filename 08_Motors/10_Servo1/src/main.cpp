/*=======================================================*/
// Servo1 : 같은 일을 Servo 라이브러리로 한다
//
// 교재 7장 실습 7-3의 뒷부분. 12_Servo_Bitbang 에서 손으로 만든 펄스를
// 라이브러리가 대신 만들어 준다. 각도를 도 단위로 쓰면 되고 펄스 폭은 감춰진다.
//
// PlatformIO 에는 Servo 가 들어 있지 않다. platformio.ini 에 적어야 한다.
//   lib_deps = arduino-libraries/Servo
// #include 는 "이 이름을 쓰겠다"는 선언일 뿐이다. 실제 헤더와 소스가 있어야
// 빌드된다. 11장 Stepper 에서와 같은 상황이다.
//
// 연결 (12_Servo_Bitbang 과 같다)
//   서보 빨강 : 5V,  갈색 : GND,  노랑 : 9번 핀
//   가변저항 와이퍼 : A0
//
// 빌드 크기를 12_Servo_Bitbang 과 비교해 보라. 라이브러리는 타이머를 써서
// 여러 서보를 동시에 돌릴 수 있게 만들어져 있다. 그만큼 코드가 크다.
//
// 선행 학습 : 12_Servo_Bitbang
/*=======================================================*/
#include <Arduino.h>
#include <Servo.h>

const uint8_t SERVO = 9;
const uint8_t POT   = A0;

Servo motor;

void setup()
{
  Serial.begin(9600);
  motor.attach(SERVO);

  // 0도에서 180도까지, 다시 0도로 한 번 쓸어 본다
  for (int deg = 0; deg <= 180; deg += 10) {
    motor.write(deg);
    Serial.println(deg);
    delay(100);
  }
  for (int deg = 180; deg >= 0; deg -= 10) {
    motor.write(deg);
    Serial.println(deg);
    delay(100);
  }
}

void loop()
{
  int adc = analogRead(POT);
  int deg = map(adc, 0, 1023, 0, 180);   // 펄스 폭이 아니라 각도로 쓴다

  motor.write(deg);
  delay(100);
}
