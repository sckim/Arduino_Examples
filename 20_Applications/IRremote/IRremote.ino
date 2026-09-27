#include <IRremote.h>
#include <Servo.h>

#define Motor  		9

#define M1A  		6
#define M1B  		7

#define IRSensor	8
#define cSteering	4

IRrecv irreceived(IRSensor);
decode_results results;

Servo steer;

int oldspeed=0, speed = 0;

void SetSpeed(int speed)
{
  if( speed >255 )
      speed = 255;
  if( speed <-255 )
      speed = -255;

  if( speed >= 0 ) {
  	digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
  } else {
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
  }

  analogWrite(Motor, abs(speed));
}

void SetAngle(int *p_angle)
{
  if( *p_angle>180 )
    *p_angle = 180;
  if( *p_angle<0 )
    *p_angle = 0;

  steer.write(*p_angle);
}

void setup() {
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);

  irreceived.enableIRIn();

  Serial.begin(9600);

  speed = 0;
  SetSpeed(speed);

  int an = 90;
  steer.attach(cSteering);
  SetAngle(&an);
}

void loop(){
  static int oldangle=90;
  static int angle = 90;

  if( irreceived.decode(&results)) {
    // 코드 값을 보고 싶을 때
    Serial.println(results.value, HEX);

    switch(results.value) {
      // 2
      case 0xFD8877: speed+=10; break;
      // 8
      case 0xFD9867: speed-=10; break;
      // 5 또는 >|| 버튼
      case 0xFDA857:
      case 0xFDA05F: speed=0; break;
      // >>
      case 0xFD609F: speed+=50; break;
      // <<
      case 0xFD20DF: speed-=50; break;
      // 4
      case 0xFD28D7: angle-=10; break;
      // 6
      case 0xFD6897: angle+=10; break;
    }
    SetSpeed(speed);
    SetAngle(&angle);
    delay(30);
    irreceived.resume();
  }
  if( oldspeed!=speed || oldangle!=angle ) {
    Serial.print("Speed = ");
  	Serial.print(speed);
  	Serial.print(", ");
  	Serial.print("Angle = ");
    Serial.println(angle);

    oldspeed = speed;
    oldangle = angle;
  }

  delay(20);
}
