
const int taster = 2, rele = 5, pauza = 3000;
bool pritisnut, pritisnutOld = false;

void setup() 
{
    pinMode(taster, INPUT_PULLUP);
    pinMode(rele, OUTPUT);
}

void loop() 
{
  pritisnut = !digitalRead(taster);
    
  if(pritisnut and !pritisnutOld)
  {
    digitalWrite(rele, HIGH);
    delay(pauza);
    digitalWrite(rele, LOW);
  }
  
  pritisnutOld = pritisnut;
    
}
