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


// Variables
File root;
File myFile;
char a;
char b;
char c;
char d;
int cont = 2;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

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
  Serial.println("Escriba el número de archivo que desea abrir:");
  c = Serial.read();
  while(!Serial.available());
  
  a = Serial.read();
  Serial.print("Su opción es:");
  Serial.print("\t");
  Serial.println(a);
  delay(500);

  leer_arch(a);
  c = Serial.read();
  Serial.println("Desea volver a mostrar la lista de archivos:");
  Serial.println("1 = Sí   1> = No");
  
  while(!Serial.available());
  b = Serial.read();
  if(b == 49){
    cont = 2;
    mostrar_arch();
    c = Serial.read();
    }
  if(b>49){
    Serial.println("No"); 
    c = Serial.read();
    while(!Serial.available());
  }
  

}


void leer_arch(char a){
  if (a == 52){
    myFile = SD.open("spider~1.txt");
    Serial.println("");
    Serial.println("spider~1.txt:");
    Serial.println("");
  }
  if (a == 53){
    myFile = SD.open("corazon.txt");
    Serial.println("");
    Serial.println("corazon.txt:");
    Serial.println("");
  }

  if (a == 54){
    myFile = SD.open("deadpool.txt");
    Serial.println("");
    Serial.println("deadpool.txt:");
    Serial.println("");
  }

  if (a == 55){
    myFile = SD.open("hongo.txt");
    Serial.println("");
    Serial.println("hongo.txt:");
    Serial.println("");
  }
  
  if (myFile) {
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    Serial.println("");
    // close the file:
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
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
