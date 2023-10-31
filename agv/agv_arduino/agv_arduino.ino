char command;
int funcflag = 0;

int RightMotor_E_pin = 6;
int LeftMotor_E_pin = 5;
int RightMotor_1_pin = 9;
int RightMotor_2_pin = 11;
int LeftMotor_3_pin = 7;
int LeftMotor_4_pin = 8;
int buttonPin = 2;
#define dirPin 3
#define stepPin 4

void led_on() {
  digitalWrite(LED_BUILTIN, HIGH);
  funcflag = 0;
}

void led_off() {
  digitalWrite(LED_BUILTIN, LOW);
  funcflag = 0;
}

void go_through() {
  analogWrite(RightMotor_E_pin, 160);
  analogWrite(LeftMotor_E_pin, 120);
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);
  digitalWrite(LeftMotor_3_pin, HIGH);
  digitalWrite(LeftMotor_4_pin, LOW);
  while (1)
  {
    int buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH)
    {
      digitalWrite(RightMotor_E_pin, LOW);
      digitalWrite(LeftMotor_E_pin, LOW);
      digitalWrite(RightMotor_1_pin, LOW);
      digitalWrite(RightMotor_2_pin, LOW);
      digitalWrite(LeftMotor_3_pin, LOW);
      digitalWrite(LeftMotor_4_pin, LOW);
      break;
    }
  }
  funcflag = 0;
}

void move_lift(int dir, int val) {
  if (dir == 0)//올리기
  {
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < val; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(10000); //original value:6000
      digitalWrite(stepPin, LOW);
      delayMicroseconds(10000);
    }
  }
  if (dir == 1)//내리기
  {
    digitalWrite(dirPin, LOW);
    for (int i = 0; i < val; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(20000); //original value:6000
      digitalWrite(stepPin, LOW);
      delayMicroseconds(20000);
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
  pinMode(RightMotor_E_pin, OUTPUT);     //agv
  pinMode(LeftMotor_E_pin, OUTPUT);
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(LeftMotor_E_pin,LOW);
  digitalWrite(RightMotor_E_pin,LOW);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
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
    go_through();
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  if (command == 'b')
  {
    funcflag = 1;
    move_lift(1, 1200);
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
  if (command == 'c')
  {
    funcflag = 1;
    move_lift(0, 6000);
    while (funcflag == 1) {}
    Serial.println(command);
    command = 0;
  }
}
