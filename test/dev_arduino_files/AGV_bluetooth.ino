#include <SoftwareSerial.h>

SoftwareSerial BT(3, 4);

int RightMotor_E_pin = 5;
int LeftMotor_E_pin =6;
int RightMotor_1_pin = 7;
int RightMotor_2_pin = 8;
int LeftMotor_3_pin = 9;
int LeftMotor_4_pin = 11;


void motor_role(int R_motor, int L_motor){
   digitalWrite(RightMotor_1_pin, R_motor);
   digitalWrite(RightMotor_2_pin, !R_motor);
   digitalWrite(LeftMotor_3_pin, L_motor);
   digitalWrite(LeftMotor_4_pin, !L_motor);

   digitalWrite(RightMotor_E_pin, HIGH);
   digitalWrite(LeftMotor_E_pin, HIGH);
}

void Right_role(){
   digitalWrite(RightMotor_1_pin, LOW);
   digitalWrite(RightMotor_2_pin, LOW);
   digitalWrite(LeftMotor_3_pin, LOW);
   digitalWrite(LeftMotor_4_pin, LOW);
   analogWrite(RightMotor_E_pin, 120);
   analogWrite(LeftMotor_E_pin, 255);
}

void Left_role(){
   digitalWrite(RightMotor_1_pin, HIGH);
   digitalWrite(RightMotor_2_pin, HIGH);
   digitalWrite(LeftMotor_3_pin, HIGH);
   digitalWrite(LeftMotor_4_pin, HIGH);
   analogWrite(RightMotor_E_pin, 255);
   analogWrite(LeftMotor_E_pin, 120);
}

void setup() {
  pinMode(RightMotor_E_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);

  Serial.begin(9600);
  BT.begin(9600);
}

void GO() {
   digitalWrite(RightMotor_1_pin, HIGH);
   digitalWrite(RightMotor_2_pin, LOW);
   digitalWrite(LeftMotor_3_pin, LOW);
   digitalWrite(LeftMotor_4_pin, HIGH);

   digitalWrite(RightMotor_E_pin, HIGH);
   digitalWrite(LeftMotor_E_pin, HIGH);
}

void RI() {
   digitalWrite(RightMotor_1_pin, LOW);
   digitalWrite(RightMotor_2_pin, HIGH);
   digitalWrite(LeftMotor_3_pin, LOW);
   digitalWrite(LeftMotor_4_pin, HIGH);

   digitalWrite(RightMotor_E_pin, HIGH);
   digitalWrite(LeftMotor_E_pin, HIGH);
}

void LE() {
   digitalWrite(RightMotor_1_pin, HIGH);
   digitalWrite(RightMotor_2_pin, LOW);
   digitalWrite(LeftMotor_3_pin, HIGH);
   digitalWrite(LeftMotor_4_pin, LOW);

   digitalWrite(RightMotor_E_pin, HIGH);
   digitalWrite(LeftMotor_E_pin, HIGH);
}

void BA() {
  digitalWrite(RightMotor_1_pin, LOW);
   digitalWrite(RightMotor_2_pin, HIGH);
   digitalWrite(LeftMotor_3_pin, HIGH);
   digitalWrite(LeftMotor_4_pin, LOW);

   digitalWrite(RightMotor_E_pin, HIGH);
   digitalWrite(LeftMotor_E_pin, HIGH);
}

void ST() {
   digitalWrite(RightMotor_E_pin, 0);
   digitalWrite(LeftMotor_E_pin, 0);
}

void GR(){
  Right_role();
}

void GL(){
  Left_role();
}

char t;

void loop() {

  if(BT.available())
  {
    t = BT.read();
  }
  //Serial.println(t);
  if(t == 'W'){
    GO();
  }
  if (t == 'D'){
    RI();
  }
  if(t == 'A'){
    LE();
  }
  if(t == 'S'){
    BA();
  }
  if(t == 'P'){
    ST();
  }
  if(t == 'E'){
    GR();
  }
  if(t == 'Q'){
    GL();
  }
}
  
