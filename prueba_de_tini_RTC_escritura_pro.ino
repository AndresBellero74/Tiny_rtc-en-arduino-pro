// Programa de escritura RTC
#include <Wire.h>

// Declaracion de las variables para almacenar informacion de tiempo
uint8_t second, minute, hour, wday, day, month, year;


void setup() {

  // NOTA: Estas sentencias se requieren para alimentar directamente el
  // chip RTC desde los pines A3 Y A2 (colocar directamente el modulo sobre
  // la tarjeta arduino, sin la necesidad de cablear en Arduino UNO).
  // Si no se quiere hacer esto, se pueden eliminar o comentar sin problemas
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);

  // Configurar la comunicacion a 9600 baudios
  Serial.begin(9600);

  // Preparar la librería Wire (I2C)
  Wire.begin();

  // Imprimir encabezado a la terminal
  Serial.println("----------------------------------------------------");
  Serial.println("       EJEMPLO ESCRITURA TINYRTC CON ARDUINO        ");
  Serial.println("            FBELLSAN-Informatica                    ");
  Serial.println("----------------------------------------------------");

  // colocar la fecha y hora a definir en el rtc
  second = 00;
  minute = 04;
  hour = 19;
  wday = 4;
  day = 26;
  month = 4;
  year = 21;
}

void loop() {
  // Escribir hora y fecha al RTC
  write_tinyRTC();

  // Imprimimos la fecha y hora
  Serial.println("Poner a tiempo el Tiny RTC:");
  print_time();

  for (;;);
}

bool write_tinyRTC()
{
  // Iniciar el intercambio de información con el tinyRTC (0x68)
  Wire.beginTransmission(0x68);

  // Escribir la dirección del registro segundero
  Wire.write(0x00);

  Wire.write(bin2bcd(second & 0x7F)); 
  Wire.write(bin2bcd(minute));
  Wire.write(bin2bcd(hour));
  Wire.write(bin2bcd(wday));
  Wire.write(bin2bcd(day));
  Wire.write(bin2bcd(month));
  Wire.write(bin2bcd(year));

  // Terminamos la escritura y verificamos si el tinyRTC respondio
  // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
  if (Wire.endTransmission() != 0)
    return false;

  // Retornar verdadero si se escribio con exito
  return true;
}

/**
   Convierte un numero binario a BCD
*/
uint8_t bin2bcd(uint8_t bin)
{
  return (bin / 10 * 16) + (bin % 10);
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
  Serial.print("20");
  Serial.print(year);

  Serial.print("  Hora: ");
  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(':');
  Serial.print(second);

  Serial.println();
}
