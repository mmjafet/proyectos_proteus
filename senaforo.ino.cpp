#include <Arduino.h>
#line 1 "C:\\Users\\Suseth Sandoval\\Documents\\Arduino\\senaforo\\senaforo.ino"
int tiempoEspera = 1000;

//Botones
const int BTNInicio = A4;   // INICIARBTN
const int BTNApagar = A5;   // APAGARBTN

//leds
const int red1 = 10;
const int yellow1 = 11;
const int green1 = 12;

const int red2 = 2;
const int yellow2 = 3;
const int green2 = 4;

//Constantes
bool inicio = false;

#line 19 "C:\\Users\\Suseth Sandoval\\Documents\\Arduino\\senaforo\\senaforo.ino"
void setup();
#line 35 "C:\\Users\\Suseth Sandoval\\Documents\\Arduino\\senaforo\\senaforo.ino"
void loop();
#line 76 "C:\\Users\\Suseth Sandoval\\Documents\\Arduino\\senaforo\\senaforo.ino"
void delayInterrumpible(int ms);
#line 88 "C:\\Users\\Suseth Sandoval\\Documents\\Arduino\\senaforo\\senaforo.ino"
void apagarTodo();
#line 19 "C:\\Users\\Suseth Sandoval\\Documents\\Arduino\\senaforo\\senaforo.ino"
void setup() {
  //SEMAFORO 1
  pinMode(red1, OUTPUT);    // Rojo
  pinMode(yellow1, OUTPUT); // Amarillo
  pinMode(green1, OUTPUT);  // Verde

  //SEMAFORO 2
  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);

  //Botones
  pinMode(BTNInicio, INPUT);
  pinMode(BTNApagar, INPUT);
}

void loop() {
  int estadoBtnInicio = digitalRead(BTNInicio);
  int estadoBtnApagar = digitalRead(BTNApagar);

  // Verificación del botón para iniciar
  if (estadoBtnInicio && !estadoBtnApagar) {
    inicio = true;
  } else if (estadoBtnApagar) {
    inicio = false;
  }

  // Si está en modo "inicio", comienza el ciclo del semáforo
  if (inicio) {
    // Ciclo de los semáforos, pero se verifica constantemente el botón de apagado
    digitalWrite(red1, HIGH);   // rojo encendido
    digitalWrite(green2, HIGH);
    delayInterrumpible(tiempoEspera);

    digitalWrite(yellow2, HIGH);
    digitalWrite(green2, LOW);
    delayInterrumpible(tiempoEspera);

    digitalWrite(red2, HIGH);
    digitalWrite(green1, HIGH); // verde encendido
    digitalWrite(yellow2, LOW);
    digitalWrite(red1, LOW);    // rojo apagado
    delayInterrumpible(tiempoEspera);

    digitalWrite(yellow1, HIGH); // amarillo encendido
    digitalWrite(green1, LOW);   // verde apagado
    delayInterrumpible(tiempoEspera);

    digitalWrite(red2, LOW);
    digitalWrite(yellow1, LOW);  // amarillo apagado
  } else {
    // Si no está en modo inicio, apaga todos los LEDs
    apagarTodo();
  }
}

// Función para verificar constantemente el botón de apagado durante las demoras
void delayInterrumpible(int ms) {
  for (int i = 0; i < ms; i += 100) {
    if (digitalRead(BTNApagar)) {
      inicio = false;
      apagarTodo();
      break; // Detiene la función y sale del ciclo
    }
    delay(100); // Pequeñas pausas para que el botón pueda ser leído
  }
}

// Función para apagar todos los LEDs
void apagarTodo() {
  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
}
