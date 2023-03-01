#include <Arduino.h>
// Including LIN Stack library
#include <lin_stack.h>
#include <DueTimer.h>

#define L_PLAY 10
#define L_PAUSE 11
#define L_STOP 12
byte togle = 1;

lin_stack LIN1(1); // 1 - channel, ident - Identification Byte

bool ledOn = false;
uint8_t counterR = 0;
uint8_t counterG = 0;
uint8_t counterB = 0;
void LinSend(int adress, byte intensidad, byte Rojo, byte Verde, byte Azul, byte diming, byte grupo);
void Timerled();

void setup()
{
  // put your setup code here, to run once:

  pinMode(8, OUTPUT);    // LIN 8
  digitalWrite(8, HIGH); // LIN 8
  pinMode(13, OUTPUT);

  Serial.begin(9600);

  // retroiluminados
  pinMode(L_PLAY, OUTPUT);
  pinMode(L_PAUSE, OUTPUT);
  pinMode(L_STOP, OUTPUT);

  Timer3.attachInterrupt(Timerled);
  Timer3.start(500000); // Calls every 500ms
}

void loop()
{
  // put your main code here, to run repeatedly:

  LinSend(16383, 100, 0, 255, 0, 0, 1);
  delay(500);
  for (int i = 0; i < 15; i++)
  {
    if ((i % 3) != 0)
    {

      LinSend(16383, 100, 255, 0, 0, 0, 1);
      delay(500);
    }
    else if ((i % 6) != 0)
    {

      LinSend(16383, 100, 0, 0, 255, 0, 1);
      delay(500);
    }
    else
    {
      LIN1.writeRequest(i);
      delay(20);
    }
    
  }

  // if(counter < 20){
  // LIN1.writeRequest(0x0E);

  // delay(100);
}

void Timerled()
{
  ledOn = !ledOn;
  digitalWrite(L_PAUSE, ledOn);
}

void LinSend(int adress, byte intensidad, byte Rojo, byte Verde, byte Azul, byte diming, byte grupo)
{

  byte adress1, adress2;
  byte intensidadlin = map(intensidad, 0, 100, 128, 228);
  byte diminglin = map(diming, 0, 100, 16, 31); // 0.25segundos cada 1 valor hasta 31

  if (grupo == 0)
  {
    adress1 = adress;
    adress2 = 0x00;
  }
  if (grupo == 1)
  {
    adress1 = adress & 0xff;
    adress2 = ((adress >> 8) & 0xff) | (grupo << 7);
  }

  if (Rojo > 255)
    Rojo = 255;
  if (Verde > 255)
    Verde = 255;
  if (Azul > 255)
    Azul = 255;
  if (intensidadlin > 228)
    intensidadlin = 228;
  if (diminglin > 31)
    diminglin = 31;

  if (Rojo < 0)
    Rojo = 0;
  if (Verde < 0)
    Verde = 0;
  if (Azul < 0)
    Azul = 0;
  if (intensidadlin < 128)
    intensidadlin = 128;
  if (diminglin < 16)
    diminglin = 16;

  byte lindataframe[] = {adress1, adress2, Rojo, Verde, Azul, intensidadlin, diminglin, 0xFE};

  LIN1.write(0x15, lindataframe, 8); // Write data to LIN
}
