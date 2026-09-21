#include <Servo.h>

#define pwm			9

Servo motor;

void setup() {
  Serial.begin(9600);
  motor.attach(pwm);


  for( int i=0; i<=180; i+=10 ) {
  	motor.write(i);
    Serial.println(i);
   	delay(1000);
  }
  for( int i=180; i>=0; i-=5 ) {
  	motor.write(i);
    Serial.println(i);
   	delay(1000);
  }
}

void loop() {
  int val = analogRead(A0);

  motor.write(map(val, 0, 1023, 0, 180));
  delay(100);
}
