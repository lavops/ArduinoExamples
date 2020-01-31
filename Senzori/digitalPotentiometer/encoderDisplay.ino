#include "TM1637.h"

//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//0~9,A,b,C,d,E,F
 
int levi = 2, desni = 3, faza = 0, brojac = 0;
const int brojacMax = 9999, brojacMin = 0;
boolean levo, desno, smer;
 
#define CLK 4//Pins for TM1637       
#define DIO 5
 
TM1637 tm1637(CLK,DIO); 
 
void prikaz()
{
  int digit1 = (brojac / 1000) % 10;
  int digit2 = (brojac / 100) % 10;
  int digit3 = (brojac / 10) % 10;
  int digit4 = brojac % 10;
  tm1637.display(0,digit1); 
  tm1637.display(1,digit2);
  tm1637.display(2,digit3);
  tm1637.display(3,digit4); 
}

void setup()
{
  pinMode(levi,INPUT);
  pinMode(desni, INPUT);  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); 
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  Serial.begin(9600);  
}
 
void loop()
{
  levo = digitalRead(levi);
  desno = digitalRead(desni);  
  
  if(faza == 0 && !levo && desno)
  {
    smer = false;
    faza = 1;
  }

  if(faza == 0 && levo && !desno)
  {
    smer = true;
    faza = 1;
  }

  if(levo && desno && faza == 1)
  {
    faza = 0;
    if(smer)
      if(brojac < brojacMax)
        brojac++;  
      else 
        brojac = 0;    
    else
      if(brojac > brojacMin)
        brojac--;    
      else 
        brojac = 9999; 

    prikaz();
    Serial.println(brojac);
  }
  
  delay(1); 
}
