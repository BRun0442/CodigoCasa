#include "BluetoothSerial.h"

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
//void ligaLedBT();
                                                                                                             
bool cozinhaLigado = false;
bool salaLigado = false;
bool quartoLigado = false;

//void ligaLedUltrassonico(int distancia);
int distanciaLigaLed = 20; //centímetros

BluetoothSerial SerialBT;


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


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  SerialBT.begin("casaTCC");
  // initialize digital pin LED_BUILTIN as an output.

  
  
  pinMode(pinoCozinha, OUTPUT);
  pinMode(pinoSala, OUTPUT);
  pinMode(pinoQuarto, OUTPUT);//led

  //O código buga nesta parte
  //pinoLedUltrassonico, OUTPUT);
  //pinMode(PinoEcho,INPUT);
  //pinMode(PinoTrigger,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  /*Serial.println("loop");
  digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);             // wait for a second
  digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); */    


  //Caso meu monitor serial receba algo ele envia essses pacotes para o bluetooth
  if(Serial.available()){
    SerialBT.write(Serial.read());
    Serial.println("SERIAL\n");
  }

  //Caso eu receba algo do bluetooth eu vou ler o que foi recebido
  if(SerialBT.available()) {
    Serial.println(SerialBT.read());
    //ligaLedBT(SerialBT.read());

    //COZINHA
    if(SerialBT.read() == 'a'){
      cozinhaLigado = !cozinhaLigado;
      digitalWrite (pinoCozinha, cozinhaLigado);  
    }
    
    //SALA
    if(SerialBT.read() == 'b'){
      salaLigado = !salaLigado;
      digitalWrite (pinoSala, salaLigado);  
    }
    
    //QUARTO
    if(SerialBT.read() == 'c'){
      quartoLigado = !quartoLigado;
      digitalWrite (pinoQuarto, quartoLigado);  
    }
  }
}
