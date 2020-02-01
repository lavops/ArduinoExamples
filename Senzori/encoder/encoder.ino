int levi = 2, desni = 3, stanje = 0, faza = 0, brojac = 0;
const int brojacMax = 10, brojacMin = 0;
boolean levo, desno, smer;
void setup() 
{
  pinMode(levi,INPUT);
  pinMode(desni, INPUT);
  Serial.begin(9600);
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
      if(brojac > brojacMin)
        brojac--;      

    Serial.println(brojac);
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
