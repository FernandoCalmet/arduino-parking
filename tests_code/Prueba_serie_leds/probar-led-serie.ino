//Pines
#define LED1 2
#define LED2 3
#define LED3 4

void setup() {
  //Iniciamos el monitor serie
  Serial.begin(9600);
  //Modo entrada/salida de los pines
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {  
  apagarLED();
  prenderLED();
}

//Metodo apagar el LED
void apagarLED()
{
  digitalWrite(LED1, LOW);delay(1000);
  digitalWrite(LED2, LOW);delay(2000);
  digitalWrite(LED3, LOW);delay(3000);
 }
//Metodo probar LED
void prenderLED()
{
  digitalWrite(LED1, HIGH);delay(1000);
  digitalWrite(LED2, HIGH);delay(2000);
  digitalWrite(LED3, HIGH);delay(3000);
 }
