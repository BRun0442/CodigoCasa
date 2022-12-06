//#include "BluetoothSerial.h"
#include <SoftwareSerial.h>

#define ligaLedCozinha 'a'
#define ligaLedSala 'b'
#define ligaLedQuarto 'c'
#define ligaLedVaranda 'd'

#define pinoCozinha 12
#define pinoSala 13
#define pinoQuarto 14
#define pinoVaranda 15

bool cozinhaLigado = false;
bool salaLigado = false;
bool quartoLigado = false;
bool varandaLigado = false;


//BluetoothSerial SerialBT;
SoftwareSerial SerialBT(10, 11); // RX, TX do Arduino

void serialRead();
void ligaLedBT();


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);  
  Serial.println("setup");
  SerialBT.begin("casaTCC");
  
  pinMode(pinoCozinha, OUTPUT);
  pinMode(pinoSala, OUTPUT);
  pinMode(pinoQuarto, OUTPUT);
  pinMode(pinoVaranda, OUTPUT);
}

void loop() {
  serialRead();
}

void serialRead()
{
  //Caso o monitor serial receba algo ele envia esses pacotes para o bluetooth
  if(Serial.available()){
    SerialBT.write(Serial.read());
  }

  //Caso receba algo do bluetooth, leia o que foi recebido
  if(SerialBT.available()) {
    Serial.println(SerialBT.read() + "\n\n");
    ligaLedBT();
  }
}

void ligaLedBT()
{
  //COZINHA
  if(SerialBT.read() == ligaLedCozinha){
    cozinhaLigado = !cozinhaLigado;
    digitalWrite (pinoCozinha, cozinhaLigado);  
  }
  
  //SALA
  if(SerialBT.read() == ligaLedSala){
    salaLigado = !salaLigado;
    digitalWrite (pinoSala, salaLigado);  
  }
  
  //QUARTO
  if(SerialBT.read() == ligaLedQuarto){
    quartoLigado = !quartoLigado;
    digitalWrite (pinoQuarto, quartoLigado);  
  }

  //QUARTO
  if(SerialBT.read() == ligaLedQuarto){
    quartoLigado = !quartoLigado;
    digitalWrite (pinoQuarto, quartoLigado);  
  }
}
