/*
Formati za aplikaciju: 

*** Analogni ulaz:
Ann: nn 00-05 UNO; nn 00 - 11 DUE broj analognog kanala

*** Analogna ulazna rezolucija 
RIrr: rr 00 - 12 broj bitova

*** Analogni PWM izlaz: 
Wnnwwww: nn 00 - 13 broj digitalnog kanala, wwww 0000 - 0255 UNO; 0000 - 4096 DUE izlazna analogna PWM vrednost

*** Analogni DAC izlaz
Cnwwww: n 0 - 1 broj DAC kanala, wwww 0000 - 4096 izlazna analogna jednosmerna vrednost

*** Analogna izlazna rezolucija 
RWrr: rr 00 - 12 broj bitova

*** Digitalni ulaz: 
DInn: nn 00 - 13 UNO; 00 - 53 DUE  broj digitalnog kanala

*** Digitalni izlaz: 
DOnnb: nn 00 - 13 UNO; 00 - 53 DUE broj digitalnog kanala, b 0 /1
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
        s = "";
        while(!Serial.available()){}
        c = Serial.read();        
        s += c;
        while(!Serial.available()){}
        c = Serial.read();        
        s += c;
        n = s.toInt();
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
    }
  }
}
