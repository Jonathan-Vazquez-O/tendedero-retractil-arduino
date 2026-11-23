# Sistema de Tendedero Retráctil Automático con Sensor de Agua (HW-038)

Proyecto final de la materia de **Programación** enfocado en resolver una situación cotidiana mediante sensores, microcontrolador Arduino Uno y flujo de trabajo colaborativo con Git y GitHub.

## Integrantes
- **Jonathan Vázquez**
- **Ximena López**

## Problema que atiende y objetivo
**Problema:** En muchos hogares la ropa se seca al aire libre en patios o azoteas. Cuando comienza a llover de forma inesperada y no hay nadie en casa, la ropa vuelve a mojarse, generando pérdida de tiempo y esfuerzo.

**Usuarios y utilidad:** Está dirigido a hogares y pequeños espacios domésticos que utilizan tendederos exteriores. El sistema detecta gotas de agua en tiempo real y acciona un mecanismo retráctil para resguardar la ropa automáticamente sin intervención manual.

**Objetivo:** Desarrollar un prototipo funcional con **Arduino Uno**, un **sensor de nivel de agua HW-038** y un **servomotor** que muestre las lecturas analógicas del sensor en tiempo real, accione el resguardo automático del tendedero al superar el umbral de agua y regrese a su posición abierta cuando la superficie se seque, gestionando todo el desarrollo con Git y GitHub.

## Sensor, lenguaje y herramientas utilizados
- **Microcontrolador:** Arduino Uno (ATmega328P, 5 V).
- **Sensor:** Módulo sensor de nivel de agua **HW-038** (salida analógica `S` proporcional a la presencia de agua sobre sus pistas metálicas).
- **Actuador:** Servomotor SG90 (controlado por señal PWM).
- **Lenguaje de programación:** C/C++ (Arduino) con la librería estándar `Servo.h`.
- **Herramientas:** Arduino IDE, protoboard, cables jumper, Git (control de versiones local) y GitHub (repositorio remoto y colaboración).

**Justificación:** Se eligió C/C++ en Arduino IDE porque permite leer señales analógicas en tiempo real con baja latencia y controlar servomotores directamente sin configuraciones complejas. El sensor HW-038 permite detectar gotas de lluvia con solo 3 pines y calibrar el umbral directamente por software. Git y GitHub permiten documentar el avance real de cada integrante mediante ramas, commits y pull requests.

*Referencia base adaptada de Arduino Nano y sensor de lluvia digital a Arduino Uno con sensor HW-038:* [Rain Detector System | Arduino Project](http://www.youtube.com/watch?v=3WZHMYPsSo8).

## Instrucciones de instalación, conexión y ejecución

### 1. Requisitos de software
1. Instalar **Arduino IDE** desde la página oficial de Arduino.
2. Clonar este repositorio en la computadora:
   ```bash
   git clone https://github.com/Jonathan-Vazquez-O/tendedero-retractil-arduino.git
   ```
3. Abrir el archivo `src/tendedero_retractil/tendedero_retractil.ino` en Arduino IDE.

### 2. Conexión del circuito (Arduino Uno)
Con el Arduino desconectado del puerto USB, realiza las siguientes conexiones usando una protoboard para compartir `5V` y `GND`:

| Componente | Pin | Conexión en Arduino Uno / Protoboard |
| :--- | :--- | :--- |
| Arduino Uno | `5V` | Riel positivo (`+`) de la protoboard |
| Arduino Uno | `GND` | Riel negativo (`-`) de la protoboard |
| Sensor HW-038 | `+` (`VCC`) | Riel positivo (`+`) de la protoboard |
| Sensor HW-038 | `-` (`GND`) | Riel negativo (`-`) de la protoboard |
| Sensor HW-038 | `S` (Señal) | Pin analógico `A0` |
| Servomotor | Rojo (`VCC`) | Riel positivo (`+`) de la protoboard |
| Servomotor | Café / Negro (`GND`) | Riel negativo (`-`) de la protoboard |
| Servomotor | Naranja / Amarillo (Señal) | Pin digital `3` |

### 3. Ejecución
1. Conecta el Arduino Uno por USB a la computadora.
2. En Arduino IDE selecciona **Herramientas → Placa → Arduino Uno** y el puerto correspondiente.
3. Haz clic en **Subir (Upload)**.
4. Abre el **Monitor Serial** (`9600 baudios`) para observar las lecturas del sensor HW-038 y el estado del tendedero en tiempo real.
5. Si deseas mayor o menor sensibilidad a las gotas, ajusta el valor de `UMBRAL_LLUVIA` en el código (por defecto `100`).

## Funcionamiento general y pruebas realizadas
El programa lee cada segundo la salida analógica (`A0`) del sensor HW-038:
- **Sin lluvia (`lectura < UMBRAL_LLUVIA`):** Muestra la lectura cruda y el porcentaje aproximado en el Monitor Serial, manteniendo el servomotor en `0°` (tendedero extendido).
- **Lluvia detectada (`lectura >= UMBRAL_LLUVIA`):** Imprime la alerta en el Monitor Serial y gira el servomotor a `90°` para resguardar el tendedero.
- **Protección contra movimientos repetidos:** Una bandera booleana (`tendederoResguardado`) evita reenviar la posición al servo si ya se encuentra en el estado correcto.

### Registro de pruebas
Pruebas realizadas en **Arduino Uno** con el sensor **HW-038** monitoreado a `9600 baudios`:

| Condición probada | Lectura HW-038 / Nivel (%) | Respuesta esperada del sistema | Resultado observado | Evidencia |
| :--- | :--- | :--- | :--- | :--- |
| 1. Sensor seco | `0` (`0%`) | Mensaje `SIN LLUVIA`, servo en `0°` | Estable en `0` (`0%`), estado `SIN LLUVIA -> Tendedero extendido (0 grados)` | `docs/evidencias/prueba_seco.heic` |
| 2. Lluvia detectada (agua sobre el sensor) | `551` a `630` (`84%` a `96%`) | Mensaje `LLUVIA DETECTADA`, servo gira a `90°` | Subió de `0` a `551–630` (`84%–96%`), cambió a `LLUVIA DETECTADA -> Resguardando tendedero (90 grados)` | `docs/evidencias/prueba_lluvia.heic` |
| 3. Secado / recuperación | `627` → `423–486` → `0` (`96%` → `65%–74%` → `0%`) | Mensaje `SIN LLUVIA`, servo regresa a `0°` | Al retirar el agua bajó a `0` (`0%`) y regresó automáticamente a `SIN LLUVIA -> Tendedero extendido (0 grados)` | `docs/evidencias/prueba_recuperacion.heic` |

## Aportaciones de cada integrante
- **Jonathan Vázquez:** Configuración inicial del repositorio, programación del sistema de lectura del sensor HW-038 y control del servomotor en Arduino Uno, calibración física del mecanismo y revisión/fusión del Pull Request.
- **Ximena López:** Documentación técnica del proyecto en `README.md`, diseño de la tabla de conexiones y protocolo de pruebas, registro de evidencias de funcionamiento y creación del Pull Request en GitHub.

## Limitaciones y posibles mejoras
### Limitaciones actuales
- El prototipo usa un servomotor SG90 pensado para una maqueta ligera; un tendedero real con ropa húmeda requiere un motor con mayor torque y fuente de alimentación externa.
- Las pistas expuestas del sensor HW-038 pueden oxidarse si permanecen energizadas continuamente al exterior.
- El sistema depende del cable USB para alimentación y monitoreo en el Monitor Serial.

### Posibles mejoras
- Agregar un LED indicador y un buzzer para emitir alertas visuales y sonoras al detectar lluvia.
- Incorporar un retardo de confirmación para evitar que el tendedero se abra y cierre repetidamente ante llovizna intermitente.
- Conectar un módulo Wi-Fi (como ESP8266 o ESP32) para enviar notificaciones al celular cuando el tendedero se cierre automáticamente.
