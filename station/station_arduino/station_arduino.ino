#include <Servo.h>

Servo rearservo;

const int motor1StepPin = 2;
const int motor1DirPin = 3;

const int motor2StepPin = 4;
const int motor2DirPin = 5;

const int motor3StepPin = 6;
const int motor3DirPin = 7;

const int motor4StepPin = 8;
const int motor4DirPin = 9;

char command;
int funcflag = 0;

void led_on() {
  digitalWrite(LED_BUILTIN, HIGH);
  funcflag = 0;
}

void led_off() {
  digitalWrite(LED_BUILTIN, LOW);
  funcflag = 0;
}

void moveServoTo(int angle, int durationSeconds) {
  int currentPosition = rearservo.read();
  int targetPosition = angle;
  int steps = 100; // 총 단계 수
  int delayBetweenSteps = (durationSeconds * 1000) / steps;

  for (int step = 0; step <= steps; step++) {
    int newPosition = map(step, 0, steps, currentPosition, targetPosition);
    rearservo.write(newPosition);
    delay(delayBetweenSteps);
  }
}

void door_close() {
  moveServoTo(180, 1); // 0도로 3초 동안 이동
  funcflag = 0;
}

void door_open() {
   // 180도로 3초 동안 이동
  moveServoTo(0, 1);
  funcflag = 0;
}

void move_stepper(int pos) {
  if (pos == 0) //init 정렬된거에서 초기단계로 돌아가는거
  {
    digitalWrite(motor1DirPin, LOW);
    digitalWrite(motor2DirPin, LOW);
    digitalWrite(motor3DirPin, LOW);
    digitalWrite(motor4DirPin, LOW);
    for (int i = 0; i < 17000; i++)
    {
      digitalWrite(motor1StepPin, HIGH);
      digitalWrite(motor2StepPin, HIGH);
      digitalWrite(motor3StepPin, HIGH);
      digitalWrite(motor4StepPin, HIGH);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
      digitalWrite(motor1StepPin, LOW);
      digitalWrite(motor2StepPin, LOW);
      digitalWrite(motor3StepPin, LOW);
      digitalWrite(motor4StepPin, LOW);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
    }
  }
  if (pos == 1) //preparing 
  {
    digitalWrite(motor1DirPin, HIGH);
    digitalWrite(motor2DirPin, HIGH);
    digitalWrite(motor3DirPin, HIGH);
    digitalWrite(motor4DirPin, HIGH);
    for (int i = 0; i < 17000; i++)
    {
      digitalWrite(motor1StepPin, HIGH);
      //digitalWrite(motor2StepPin, HIGH);
      digitalWrite(motor3StepPin, HIGH);
      //digitalWrite(motor4StepPin, HIGH);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
      digitalWrite(motor1StepPin, LOW);
      //digitalWrite(motor2StepPin, LOW);
      digitalWrite(motor3StepPin, LOW);
      //digitalWrite(motor4StepPin, LOW);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
    }
    for (int i = 0; i < 17000; i++)
    {
      //digitalWrite(motor1StepPin, HIGH);
      digitalWrite(motor2StepPin, HIGH);
      //digitalWrite(motor3StepPin, HIGH);
      digitalWrite(motor4StepPin, HIGH);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
      //digitalWrite(motor1StepPin, LOW);
      digitalWrite(motor2StepPin, LOW);
      //digitalWrite(motor3StepPin, LOW);
      digitalWrite(motor4StepPin, LOW);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
    }
  }
  if (pos == 2) //center
  {
    digitalWrite(motor1DirPin, HIGH);
    digitalWrite(motor2DirPin, LOW);
    digitalWrite(motor3DirPin, LOW);
    digitalWrite(motor4DirPin, LOW);
    for (int i = 0; i < 15000; i++)
    {
      digitalWrite(motor3StepPin, HIGH);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
      digitalWrite(motor3StepPin, LOW);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
    }
    for (int i = 0; i < 21600; i++)
    {
      digitalWrite(motor1StepPin, HIGH);
      //digitalWrite(motor2StepPin, HIGH);
      //digitalWrite(motor3StepPin, HIGH);
      //digitalWrite(motor4StepPin, HIGH);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
      digitalWrite(motor1StepPin, LOW);
      //digitalWrite(motor2StepPin, LOW);
      //digitalWrite(motor3StepPin, LOW);
      //digitalWrite(motor4StepPin, LOW);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
    }
  }
  if(pos==3)
  {
    digitalWrite(motor2DirPin, LOW);
    digitalWrite(motor3DirPin, LOW);
    digitalWrite(motor4DirPin, LOW);
    for (int i = 0; i < 21600; i++)
    {
      //digitalWrite(motor1StepPin, HIGH);
      digitalWrite(motor2StepPin, HIGH);
      digitalWrite(motor3StepPin, HIGH);
      digitalWrite(motor4StepPin, HIGH);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
      //digitalWrite(motor1StepPin, LOW);
      digitalWrite(motor2StepPin, LOW);
      digitalWrite(motor3StepPin, LOW);
      digitalWrite(motor4StepPin, LOW);
      delayMicroseconds(200);  // 스텝 신호 유지 시간
    }
  }
  funcflag = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.setTimeout(10);
  Serial.begin(9600);
  while (1)
  {
    Serial.println('k');
    delay(500);
    command = Serial.read();
    if (command == 'p')
    {
      break;
    }
  }
  Serial.flush();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(motor1StepPin, OUTPUT);
  pinMode(motor1DirPin, OUTPUT);
  pinMode(motor2StepPin, OUTPUT);
  pinMode(motor2DirPin, OUTPUT);
  pinMode(motor3StepPin, OUTPUT);
  pinMode(motor3DirPin, OUTPUT);
  pinMode(motor4StepPin, OUTPUT);
  pinMode(motor4DirPin, OUTPUT);
  rearservo.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    command = Serial.read();
  }
  
  if (command == 'o')
  {
    funcflag = 1;
    led_on();
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  
  if (command == 'x')
  {
    funcflag = 1;
    led_off();
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  
  if (command == 'a')
  {
    funcflag = 1;
    move_stepper(0);
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  
  if (command == 'b')
  {
    funcflag = 1;
    move_stepper(1);
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  
  if (command == 'c')
  {
    funcflag = 1;
    move_stepper(2);
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  
  if (command == 'd')
  {
    funcflag = 1;
    door_close();
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  
  if (command == 'e')
  {
    funcflag = 1;
    door_open();
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  if (command == 'f')
  {
    funcflag = 1;
    move_stepper(3);
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  
}
