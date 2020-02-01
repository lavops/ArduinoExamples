#include <Keypad.h>
#include <TM1637.h>

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define CLK 10//Pins for TM1637       
#define DIO 11
 
TM1637 tm1637(CLK,DIO); 

int znaci[4], znak;

void prikaz()
{
  for(int i = 3; i > 0; i--)
  {
    znaci[i] = znaci[i - 1];
    tm1637.display(i,znaci[i]); 
  }
  znaci[0] = znak;
  tm1637.display(0,znak); 
}

void setup()
{
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); 
   Serial.begin(9600);
}
  
void loop()
{
  char key = keypad.getKey();
  
  if (key)
  {
    znak = key - 48;
    switch(key)
    {
      case 'A':
        znak = 10;
        break; 
      case 'B':
        znak = 11;
        break;
      case 'C':
        znak = 12;
        break;
      case 'D':
        znak = 13;
        break;
      case '*':
        znak = 14;
        break;
      case '#':
        znak = 15;
        break;
    }
    
    prikaz();
    Serial.println(key);
    Serial.println(znak);
  }
}
