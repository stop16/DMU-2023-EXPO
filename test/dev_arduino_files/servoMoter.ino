#include <Servo.h>

Servo rearservo;
Servo frontservo;

int pos = 0;

void gripper_close()
{
  rearservo.write(169);//170쓰면 오류남
  frontservo.write(10);
}

void gripper_open()
{
  rearservo.write(10);
  frontservo.write(130);
}


void setup() {
  rearservo.attach(7);
  frontservo.attach(6);
  Serial.begin(9600);
  //pinMode(6,OUTPUT); // 아두이노 D6핀, OUTPUT 설정
}
int value = 90;
void loop() {
  gripper_close();
  delay(3000);
  gripper_open();
  delay(3000);
  // 서보모터 -90도 : 20ms 중 0.5ms
 /* for(i=0; i<30 ; i++)
  {
    digitalWrite(7,LOW);
    delayMicroseconds(15000);
    delayMicroseconds(5000-500);
    digitalWrite(7,HIGH);
    delayMicroseconds(500);
    digitalWrite(7,LOW);
  } 
  
  delay(500);*/
/*
  // 서보모터 0도 : 20ms 중 1.5ms
   for(i=0; i<30 ; i++)
  {
    digitalWrite(7,LOW);
    delayMicroseconds(15000);
    delayMicroseconds(5000-1500);
    digitalWrite(7,HIGH);
    delayMicroseconds(1500);
    digitalWrite(7,LOW);
  }
  
  delay(500);
*/
  // 서보모터 90도 : 20ms 중 2.5ms
  /* for(i=0; i<30 ; i++)
  {
    digitalWrite(7,LOW);
    delayMicroseconds(15000);
    delayMicroseconds(5000-2500);
    digitalWrite(7,HIGH);
    delayMicroseconds(2500);
    digitalWrite(7,LOW);
  }
   delay(500);*/
}
