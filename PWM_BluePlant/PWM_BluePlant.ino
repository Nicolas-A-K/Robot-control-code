#include <Arduino.h>
#include <Modbusino.h>

ModbusinoSlave modbusino_slave(1);
uint16_t tab_reg[10];

// motores esquerdo e inferior
#define in1 12
#define in2 13
#define ena 14
#define led 2
// motores direito e inferior
#define in3 5
#define in4 18
#define enb 19
#define ledPin 4

// variáveis
int Bdir;
int vel;
int lum;
int pwm;
int vel2;

void setup()
{
  modbusino_slave.setup(115200);

  // saídas
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(led, OUTPUT);

  // inicializa as variáveis em 0
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  digitalWrite(led, 0);
}

void loop()
{
  if (Bdir == 1)
  { // robô anda para frente
    digitalWrite(led, 1);
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    digitalWrite(in3, 1);
    digitalWrite(in4, 0);
  }
  else
  { // robô anda para trás
    digitalWrite(led, 0);
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);
  }

  vel2 = vel * 2,55; // converte a % do slider em um pwm de até 255;
  
  delay(50);
  analogWrite(ena, vel2);
  delay(25);
  analogWrite(enb, vel2);
  delay(25);

  pwm = map(lum, 0, 255, 255, 0);
  analogWrite(ledPin, pwm);

  vel = tab_reg[0];
  Bdir = tab_reg[1];
  lum = tab_reg[3];
   
  modbusino_slave.loop(tab_reg, 10);
}
