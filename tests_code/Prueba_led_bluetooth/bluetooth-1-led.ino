char dato;
void setup() {
  Serial.begin(9600);
  pinMode(10,OUTPUT);
}

void loop() {
  dato = Serial.read();
  if(dato=='A'){
    digitalWrite(10,HIGH);
  }
  else if(dato=='B'){
    digitalWrite(10,LOW);
  }  
}
