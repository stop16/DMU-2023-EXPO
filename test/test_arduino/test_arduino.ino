char command;
int funcflag = 0;

void led_on(){
  digitalWrite(LED_BUILTIN, HIGH);
  funcflag = 0; 
}

void led_off(){
  digitalWrite(LED_BUILTIN, LOW);
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
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    command = Serial.read();
  }
  if(command == 'o')
  {
    funcflag = 1;
    led_on();
    while(funcflag == 1){}
      Serial.println(command);
      command = 0;
  }
  if(command == 'x')
  {
    funcflag = 1;
    led_off();
    while(funcflag == 1){}
      Serial.println(command);
      command = 0;
  }
}
