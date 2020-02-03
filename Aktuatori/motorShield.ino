
const int aDir = 12, bDir = 13, aPwm = 3, bPwm = 11, aBrk = 9, bBrk = 8;

char c;
int numData;
String s = "";

void setup()
{
  analogWrite(aPwm, 0);
  analogWrite(bPwm, 0);
  pinMode(aDir, OUTPUT);
  pinMode(bDir, OUTPUT);
  pinMode(aBrk, OUTPUT);
  pinMode(bBrk, OUTPUT);
  digitalWrite(aDir, LOW);
  digitalWrite(bDir, LOW);
  digitalWrite(aBrk, LOW);
  digitalWrite(bBrk, LOW);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    c = Serial.read();
    s += c;
    switch(c)
    {      
      case 's':
        while(!Serial.available()){}
        c = Serial.read();
        s += c;
        if( c == 'a')
        {
          while(!Serial.available()){}
          numData = Serial.parseInt();
          s += String(numData);
          analogWrite(aPwm, numData);
        }
        if( c == 'b')
        {
          while(!Serial.available()){}
          numData = Serial.parseInt();
          s += String(numData);
          analogWrite(bPwm, numData);
        }
        Serial.println(s);
        s = "";
        break;
      case 'd':
        while(!Serial.available()){}
        c = Serial.read();
        s += c;
        if( c == 'a')
        {
          while(!Serial.available()){}
          numData = Serial.parseInt();
          s += String(numData);
          digitalWrite(aDir, numData);
        }
        if( c == 'b')
        {
          while(!Serial.available()){}
          numData = Serial.parseInt();
          s += String(numData);
          digitalWrite(bDir, numData);
        }
        Serial.println(s);
        s = "";
        break; 
    }    
  }
}