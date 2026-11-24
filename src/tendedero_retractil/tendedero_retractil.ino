#include <Servo.h>

// Pines de conexion en Arduino Uno
const int PIN_SENSOR_AGUA = A0;     // Pin S (senal analogica) del sensor HW-038
const int PIN_SERVO = 3;            // Pin PWM para el micro servomotor Steren MOT-100

// Calibracion del sensor HW-038 basada en pruebas fisicas
// (0 = seco, 551-630 = agua detectada sobre las pistas)
const int UMBRAL_LLUVIA = 100;      // Umbral para activar resguardo
const int UMBRAL_SECO = 50;         // Umbral inferior (histeresis) para evitar vibraciones al reabrir
const int LECTURA_MAX_AGUA = 630;   // Valor maximo observado en pruebas para calcular porcentaje

// Angulos del tendedero retractil con servomotor Steren MOT-100 (0 a 180 grados)
const int ANGULO_ABIERTO = 0;       // Posicion extendida (sin lluvia)
const int ANGULO_CERRADO = 90;      // Posicion resguardada (lluvia detectada)

// Tiempo entre lecturas en milisegundos
const unsigned long INTERVALO_LECTURA_MS = 1000;

Servo servoTendedero;
bool tendederoResguardado = false;

void setup() {
  servoTendedero.attach(PIN_SERVO);
  servoTendedero.write(ANGULO_ABIERTO);

  Serial.begin(9600);
  Serial.println("===================================================");
  Serial.println("  Sistema de Tendedero Retractil Automatico (UNO)  ");
  Serial.println("  Sensor: HW-038 | Actuador: Servo Steren MOT-100  ");
  Serial.println("===================================================");
  Serial.println("Estado inicial: Tendedero extendido (0 grados)");
}

void loop() {
  int lecturaAgua = analogRead(PIN_SENSOR_AGUA);
  int porcentajeAgua = map(lecturaAgua, 0, LECTURA_MAX_AGUA, 0, 100);
  porcentajeAgua = constrain(porcentajeAgua, 0, 100);

  Serial.print("Lectura HW-038: ");
  Serial.print(lecturaAgua);
  Serial.print(" | Nivel aprox.: ");
  Serial.print(porcentajeAgua);
  Serial.print("% | Estado: ");

  if (!tendederoResguardado && lecturaAgua >= UMBRAL_LLUVIA) {
    servoTendedero.write(ANGULO_CERRADO);
    tendederoResguardado = true;
    Serial.println("LLUVIA DETECTADA -> Resguardando tendedero (90 grados)");
  } else if (tendederoResguardado && lecturaAgua <= UMBRAL_SECO) {
    servoTendedero.write(ANGULO_ABIERTO);
    tendederoResguardado = false;
    Serial.println("SIN LLUVIA -> Tendedero extendido (0 grados)");
  } else if (tendederoResguardado) {
    Serial.println("LLUVIA DETECTADA -> Tendedero resguardado (90 grados)");
  } else {
    Serial.println("SIN LLUVIA -> Tendedero extendido (0 grados)");
  }

  delay(INTERVALO_LECTURA_MS);
}
