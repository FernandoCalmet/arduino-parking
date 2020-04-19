char d;                      //variable d = dato enviado desde Android

void setup(){            
Serial.begin(9600);          // Velocidad de transmision de datos kbps
pinMode(13,OUTPUT);          // led Azul
pinMode(12,OUTPUT);          // led Verde
pinMode(11,OUTPUT);          // led Rojo
pinMode(10,OUTPUT);          // led Naranja
pinMode(9,OUTPUT);           // led Amarillo
}

void loop() {
    if(Serial.available()){
        d=Serial.read();            // lee el dato enviado desde Android
    
        switch(d){
        case 'A':                  // si dato = A
        digitalWrite(13,HIGH);     // prende led Azul
        digitalWrite(12,LOW);      // y apaga los demas leds
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        break;
        
        case 'V':                  // si dato = V
        digitalWrite(12,HIGH);     // prende led Verde
        digitalWrite(13,LOW);      // y apaga los demas
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        break;
        
        case 'R':                  // si dato = R
        digitalWrite(11,HIGH);     // prende led Rojo
        digitalWrite(13,LOW);      // y apaga los demas 
        digitalWrite(12,LOW);
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        break;
        
        case 'N':                  // si dato = N
        digitalWrite(10,HIGH);     // prende led Naranja
        digitalWrite(13,LOW);      // y apaga los demas
        digitalWrite(12,LOW);
        digitalWrite(11,LOW);
        digitalWrite(9,LOW);
        break;
        
        case 'M':                  // si dato = M
        digitalWrite(9,HIGH);      // prende led aMarillo 
        digitalWrite(13,LOW);      // y apaga los demas
        digitalWrite(12,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        break;
        
        case 'B':                  // si dato = B
        digitalWrite(13,LOW);      // apagamos todos los leds
        digitalWrite(12,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        break;
        }
    }
}