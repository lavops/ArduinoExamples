const int signal = 5;
bool pokret, pokretOld = false;
int n, brojacPokreta = 0;

void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    n = analogRead(signal);
    if(n > 511)
      pokret = false;
    else
      pokret = true;
    
    if(pokret and !pokretOld)
    {
      brojacPokreta++;
      Serial.println("Pokret: " + String(brojacPokreta));
    }
    pokretOld = pokret;
}
