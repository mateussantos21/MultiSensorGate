// ligar relé da esquerda no 7 e o da direita no 8
// ligar chave da porta fechada no 12 e aberta no 13

//fim de curso
int fechada = 12; //recebe a chave que indica a porta fechada 0 = chave pressionada
int aberta = 13;  //recebe a chave que indica a porta aberta 0 = chave pressionada

//ponte
int r1 = 7;
int r2 = 2;

//fotodiodo
int pdpin = A0;


//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);


void setup() {
  Serial.begin(9600);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(fechada, INPUT);
  pinMode(aberta, INPUT);
}

float leultra() {
  long microsec = ultrasonic.timing();
  float us = ultrasonic.convert(microsec, Ultrasonic::CM);
  return us;
}

int lefoto() {
  int pd = analogRead(pdpin);
  return pd;
}

void abre() {
  int ab = digitalRead(13);
  digitalWrite(r2, HIGH);
  while (ab == 1) {
    ab = digitalRead(13);
  }
  digitalWrite(r2, LOW);
}

void fecha() {
  int fe = digitalRead(12);
  digitalWrite(r1, HIGH);
  while (fe == 1) { //enquanto não fechar
    float a = leultra();
    int b = lefoto();
    if (a <= 10 || b <= 15) {    //se aparecer objeto no ultrasson ou obstaculo na porta
      digitalWrite(r1, LOW);     //desliga a porta e abre de novo
      abre();
      delay(5000);  
      break;
    }
    fe = digitalRead(12);
  }
  digitalWrite(r1, LOW);
}

void loop() {
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  float x = leultra();
  int y = lefoto();
  int i = digitalRead(12);
  int j = digitalRead(13);
  if (i == 0  && x <= 10) { //se a porta estiver fechada e le o ultrasson, se tiver objeto
      abre();
      delay(5000);
  }
  if (j == 0) {   //se a porta estiver aberta
    fecha();
  }
}
