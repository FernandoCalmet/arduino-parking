#define LEDVERDE 10
#define LEDAMARILLO 9
#define LEDROJO 8
#define TRIGGER 4
#define ECHO 3
#define BUZZER 2
char dato;
const float sonido = 34300.0;
const float umbral1 = 30.0;
const float umbral2 = 20.0;
const float umbral3 = 10.0;

void setup() {
  Serial.begin(9600);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARILLO, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  apagarLEDs();
}

void loop() {
  iniciarTrigger();
  float distancia = calcularDistancia();
  apagarLEDs(); 
  if (distancia < umbral1)
    {alertas(distancia);}
  dato = Serial.read();
  switch(dato){
    case'A':
    digitalWrite(LEDVERDE, HIGH);
    delay(5000);
    digitalWrite(LEDVERDE, LOW);
    break;
    case'B':
    digitalWrite(LEDAMARILLO, HIGH);
    delay(5000);
    digitalWrite(LEDAMARILLO, LOW);
    break;
    case'C':
    digitalWrite(LEDROJO, HIGH);
    delay(5000);
    digitalWrite(LEDROJO, LOW);
    break;
  }
}

void apagarLEDs()
{
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARILLO, LOW);
  digitalWrite(LEDROJO, LOW);
}

void alertas(float distancia)
{
  if (distancia < umbral1 && distancia >= umbral2)
  {
    digitalWrite(LEDVERDE, HIGH);
    tone(BUZZER, 2000, 200);
  }
  else if (distancia < umbral2 && distancia > umbral3)
  {
    digitalWrite(LEDAMARILLO, HIGH);
    tone(BUZZER, 2500, 200);
  }
  else if (distancia <= umbral3)
  {  
    digitalWrite(LEDROJO, HIGH);
    tone(BUZZER, 3000, 200);
  }
}

float calcularDistancia()
{  
  unsigned long tiempo = pulseIn(ECHO, HIGH);
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);
  return distancia;
}

void iniciarTrigger()
{ 
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER, LOW);
}
