#include <SPI.h>
const byte address = 0x00;
const int CS = 10, levi = 2, desni = 3, brojacMax = 20, brojacMin = 0, rMin = 0, rMax = 128, r = 5, g = 6, b = 9;
int stanje = 0, faza = 0, brojac = 0, rKorak, proizvod, trecina, crveni, crveniMax, zeleni, zeleniMax, plavi, plaviMax;
boolean levo, desno, smer;

void setup() 
{  
  rKorak = (rMax - rMin)/(brojacMax - brojacMin);
  pinMode (CS, OUTPUT);
  pinMode(levi,INPUT);
  pinMode(desni, INPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  SPI.begin();   
  brojac = (brojacMax - brojacMin) / 2;
  proizvod = brojac * rKorak;
  digitalPotWrite(proizvod);
  trecina = (brojacMax - brojacMin) / 3;
  analogWrite(r, 255);
  analogWrite(g, 255);
  analogWrite(b, 255);
}

void loop() 
{
  levo = digitalRead(levi);
  desno = digitalRead(desni);

  if(levo && desno && faza != 3)
    faza = 0;
    
  if(levo && desno && faza == 3)
  {
    faza = 0;
    
    if(smer)  
    {  
      if(brojac < brojacMax)
        brojac++;       
    }   
    else    
    {
      if(brojac > brojacMin)
        brojac--;      
    }
    proizvod = brojac * rKorak;
    digitalPotWrite(proizvod); 
    if(brojac <= trecina)
      digitalWrite(r, 0);
    else
      digitalWrite(r, 1);
    if(brojac > trecina && brojac <= (2 * trecina))
      digitalWrite(g, 0);
    else
      digitalWrite(g, 1);
    if(brojac > (2 * trecina))
      digitalWrite(b, 0);
    else
      digitalWrite(b, 1);
  }
  
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

  if(faza == 1 && !levo && !desno)
    faza = 2;

  if(faza == 2 && !smer && levo && !desno)
    faza = 3;

  if(faza == 2 && smer && !levo && desno)
    faza = 3;

  delay(1);  
}

int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
