#include <esp32dacFast.h>

#define SAM 64 //resolução da amostragem - sample resolution!
//Maiores resoluções resultam em menores frenquencias maximas! -Greather resolutions results on smaller max frequencies
float values[SAM];
uint8_t tvalues[SAM];
uint8_t tvaluesCopia[SAM];
int in,fi;
float freq = 10;
float periodo;
int per = 1;
int perCopia = 1;
SemaphoreHandle_t semaph;

void geraOnda(int tipo)
{
  if(tipo == 1) //onda seno/ sine wave
  {
    for(int i=0;i<SAM;i++)
    {
      values[i] = (1 + sin(2*3.14*i/SAM))/2;
      tvalues[i] = values[i] * SAM;
    }
  }
  if(tipo == 2) //onda quadrada/ square wave
  {
    for(int i=0;i<(SAM/2);i++)
    {
      tvalues[i] = SAM-1;
    }
    for(int i=(SAM/2);i<SAM;i++)
    {
      tvalues[i] = 0;
    }
  }
  if(tipo == 3) //onda serra / sawtooth wave
  {
    for(int i=0;i<SAM;i++)
    {
      tvalues[i] = i;
    }
  }
}

void confereEntradas(void *p)
{
  while(1)
  {
      xSemaphoreTake(semaph,10);
      freq = 1 + analogRead(4);
      freq = map(freq,1,4096,1,5000);
      periodo = 1.0/freq;
      periodo = periodo/SAM;
      periodo = periodo*1000000;
      per = (int)periodo;
      xSemaphoreGive(semaph);
      delay(50);
  }
}


void setup() {
   Serial.begin(115200);
   geraOnda(1); //set here the type of wave you want! Fell free to implement a touch button to control it!
   //Acima você coloca o tipo de onda que quer, sinta-se a vontade para implementar um botão touch para controlar isso
   dacAttachPin(25);
   semaph = xSemaphoreCreateBinary();
   xTaskCreate(confereEntradas,"confereEntradas",10000,NULL,0,NULL); // Create a task to read the potentiomenter that controls the frequency
}

void loop() {
  xSemaphoreTake(semaph,1);
  perCopia = per;
  xSemaphoreGive(semaph);
  for(int i=0;i<SAM;i++)
  {
    dacFastWrite25(tvalues[i]);
    delayMicroseconds(perCopia);
  }
}
