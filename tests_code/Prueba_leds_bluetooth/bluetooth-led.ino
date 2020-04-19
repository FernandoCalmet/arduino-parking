#define LED1 10
#define LED2 9
char dato;

void setup(){
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  }

void loop(){
  dato = Serial.read();
  switch(dato){
    case 'A':digitalWrite(LED1,HIGH);break;
    case 'B':digitalWrite(LED1,LOW);break;
    case 'C':digitalWrite(LED2,HIGH);break;
    case 'D':digitalWrite(LED2,LOW);break;
  }
}
