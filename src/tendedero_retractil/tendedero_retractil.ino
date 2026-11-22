#include <Servo.h>

// Pines de conexion en Arduino Uno
const int PIN_SENSOR_AGUA = A0;     // Pin S (senal analogica) del sensor HW-038
const int PIN_SERVO = 3;            // Pin PWM para el servomotor

// Calibracion del sensor HW-038 (0 = seco, valores altos = agua detectada)
const int UMBRAL_LLUVIA = 100;      // Ajustar segun pruebas fisicas con gotas
const int LECTURA_MAX_AGUA = 650;   // Referencia aproximada para calcular porcentaje

// Angulos del tendedero retractil (ajustar segun la maqueta fisica)
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
  Serial.println("  Sensor: Nivel de agua HW-038                     ");
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

  if (lecturaAgua >= UMBRAL_LLUVIA) {
    Serial.println("LLUVIA DETECTADA -> Resguardando tendedero (90 grados)");
    if (!tendederoResguardado) {
      servoTendedero.write(ANGULO_CERRADO);
      tendederoResguardado = true;
    }
  } else {
    Serial.println("SIN LLUVIA -> Tendedero extendido (0 grados)");
    if (tendederoResguardado) {
      servoTendedero.write(ANGULO_ABIERTO);
      tendederoResguardado = false;
    }
  }

  delay(INTERVALO_LECTURA_MS);
}
