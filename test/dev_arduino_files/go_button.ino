int RightMotor_E_pin = 6;
int LeftMotor_E_pin =5;
int RightMotor_1_pin = 9;
int RightMotor_2_pin = 11;
int LeftMotor_3_pin = 7;
int LeftMotor_4_pin = 8;

const int buttonPin = 2;    
const int ledPin =  13;    

int buttonState = 0;     
void setup() {
  pinMode(RightMotor_E_pin, OUTPUT);     //agv
  pinMode(LeftMotor_E_pin, OUTPUT);
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);
  pinMode(ledPin, OUTPUT);               //button
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(RightMotor_1_pin, HIGH);
  digitalWrite(RightMotor_2_pin, LOW);
  digitalWrite(LeftMotor_3_pin, HIGH);
  digitalWrite(LeftMotor_4_pin, LOW);
  /*digitalWrite(RightMotor_E_pin, HIGH);
  digitalWrite(LeftMotor_E_pin, HIGH);
  */
  analogWrite(RightMotor_E_pin, 160);
  analogWrite(LeftMotor_E_pin, 120);
  
  
  if (buttonState == HIGH) {
    digitalWrite(RightMotor_E_pin, 0);
    digitalWrite(LeftMotor_E_pin, 0);
    digitalWrite(RightMotor_1_pin, LOW);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, LOW);
    digitalWrite(LeftMotor_4_pin, LOW);
    Serial.println(buttonState);
  }
}
