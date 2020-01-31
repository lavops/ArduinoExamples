#include "DHT.h"
#include "TM1637.h"

//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//0~9,A,b,C,d,E,F
 

 
#define DHTPIN 2
#define DHTTYPE DHT11
#define CLK 10//Pins for TM1637       
#define DIO 11
 
TM1637 tm1637(CLK,DIO);
DHT dht(DHTPIN, DHTTYPE);
 

void setup(){
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
 
  delay(1500);
}
 

 
void loop(){

 int temp = (int)dht.readTemperature();
 int humidity = (int)dht.readHumidity();
 
 int digitoneT = temp / 10;
 int digittwoT = temp % 10;
 
 int digitoneH = humidity / 10;
 int digittwoH = humidity % 10;
  

    tm1637.display(1,digitoneT); 
    tm1637.display(2,digittwoT);
    tm1637.display(3,12);
    
    delay (3000);

    tm1637.display(1,16);
    tm1637.display(2,digitoneH); 
    tm1637.display(3,digittwoH);

    delay(3000);
 
}
