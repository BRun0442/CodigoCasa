//#include "BluetoothSerial.h"
#include <SoftwareSerial.h>

#define ligaledCozinha 'a'
#define ligaledSala 'b'
#define ligaledQuarto 'c'
#define ligaledBanheiro 'd'

#define pinoCozinha 12
#define pinoSala 13
#define pinoQuarto 14
#define pinoBanheiro 27
                                                                                                             
bool cozinhaLigado = false;
bool salaLigado = false;
bool quartoLigado = false;
bool banheiroLigado = false;

//BluetoothSerial SerialBT;
SoftwareSerial SerialBT(10, 11); // RX, TX do Arduino

void setup() {
  Serial.begin(115200);
  SerialBT.begin("casa");
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(pinoCozinha, OUTPUT);
  pinMode(pinoSala, OUTPUT);
  pinMode(pinoQuarto, OUTPUT);
  pinMode(pinoBanheiro, OUTPUT);
  
}
void loop() {
  //Caso meu monitor serial receba algo ele envia essses pacotes para o bluetooth
  if(Serial.available()){
    SerialBT.write(Serial.read());
  }

  //Caso eu receba algo do bluetooth eu vou ler o que foi recebido
  if(Serial.available()) {
    Serial.write(SerialBT.read());

    //COZINHA
    if(SerialBT.read() == ligaledCozinha){
      cozinhaLigado = !cozinhaLigado;
      digitalWrite (pinoCozinha, cozinhaLigado);  
    }
  
    //SALA
    if(SerialBT.read() == ligaledSala){
      salaLigado = !salaLigado;
      digitalWrite (pinoSala, salaLigado);  
    }
  
    //QUARTO
    if(SerialBT.read() == ligaledQuarto){
      quartoLigado = !quartoLigado;
      digitalWrite (pinoQuarto, quartoLigado);  
    }
  
    //BANHEIRO
    if(SerialBT.read() == ligaledBanheiro){
      banheiroLigado = !banheiroLigado;
      digitalWrite (pinoBanheiro, banheiroLigado);  
    }
  }
  
  delay(20);
 }
