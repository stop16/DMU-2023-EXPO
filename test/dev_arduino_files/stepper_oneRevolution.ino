const int motor1StepPin = 2;   // 모터 1의 스텝 핀
const int motor1DirPin = 3;    // 모터 1의 방향 핀

const int motor2StepPin = 4;   // 모터 2의 스텝 핀
const int motor2DirPin = 5;    // 모터 2의 방향 핀

const int motor3StepPin = 6;   // 모터 2의 스텝 핀
const int motor3DirPin = 7;    // 모터 2의 방향 핀

const int motor4StepPin = 8;   // 모터 2의 스텝 핀
const int motor4DirPin = 9;    // 모터 2의 방향 핀

void setup() {
  pinMode(motor1StepPin, OUTPUT);
  pinMode(motor1DirPin, OUTPUT);
  
  pinMode(motor2StepPin, OUTPUT);
  pinMode(motor2DirPin, OUTPUT);

  pinMode(motor3StepPin, OUTPUT);
  pinMode(motor3DirPin, OUTPUT);

  pinMode(motor4StepPin, OUTPUT);
  pinMode(motor4DirPin, OUTPUT);
}

void loop() {
  // 모터 1 및 모터 2를 시계 방향으로 1회전 회전
  digitalWrite(motor1DirPin, HIGH);  // 시계 방향
  digitalWrite(motor2DirPin, HIGH);  // 시계 방향
  digitalWrite(motor3DirPin, HIGH);
  digitalWrite(motor4DirPin, HIGH);
  
  for (int i = 0; i < 3200; i++) {  // 200 스텝 = 1회전
    digitalWrite(motor1StepPin, HIGH);
    digitalWrite(motor2StepPin, HIGH);
    digitalWrite(motor3StepPin, HIGH);
    digitalWrite(motor4StepPin, HIGH);
    delayMicroseconds(300);  // 스텝 신호 유지 시간
    digitalWrite(motor1StepPin, LOW);
    digitalWrite(motor2StepPin, LOW);
    digitalWrite(motor3StepPin, LOW);
    digitalWrite(motor4StepPin, LOW);
    delayMicroseconds(300);  // 스텝 신호 유지 시간
  }
  
  // 일정 시간 동안 대기
  delay(1000);
}
