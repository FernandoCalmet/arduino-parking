//Pines
#define LED 2

void setup() {
  //Iniciamos el monitor serie a una velocidad de 9600 baudios para la transmision de datos
  Serial.begin(9600);
  //Modo entrada/salida de los pines
  pinMode(LED, OUTPUT);
}

void loop() {  
  apagarLED();
  prenderLED();
}

//Metodo apagar el LED
void apagarLED(){
  digitalWrite(LED, LOW);
  delay(3000);
}
//Metodo probar LED
void prenderLED(){
  digitalWrite(LED, HIGH);
  delay(3000);
}
