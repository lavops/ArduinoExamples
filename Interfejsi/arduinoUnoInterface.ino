/*
Formati za aplikaciju: 

*** Analogni ulaz:
An: n 0-5

*** Analogni PWM izlaz: 
Wnnwww: nn 00 - 13 broj digitalnog kanala, www 000 - 255

*** Digitalni ulaz: 
DInn: nn 00 - 13

*** Digitalni izlaz: 
DOnnb: nn 00 - 13, b 0 /1
*/
char c, m;
String s;
int n, b, w, r;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    c = Serial.read();
    switch(c)
    {
      case 'A':
        //Serial.println("Analog read:");        
        while(!Serial.available()){}
        c = Serial.read();               
        n = (int)c - 48;
        //Serial.println("Channel: " + String(n));
        Serial.println(analogRead(n));        
        break;
      case 'W': 
        //Serial.println("Analog write: ");        
        s = "";
        while(!Serial.available()){}
        c = Serial.read();
        s += c;
        while(!Serial.available()){}
        c = Serial.read();
        s += c;
        n  = s.toInt();
        //pinMode(n, OUTPUT);
        //Serial.println("Channel: " + String(n));
        s = "";
        while(!Serial.available()){}
        c = Serial.read();
        s += c;
        while(!Serial.available()){}
        c = Serial.read();
        s += c;
        while(!Serial.available()){}
        c = Serial.read();
        s += c;        
        w = s.toInt();
        analogWrite(n, w);
        //Serial.println("Upisana vrednost: " + String(w));        
        Serial.println("W OK");
        break;
      case 'D':
        s = "";
        while(!Serial.available()){}
        m = Serial.read();
        while(!Serial.available()){}
        c = Serial.read();
        s += c;
        while(!Serial.available()){}
        c = Serial.read();
        s += c;
        n  = s.toInt();
        if(m == 'I')
        {      
          //Serial.println("Digital input");          
          pinMode(n, INPUT);    
          //Serial.println("Channel: " + String(n));          
          b = digitalRead(n);
          //Serial.println("Ocitana binarna vrednost: " + String(b));
          Serial.println(b);
        }
        else
        {
          //Serial.println("Digital output");          
          pinMode(n, OUTPUT);  
          //Serial.println("Channel: " + String(n));    
          while(!Serial.available()){}  
          c = Serial.read();          
          b = (int)c - 48;
          digitalWrite(n, b);
          //Serial.println("Upisana binarna vrednost: " + String(b));
          Serial.println("D OK");
        }        
        break;
/*        
      case 'R':
        s = "";
        while(!Serial.available()){}  
        m = Serial.read(); 
        while(!Serial.available()){}  
        c = Serial.read();
        s += c;
        while(!Serial.available()){}  
        c = Serial.read();
        s += c;
        r = s.toInt();
        if(m == 'I')
        {
          analogReadResolution(r);
          Serial.println("RI OK");
        }
        else
        {
          analogWriteResolution(r);
          Serial.println("RW OK");
        }
        break;
        
      case 'C':
        s = "";
        while(!Serial.available()){}  
        c = Serial.read();
        n = (int)(c - 48);
        while(!Serial.available()){}  
        c = Serial.read();
        s += c;
        while(!Serial.available()){}  
        c = Serial.read();
        s += c;
        while(!Serial.available()){}  
        c = Serial.read();
        s += c;
        while(!Serial.available()){}  
        c = Serial.read();
        s += c;
        w = s.toInt();
        if(n == 0)
        {
          analogWrite(DAC0, w);
          Serial.println("DAC0 OK");
        }
        else
        {
          analogWrite(DAC1, w);
          Serial.println("DAC1 OK");
        }
        break;
*/        
    }
  }
}
