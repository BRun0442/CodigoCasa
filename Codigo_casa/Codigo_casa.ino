#include "BluetoothSerial.h"

//Ultrassonico
#define PinoTrigger 34
#define PinoEcho 35
int duracao = 0;
int distanciaSensor = 0;
int distanciaLigaLed = 20; //centímetros

#define ligaledCozinha 'a'
#define ligaledSala 'b'
#define ligaledQuarto 'c'

#define pinoCozinha 12
#define pinoSala 13
#define pinoQuarto 14
#define ledUltrassonico 27
                                                                                                             
bool cozinhaLigado = false;
bool salaLigado = false;
bool quartoLigado = false;


BluetoothSerial SerialBT;
void serialRead();
void ligaLedBT();
void ligaLedUltrassonico();


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);  
  Serial.println("setup");
  SerialBT.begin("casaTCC");
  
  
  pinMode(pinoCozinha, OUTPUT);
  pinMode(pinoSala, OUTPUT);
  pinMode(pinoQuarto, OUTPUT);

  //O código buga nesta parte
  pinMode(ledUltrassonico, OUTPUT);
  pinMode(PinoEcho,INPUT);
  pinMode(PinoTrigger,OUTPUT);
}

void loop() {
  /*Serial.println("loop");
  digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);             // wait for a second
  digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); */ 
  Serial.print("loop");
  ligaLedUltrassonico();
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

void ligaLedUltrassonico()
{ 
  //Da varios pulsos no pino trigger
  digitalWrite(PinoTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinoTrigger,LOW);


  //Leitura e armazenamento do Trigger
  duracao = pulseIn(PinoEcho, HIGH);
  distanciaSensor = duracao*0.017175;
  Serial.print(distanciaSensor);
  Serial.println("cm");  

 
  //Caso a distancia que o ultrassonico esteja marcando
  //for menor que a distancia pré-definida ele aciona o led
  if(distanciaSensor >= distanciaLigaLed)
  {
    digitalWrite(ledUltrassonico, HIGH);
  }else{
    digitalWrite(ledUltrassonico, LOW);
  }
}

void ligaLedBT()
{
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
