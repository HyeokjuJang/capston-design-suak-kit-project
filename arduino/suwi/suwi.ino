#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int analogPin = 0;    // 워터센서 analog port 0 연결 선언
int val = 0;          // 전류변화값 변수선언

void setup() {
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  Serial.begin (9600);
}

void loop() {
  val = analogRead(analogPin);   // analogPin 의 변화값(전류값)을 읽음
 
  if (val > 100)                 // val 값이 100이 넘으면 (전류가 100이 넘으면)
  {                               
        myservo.write(180);              // tell servo to go to position in variable 'pos'
        delay(500);                       // waits 15ms for the servo to reach the position
  }
  else                           // val 값이 100이하면 (전류가 100이하면)
  {
    myservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(500);
  }
  
  Serial.println(val);      // 시리얼모니터에 전류값 표시
  delay (500);
}


