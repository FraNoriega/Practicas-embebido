//4.1
#include <Arduino.h>

const int pinAnalog = 26;
int pines[] = {2, 4, 5, 18, 19, 21, 22, 23, 32, 33};
int ADC = 0;

void mostrarleds() {
  float r = (ADC / 1023.0) * 3.3;

  if (r < 0.33) {
    for (int i = 0; i <= 9; i++) {
      if (i < 1) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else if (r < 0.66) {
    for (int i = 0; i <= 9; i++) {
      if (i <= 1) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else if (r < 0.99) {
    for (int i = 0; i <= 9; i++) {
      if (i <= 2) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else if (r < 1.32) {
    for (int i = 0; i <= 9; i++) {
      if (i <= 3) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else if (r < 1.65) {
    for (int i = 0; i <= 9; i++) {
      if (i <= 4) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else if (r < 1.98) {
    for (int i = 0; i <= 9; i++) {
      if (i <= 5) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else if (r < 2.31) {
    for (int i = 0; i <= 9; i++) {
      if (i <= 6) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else if (r < 2.64) {
    for (int i = 0; i <= 9; i++) {
      if (i <= 7) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else if (r < 2.97) {
    for (int i = 0; i <= 9; i++) {
      if (i <= 8) {
        digitalWrite(pines[i], HIGH);
      } else {
        digitalWrite(pines[i], LOW);
      }
    }
  } else {
    // Para cualquier valor >= 2.97V (incluyendo 3.30V exactos)
    for (int i = 0; i <= 9; i++) {
      digitalWrite(pines[i], HIGH);
    }
  }
}

void setup() {
  pinMode(pinAnalog, INPUT);
  for (int i = 0; i < 10; i++) {
    pinMode(pines[i], OUTPUT);
  }
  analogReadResolution(10);
  delay(100);
}

void loop() {
  ADC = analogRead(pinAnalog);
  mostrarleds();
  delay(500);
}

//4.2
#include <Arduino.h>

const int ledPin1 = 12;    // Pin utilizado para el primer LED
const int ledPin2 = 14;    // Pin utilizado para el segundo LED
const int freq = 5000;     // Frecuencia de 5 kHz
const int resolution = 10; // Resolución PWM en bits (10 bits -> max 1023)

// Canales de PWM (0 y 1)
const int canal0 = 0;
const int canal1 = 1;

// Valor máximo del ciclo de trabajo (2^10 - 1 = 1023)
const int maxDuty = 1023; 

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // 1. Configurar canales PWM: ledcSetup(canal, frecuencia, resolucion)
  ledcSetup(canal0, freq, resolution);
  ledcSetup(canal1, freq, resolution);

  // 2. Asignar los pines a los canales: ledcAttachPin(pin, canal)
  ledcAttachPin(ledPin1, canal0);
  ledcAttachPin(ledPin2, canal1);
}

void loop() {
  // Incrementar brillo en LED 1 y decrementar en LED 2
  for (int dutyCycle = 0; dutyCycle <= maxDuty; dutyCycle++) {
    ledcWrite(canal0, dutyCycle);            // Escribir en canal 0
    ledcWrite(canal1, maxDuty - dutyCycle); // Escribir complementario en canal 1
    delay(10);
  }

  // Decrementar brillo en LED 1 e incrementar en LED 2
  for (int dutyCycle = maxDuty; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(canal0, dutyCycle);            // Escribir en canal 0
    ledcWrite(canal1, maxDuty - dutyCycle); // Escribir complementario en canal 1
    delay(10);
  }
}
// 4.3
#include <Arduino.h>

#define LED_PIN_1 25   // Pin DAC 1
#define LED_PIN_2 26   // Pin DAC 2

const int minBrightness = 0;    // Voltaje mínimo (0V)
const int maxBrightness = 255;  // Voltaje máximo (3.3V)
const int fadeSpeed = 5;        // Incremento para acelerar la animación

void setup() {
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
}

void loop() {
  // Transición 1: LED 1 disminuye de brillo, LED 2 aumenta de brillo
  for (int b1 = maxBrightness, b2 = minBrightness; b1 >= minBrightness; b1 -= fadeSpeed, b2 += fadeSpeed) {
    analogWrite(LED_PIN_1, b1);
    analogWrite(LED_PIN_2, b2);
    delay(20);
  }

  // Transición 2: LED 1 aumenta de brillo, LED 2 disminuye de brillo
  for (int b1 = minBrightness, b2 = maxBrightness; b2 >= minBrightness; b1 += fadeSpeed, b2 -= fadeSpeed) {
    analogWrite(LED_PIN_1, b1);
    analogWrite(LED_PIN_2, b2);
    delay(20);
  }
}
//4.4
#include <Arduino.h>

const int motor1 = 18;
const int motor2 = 19;

const int freq = 30000;
const int canalPWM1 = 0;
const int canalPWM2 = 1;
const int resolucion = 8;

void setup()
{
  // Configurar la señal PWM
  ledcSetup(canalPWM1, freq, resolucion);
  ledcSetup(canalPWM2, freq, resolucion);

  // Asignar los pines a sus respectivos canales PWM
  ledcAttachPin(motor1, canalPWM1);
  ledcAttachPin(motor2, canalPWM2);
}

void loop()
{
  // Resetear estados: Motor detenido en ambos sentidos
  int ciclo1 = 0;
  int ciclo2 = 0;
  ledcWrite(canalPWM1, 0);
  ledcWrite(canalPWM2, 0);

  // Aumentar la velocidad progresivamente en el primer sentido
  while (ciclo1 < 255)
  {
    ledcWrite(canalPWM1, ciclo1);
    ciclo1 = ciclo1 + 5;
    delay(250);
  }
  delay(2000);

  // Detener motor antes de invertir el sentido
  ledcWrite(canalPWM1, 0);
  ledcWrite(canalPWM2, 0);

  // Aumentar la velocidad progresivamente en el sentido contrario
  while (ciclo2 < 255)
  {
    ledcWrite(canalPWM2, ciclo2);
    ciclo2 = ciclo2 + 5;
    delay(250);
  }
  delay(2000);
}