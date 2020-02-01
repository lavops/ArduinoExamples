#include "TM1637.h"

//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//0~9,A,b,C,d,E,F 

#define CLK 10//Pins for TM1637       
#define DIO 11
 
TM1637 tm1637(CLK,DIO); 

void setup()
{
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); 
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  Serial.begin(9600);  
  tm1637.display(0,1);
  tm1637.display(1,2);
  tm1637.display(2,3);
  tm1637.display(3,4);
}

void loop()
{
  
}
