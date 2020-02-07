#include<Wire.h>
#define PCF8591 (0x90 >> 1)
#define PCF8591_DAC_ENABLE 0x40
#define PCF8591_ADC_CH0 0x40
#define PCF8591_ADC_CH1 0x41
#define PCF8591_ADC_CH2 0x42
#define PCF8591_ADC_CH3 0x43
byte trenutnaTacka=1;
int brojTacaka;
int interval;
int i;
int podeok;
byte upisi(byte args)
{
  Wire.beginTransmission(PCF8591);
  Wire.write(PCF8591_DAC_ENABLE);
  Wire.write(args);
  Wire.endTransmission();
}
byte temp;
void setup() 
{
  Serial.begin(9600);
  Wire.begin();
}

void loop() 
{
  if(Serial.available())
  {
    String komanda = Serial.readString();
    int indeks = komanda.indexOf(' ');
    int duzina = komanda.length();
    brojTacaka = komanda.substring(0,indeks).toInt();
    interval = komanda.substring(indeks+1,duzina).toInt();
    podeok = 255/brojTacaka;
    trenutnaTacka=0;
    for(i=0;i<2*brojTacaka;i++)
    {
      upisi(trenutnaTacka);
      Serial.print(trenutnaTacka);
      Wire.beginTransmission (0x48); 
      Wire.write (0x42); 
      Wire.endTransmission ();
      Wire.requestFrom (0x48, 3); 
      while (Wire.available ()) 
      { 
        temp = Wire.read(); 
      }
      Serial.println(" " + String(int(temp)));
      if(i<brojTacaka)
        trenutnaTacka+= podeok;
      else
        trenutnaTacka-=podeok;
      delay(interval);
    }
    
  }

}
