//#include "BluetoothSerial.h"
#include <SoftwareSerial.h>


#define PinoTrigger 6
#define PinoEcho 7
int duracao = 0;
int distanciaSensor = 0;
unsigned long tempoUltrasonico = 0;

#define ligaledCozinha 'a'
#define ligaledSala 'b'
#define ligaledQuarto 'c'

#define pinoCozinha 12
#define pinoSala 13
#define pinoQuarto 14
#define pinoLedUltrassonico 27
                                                                                                             
bool cozinhaLigado = false;
bool salaLigado = false;
bool quartoLigado = false;

void ligaLedUltrassonico(int distancia);
int distanciaLigaLed = 20; //centímetros

//BluetoothSerial SerialBT;
SoftwareSerial SerialBT(10, 11); // RX, TX do Arduino

void setup() {
  Serial.begin(115200);
  SerialBT.begin("casa");
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(pinoCozinha, OUTPUT);
  pinMode(pinoSala, OUTPUT);
  pinMode(pinoQuarto, OUTPUT);
  pinMode(pinoLedUltrassonico, OUTPUT);
  pinMode(PinoEcho,INPUT);
  pinMode(PinoTrigger,OUTPUT);
  
}
void loop() {
  //Acionamento do Trigger
  digitalWrite(PinoTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinoTrigger,LOW);
  

  //Leitura e armazenamento do Trigger
  duracao = pulseIn(PinoEcho, HIGH);
  distanciaSensor = duracao*0.017175;
  //Serial.print(distancia);
  //Serial.println("cm");  

  ligaLedUltrassonico(distanciaSensor);
  
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
  }
  
  delay(10);
}

void ligaLedUltrassonico(int distancia)
{
  //Caso a distancia que o ultrassonico esteja marcando
  //for menor que a distancia pré-definida ele aciona o led
  if(distancia <= distanciaLigaLed)
  {
    digitalWrite(pinoLedUltrassonico, HIGH);
  }else{
    digitalWrite(pinoLedUltrassonico, LOW);
  }
}
