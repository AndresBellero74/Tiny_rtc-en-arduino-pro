// Lectura de FEcha y hora
#include <Wire.h>

// Declaracion de las variables para almacenar informacion de tiempo leida desde RTC
uint8_t second, minute, hour, wday, day, month, year, ctrl;

/**
   Inicio del sketch: Este codigo se ejecuta al conectar el arduino
*/
void setup() {

  // Configurar la comunicacion a 9600 baudios
  Serial.begin(9600);

  // Preparar la librería Wire (I2C)
  Wire.begin();

  // Imprimir encabezado a la terminal
  Serial.println("----------------------------------------------------");
  Serial.println("EJEMPLO LECTURA RTC EN TINYRTC CON ARDUINO          ");
  Serial.println("FBELLSAN - Informatica                              ");
  Serial.println("----------------------------------------------------");
}

void loop() {
  // Esperar 1 segundo
  delay(1000);

  // Leer los registros del RTC
  if (read_tinyRTC()) {
    // Mostrar la fecha y hora
    print_time();
  } else {
    // No se puede leer desde le tinyRTC (NACK en I2C)
    Serial.println("No se detecta el tinyRTC, revisar conexiones");
  }
}

/**
   Esta funcion establece la cominicación con el tinyRTC y lee los registros
   de fecha y hora. Entrega la informacion horaria en las variables globales
   declaradas al principio del sketch.
*/
bool read_tinyRTC()
{
  // Iniciar el intercambio de información con el tinyRTC (0xD0)
  Wire.beginTransmission(0x68);

  // Escribir la dirección del segundero
  Wire.write(0x00);

  // Terminamos la escritura y verificamos si el tinyRTC respondio
  // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
  if (Wire.endTransmission() != 0)
    return false;

  // Si el tinyRTC esta presente, comenzar la lectura de 8 bytes
  Wire.requestFrom(0x68, 8);

  // Recibimos el byte del registro 0x00 y lo convertimos a binario
  second = bcd2bin(Wire.read());
  minute = bcd2bin(Wire.read()); // Continuamos recibiendo cada uno de los registros
  hour = bcd2bin(Wire.read());
  wday = bcd2bin(Wire.read());
  day = bcd2bin(Wire.read());
  month = bcd2bin(Wire.read());
  year = bcd2bin(Wire.read());

  // Recibir los datos del registro de control en la dirección 0x07
  ctrl = Wire.read();

  // Operacion satisfactoria, retornamos verdadero
  return true;
}

/**
   Esta función convierte un número BCD a binario. Al dividir el número guardado
   en el parametro BCD entre 16 y multiplicar por 10 se convierten las decenas
   y al obtener el módulo 16 obtenemos las unidades. Ambas cantidades se suman
   para obtener el valor binario.
*/
uint8_t bcd2bin(uint8_t bcd)
{
  // Convertir decenas y luego unidades a un numero binario
  return (bcd / 16 * 10) + (bcd % 16);
}

/**
   Imprime la fecha y hora al monitor serial de arduino
*/
void print_time()
{
  Serial.print("Fecha: ");
  Serial.print(day);
  Serial.print('/');
  Serial.print(month);
  Serial.print('/');
  Serial.print(year);

  Serial.print("  Hora: ");
  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(':');
  Serial.print(second);

  Serial.println();
}
