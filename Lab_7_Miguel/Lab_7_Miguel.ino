 /*
  Laboratorio 7

  Miguel García  
  17560
  Electrónica digital 2
  Sección: 20

*/

#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

File root;
char a;
int cont = 1;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("INICIANDO SD DE MIGUEL");

  if (!SD.begin(10)) {
    Serial.println("FALLO INICIALIZACIÓN");
    while (1);
  }
  Serial.println("INICIALIZACIÓN COMPLETA");
  Serial.println("");
  mostrar_arch();

}
void loop() {
  // put your main code here, to run repeatedly:
  
  while(!Serial.available()){
  }
  
  a = Serial.read();
  Serial.print("Su opción es:");
  Serial.print("\t");
  Serial.println(a);
  delay(1000);


}


void leer_arch(char a){
  
}


void mostrar_arch(void){
  root = SD.open("/");
  Serial.println("---------------------------------------------");
  Serial.println("NOMBRE                TAMAÑO         NÚMERO |");
  Serial.println("---------------------------------------------");
  printDirectory(root, 0);
  Serial.println("---------------------------------------------");
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      //Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.print(entry.size(), DEC);
      Serial.print("\t\t");
      Serial.println(cont++);
    }
    entry.close();
  }
}
