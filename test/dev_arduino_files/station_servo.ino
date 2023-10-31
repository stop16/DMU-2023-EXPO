#include <Servo.h>

Servo rearservo;

void setup() {
  rearservo.attach(2);
  Serial.begin(9600);
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
  moveServoTo(0, 1); // 0도로 3초 동안 이동
}

void door_open() {
  moveServoTo(180, 1); // 180도로 3초 동안 이동
}

void loop() {
  door_close();
  delay(1000); // 3초 대기
  door_open();
  delay(1000); // 3초 대기
}
