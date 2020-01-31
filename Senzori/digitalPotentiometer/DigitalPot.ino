#include <SPI.h>
byte address = 0x00;
int CS= 10;
int i=0;
int pauza = 300;

void setup()
{  
  pinMode (CS, OUTPUT);
  SPI.begin();  
}

void loop()
{  
    for (i = 0; i <= 128; i++)
    {
      digitalPotWrite(i);
      delay(pauza);
    }
    delay(500);    
    for (i = 128; i >= 0; i--)
    {
      digitalPotWrite(i);
      delay(pauza);
    }
}

int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}

