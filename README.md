# Sensor ultrasónico para medir la distancia en un sistema de aparcamiento  

[![Github][github-shield]][github-url]
[![Kofi][kofi-shield]][kofi-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
[![Khanakat][khanakat-shield]][khanakat-url]

## 📓 TABLA DE CONTENIDO

1. Componentes necesarios
2. Arduino UNO
3. Cómo funciona el sensor ultrasónico Arduino
4. El zumbador o buzzer Arduino
5. Sistema de alerta con LEDs
6. Sensor ultrasónico montando al circuito
7. Diagramas de flujo de las funciones del código fuente
8. Programando el sensor ultrasónico Arduino para medir distancia
9. Resultados en interface de hardware
10. Resultados en interface de Software.
11. Implementación de reconocimiento de voz con control de dispositivo móvil  

## ✔️ Componentes necesarios

La siguiente lista te muestra todo el material necesario para la implementación.  
* Arduino UNO
* Protoboard
* Cables
* 3 resistencias de 220 Ω
* 1 LED verde
* 1 LED amarillo
* 1 LED rojo
* 1 sensor ultrasónico Arduino (HC-SR04)
* 1 buzzer
* 1 bluetooth HC-06

![Materiales](img/Screenshot_1.png?raw=true)

## Arduino UNO

El Arduino es una plataforma computacional física open-source basada en una simple tarjeta de I/O y un entorno de desarrollo que implementa el lenguaje Processing/Wiring. El Arduino Uno R3 puede ser utilizado para desarrollar objetos interactivos o puede ser conectado a software de tu computadora (por ejemplo, Flash, Processing, MaxMSP). El IDE open-source puede ser descargado gratuitamente (actualmente para Mac OS X, Windows y Linux).  

![arduino](img/Screenshot_2.png?raw=true)  

## Cómo funciona el sensor ultrasónico Arduino

Para medir distancias con Arduino podemos hacerlo de diferentes maneras. Existen el sensor de infrarrojos, que utilizan las propiedades de la luz para calcular la distancia, y el sensor ultrasónico Arduino utiliza las propiedades de propagación del sonido para medir distancias. Más concreto utiliza los ultrasonidos. Este tipo de ondas sonoras se encuentran por encima del espectro audible por los seres humanos.

![espectro](img/Screenshot_3.png?raw=true)

El funcionamiento es muy sencillo. El sensor envía una onda ultrasónica a través del disparador o trigger, rebota contra el objeto y el receptor o echo detecta la onda. Sabiendo cuánto ha tardado en viajar dicha onda, podemos saber la distancia.

![sensor](img/Screenshot_4.png?raw=true)

Solo hace falta utilizar la famosa fórmula de la velocidad (V = S/T)  
Donde s es el espacio y t es el tiempo. Si despejamos es espacio que es lo que necesitamos saber, nos quedaría de la siguiente manera: S = V x T  

La velocidad del sonido viaja a 343 metros por segundo, osea 34300.0 milisegundos. El tiempo nos lo devolverá el propio sensor ultrasónico Arduino a través de la API de Arduino. Con todo esto ya podemos calcular a qué distancia se encuentra un objeto.  
La velocidad del sonido es 343 m/s a una temperatura de 20ºC. La velocidad aumenta o disminuye 0,6 m/s por grado centígrado. Podemos ser más exactos si utilizamos un sensor de temperatura como el LM35.  

## Buzzer Arduino

Para simular correctamente el sensor de distancia vamos a utilizar un buzzer Arduino. Estos componentes utilizan la piezoelectricidad, un fenómeno físico que afecta en determinados cristales (el cuarzo es el más común). Al someter un cristal de este tipo, se deforman y vibran. Si conseguimos que esa vibración tenga una frecuencia dentro del espectro audible, conseguiremos un sonido.  

![buzzer](img/Screenshot_5.png?raw=true)  
Por lo tanto, es importante conocer las frecuencias del espectro audible. Debemos quedarnos con el rango de frecuencias que va de 20 Hz (hercios) a 20 kHz (kilohercio).  
![espectro audible](img/Screenshot_6.png?raw=true)  
Cerca de los 20 Hz el sonido es muy grave. Cuando vamos subiendo de frecuencia, el sonido se va haciendo cada vez más agudo. Esto nos servirá para alertar de que nos estamos acercando a un obstáculo al aparcar.  

## Sistema de alerta con LEDs

Por último, incorporamos el sistema de alerta visual para el sensor ultrasónico Arduino. Esto nos permite visualizar si estamos cerca o lejos de un obstáculo. Con 3 LEDs (verde, amarillo y rojo) conseguimos determinar si estamos lejos, cerca o en zona de peligro.  

## Sensor ultrasónico, montando al circuito

Se trata de un circuito muy sencillo. Por un lado vamos a tener toda la parte de alertas, acústica y visual, y por otra parte el sensor de ultrasonidos. En el siguiente esquema muestra el conexionado.  
![modelo](img/Screenshot_7.png?raw=true)  
Cosas a tener en cuenta. Las resistencias son de 220 Ω y se colocan en serie con los LEDs. El sensor ultrasónico Arduino se conecta a dos pines digitales, uno para el trigger o disparador y otro para el echo o receptor. El buzzer Arduino se conecta a una salida PWM.  

## Diagramas de flujo de las funciones del código fuente

![diagrama](img/Screenshot_8.png?raw=true)  
![diagrama](img/Screenshot_9.png?raw=true)  

## Programando el sensor ultrasónico Arduino para medir distancia

El sistema de aparcamiento consiste en detectar un objeto a través del sensor ultrasónico y avisar con señales de luz y sonido. Por lo tanto, ya tenemos la primera división, detectar el obstáculo, alertas con sonido y luces.  
Lo primero que haré será plantear el algoritmo del sistema de detección de obstáculos.  
De los dos algoritmos anteriores, deducimos que vamos a necesitar varios umbrales de decisión, uno para cada situación. Podemos coger una simple regla y determinarlos.  
* Umbral 1: está en zona verde desde 30 cm a 20 cm.
* Umbral 2: está en zona amarilla, desde 20 cm a 10 cm.
* Umbral 3: está en zona roja, menos de 10 cm.
 Es importante conocer el rango de funcionamiento del sensor de ultrasonidos. Va de 2 cm a 400 cm según la hoja de especificaciones técnicas.

## Variables y constantes

A través del sensor de ultrasonidos vamos a detectar el obstáculo. Comenzamos a programar declarando las variables y constantes. Siempre que trabajemos con pines digitales o analógicos, es una buena práctica declarar una constante por cada uno de ellos.

```
// Pines utilizados
#define LEDVERDE 10
#define LEDAMARILLO 9
#define LEDROJO 8
#define TRIGGER 4
#define ECHO 3
#define BUZZER 2

// Constantes
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 30.0;
const float umbral2 = 20.0;
const float umbral3 = 10.0;
```

Definimos los pines para los LEDs, para el sensor de ultrasonidos y para el buzzer Arduino. Luego declaramos 4 constantes. La primera es la velocidad del sonido convirtiendo de metros por segundo a centímetros por segundo. Esto lo hacemos multiplicando por 100. Las siguientes constantes son los umbrales de decisión que hemos marcado antes.  

## Función setup

En la función setup iniciamos el monitor serie y ponemos los pines en el modo correspondiente. Los LEDs, el Trigger del sensor de ultrasonidos y el buzzer son en modo salida (OUTPUT). El pin Echo del sensor ultrasónico en modo entrada (INPUT).  
Por último vamos a empezar desde un estado conocido, todos los LEDs apagados.  
```
void setup() {
  // Iniciamos el monitor serie
  Serial.begin(9600);

  // Modo entrada/salida de los pines
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARILLO, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Apagamos todos los LEDs
  apagarLEDs();
}
```
```
// Apaga todos los LEDs
void apagarLEDs()
{
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARILLO, LOW);
  digitalWrite(LEDROJO, LOW);
}
```

Las funciones son muy útiles por dos razones, nos permiten ordenar el código para que sea más legible y también reutilizar el código. En este caso vamos a necesitar apagar todos los LEDs más de una vez y es más fácil escribir una llamada a una función con una línea de código que hacer las 3 llamadas a la función digitalWrite para apagar cada LED.  

## Función Loop

La función loop() contiene el código que se repetirá una y otra vez. Aquí es donde vamos a ir poniendo todo nuestro algoritmo, el que hemos detallado anteriormente. He dividido esta función en varias funciones para hacer el código más legible.

```
void loop() {
  // Preparamos el sensor de ultrasonidos
  iniciarTrigger();

  // Obtenemos la distancia
  float distancia = calcularDistancia();

  // Apagamos todos los LEDs
  apagarLEDs();

  // Lanzamos alerta si estamos dentro del rango de peligro
  if (distancia < umbral1)
  {
    // Lanzamos alertas
    alertas(distancia);
  }
}
```

## Función para Iniciar sensor ultrasónico

Lo primero que hacemos es preparar el sensor de ultrasonidos. Esto lo hacemos con la función iniciarTrigger() que manda un pulso. Comienza en estado bajo durante 2 milisegundos, luego 10 milisegundos estado alto y por último ponemos en estado bajo. Esto indica que a continuación se mandará la señal para que la capte el echo.

```
// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(TRIGGER, LOW);
}
```

## Función para calcular la distancia de los objetos

Una vez que está preparado el sensor, ya podemos utilizarlo para calcular la distancia. Eso lo hacemos con la función calcularDistancia(). Es una función particular ya que nos va a devolver un valor. Eso se hace poniendo al final (o donde quieras) la palabra reservada return seguido del valor que quieres devolver. Todo el código que haya por debajo del return no se ejecuta así que precaución. En este caso yo devuelvo la distancia calculada dentro de la función que es una variable del tipo float.  
Para calcular el tiempo se utiliza la función nativa de Arduino pulseIn. Esta función nos devuelve el tiempo transcurrido hasta que cambia de estado. Anteriormente hemos preparado el sensor dejando el pin, donde tenemos conectado el trigger, en estado bajo. Cuando la onda ultrasónica viaja por el aire, rebota en el objeto y es detectada por el echo, el pin cambia de estado a alto (HIGH).  
La función pulseIn detecta eso precisamente, y devuelve el tiempo transcurrido en microsegundos. Por este motivo se debe convertir a segundos multiplicando por 0,000001 que es lo mismo que dividir por 1.000.000. Con esta información ya podemos aplicar la fórmula para calcular la distancia en función del tiempo y la velocidad.

```
// Método que calcula la distancia a la que se encuentra un objeto.
// Devuelve una variable tipo float que contiene la distancia
float calcularDistancia()
{
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH);

  // Obtenemos la distancia en cm, hay que convertir el tiempo en segundos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);

  return distancia;
}
```

El tiempo obtenido por la función pulseIn debe ser dividido por 2. Esto es debido a que recorre dos veces la distancia, va hacia el objeto, rebota y vuelve hasta el sensor y por lo tanto tarda el doble.  

## Función para Lanzar alertas

Una vez tenemos la distancia calculada ya podemos decidir si estamos en la situación de enviar alerta o no. Siempre que la distancia esté por debajo del primer umbral (umbral del LED verde y el menos restrictivo), lanzaremos la correspondiente alerta visual y sonora.  
Antes de hacer nada es conveniente apagar todos los LEDs. Esto lo hacemos llamando a la función que hemos generado anteriormente.  
Para reproducir un sonido con buzzer, utilizamos la función nativa de Arduino tone(pin, frecuencia, duración). Esta función admite hasta 3 parámetros aunque con los 2 primeros, sería suficiente.  
* Pin: es el pin donde hemos conectado el buzzer. Recuerda que debe ser un pin PWM.
* Frecuencia: podemos poner un valor entre 20 Hz y 20.000 Hz. Juega con estos valores hasta conseguir un sonido adecuado.
* Duración: la duración en milisegundos que quieres que dure el sonido.
Si no utilizas el parámetro de duración, el sonido se reproducirá continuamente hasta que llames a la función noTone(pin).  
La función comprueba que tipo de alerta hay que lanzar. Si está dentro del rango umbral 1 y umbral 2, enciende el LED verde y reproduce un sonido de 2.000 Hz durante 200 milisegundos. Si está dentro del rango umbral 2 y umbral 3, enciende el LED amarillo y reproduce un sonido de 2.500 Hz durante 200 milisegundos y si está por debajo de umbral 3, enciende el LED rojo y reproduce un sonido de 3.000 Hz durante 200 milisegundos.

```
// Función que comprueba si hay que lanzar alguna alerta visual o sonora
void alertas(float distancia)
{
  if (distancia < umbral1 && distancia >= umbral2)
  {
    // Encendemos el LED verde
    digitalWrite(LEDVERDE, HIGH);
    tone(BUZZER, 2000, 200);
  }
  else if (distancia < umbral2 && distancia > umbral3)
  {
    // Encendemos el LED amarillo
    digitalWrite(LEDAMARILLO, HIGH);
    tone(BUZZER, 2500, 200);
  }
  else if (distancia <= umbral3)
  {
    // Encendemos el LED rojo
    digitalWrite(LEDROJO, HIGH);
    tone(BUZZER, 3000, 200);
  }
}
```
## Resultados en interface de hardware

Compilar y grabar el código fuente al arduino uno. Luego como vemos en la imagen el sensor detectará si algún objeto se pone delante y medirá su distancia, y según nuestra configuración de umbrales obtendremos diferentes resultados de sonido y luces según la distancia del objeto.  
![prueba](img/Screenshot_10.png?raw=true)  
También podemos monitorear los valores de la distancias medidas con el Monitor Serie. Como podemos ver en la siguiente imagen.  
![consola](img/Screenshot_11.png?raw=true)  

## Resultados en interface de software

En el IDE de Arduino seleccionamos Programa > Exportar Binarios compilados. Para obtener en nuestro folder donde se grabó el proyecto un archivo con el mismo nombre con una extensión ‘.HEX’ la cual utilizaremos para configurar nuestro Arduino en el emulador de Proteus.  
![exportar](img/Screenshot_12.png?raw=true)  
Ahora en Proteus cargo las librerías de Arduino para posteriormente poder crear el modelo del diagrama hecho en Fritzing.  
![libreria en proteus](img/Screenshot_13.png?raw=true) 
![libreria en proteus](img/Screenshot_14.png?raw=true) 
Se abrirá una ventana el cual tiene la ruta de librerías del Proteus, entonces pego mi Arduino.lib y luego cierro la ventana. Cierro Proteus y vuelvo a inicializar el programa.  
![libreria en proteus](img/Screenshot_15.png?raw=true)
Ahora reviso los componentes de Device y podre encontrar los componentes de Arduino.  
![libreria en proteus](img/Screenshot_16.png?raw=true)
![modelo en proteus](img/Screenshot_17.png?raw=true)  
Le damos doble click al Arduino, y le cargamos nuestro archivo grabado con extensión hexadecimal.  
![modelo en proteus](img/Screenshot_18.png?raw=true)  
![modelo en proteus](img/Screenshot_19.png?raw=true) 
![modelo en proteus](img/Screenshot_20.png?raw=true)  
Y finalmente corremos el programa para emular el resultado que obtuvimos en la muestra de Hardware.  
![modelo en proteus](img/Screenshot_21.png?raw=true) 

## Implementación de Reconocimiento de Voz con control de dispositivo móvil

Voy a utilizar una aplicación de la pagina http://ai2.appinventor.mit.edu , para diseñar la aplicación que usará mi dispositivo móvil para ejecutar acciones en mi proyecto de Arduino.  
![creando la apk](img/Screenshot_22.png?raw=true)  
En primera instancia creamos nuestra interfaz, en donde insertó 4 componentes.  
* ListPicker
* Button
* SpeechRecognizer
* BluetoothClient
Luego procedemos a crear el algoritmo en Bloques.  
![creando la apk](img/Screenshot_23.png?raw=true)  
El código en bloque nos permitirá la conectividad del reconocimiento de voz a través del bluetooth, y lo grabará en un valor para poder ser tomado como un case del switch del código fuente.  
Luego le doy click a Build y se compila el programa.  
![creando la apk](img/Screenshot_24.png?raw=true)  
Ahora añadire las siguientes lineas de codigo a mi actual código fuente, para poder realizar las pruebas de funcionamiento de los LED utilizando el bluetooth del dispositivo móvil. El cual responderá a las órdenes que yo de con mi voz a través del micrófono del dispositivo.  

```
//declaro el dato que se va a capturar
char dato;
```

```
void loop() {
  // Codigo anterior...
  //agregamos un switch con las tres opciones de probar led
  dato = Serial.read();
  switch(dato){
    case'A':
    digitalWrite(LEDVERDE, HIGH);
    delay(3000);
    digitalWrite(LEDVERDE, LOW);
    break;
    case'B':
    digitalWrite(LEDAMARILLO, HIGH);
    delay(3000);
    digitalWrite(LEDAMARILLO, LOW);
    break;
    case'C':
    digitalWrite(LEDROJO, HIGH);
    delay(3000);
    digitalWrite(LEDROJO, LOW);
    break;
  }
}
```
Finalmente compilamos y grabamos el código en nuestro arduino para hacer la prueba final del funcionamiento de los Leds utilizando mi voz. El cual responderá ante las palabras: Verde, Amarillo o Rojo. Las cuales se encenderá por 5 segundos y luego se apagaran, y con eso se comprobará que los Leds están en correcto funcionamiento. De otra manera también podemos utilizar nuestro sensor el cual nos devolverá los encendidos según los umbrales de distancia acompañado de tres distintas frecuencias de tonos.  

## 📥 DEMO

![resultado final](img/Screenshot_25.png?raw=true)
![resultado final](img/Screenshot_26.png?raw=true)

## 📄 LICENCIA

Este proyecto está bajo la Licencia (Licencia MIT) - mire el archivo [LICENSE](LICENSE) para más detalles.

## ⭐️ DAME UNA ESTRELLA

Si esta Implementación le resultó útil o la utilizó en sus Proyectos, déle una estrella. ¡Gracias! O, si te sientes realmente generoso, [¡Apoye el proyecto con una pequeña contribución!](https://ko-fi.com/fernandocalmet).

<!--- reference style links --->
[github-shield]: https://img.shields.io/badge/-@fernandocalmet-%23181717?style=flat-square&logo=github
[github-url]: https://github.com/fernandocalmet
[kofi-shield]: https://img.shields.io/badge/-@fernandocalmet-%231DA1F2?style=flat-square&logo=kofi&logoColor=ff5f5f
[kofi-url]: https://ko-fi.com/fernandocalmet
[linkedin-shield]: https://img.shields.io/badge/-fernandocalmet-blue?style=flat-square&logo=Linkedin&logoColor=white&link=https://www.linkedin.com/in/fernandocalmet
[linkedin-url]: https://www.linkedin.com/in/fernandocalmet
[khanakat-shield]: https://img.shields.io/badge/khanakat.com-brightgreen?style=flat-square
[khanakat-url]: https://khanakat.com
