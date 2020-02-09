const float volt=5.0, t0=18,v0=2,dv=0.1;

void setup() 
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(2,INPUT);
  digitalWrite(3,HIGH);
  attachInterrupt(digitalPinToInterrupt(2), event, FALLING);
  Serial.begin(9600);
}

void event() 
{
  double t1,t2,v;
  double temp1,temp2;
  temp1 = analogRead(A1);
  temp2 = analogRead(A2);
  v = temp1 * volt / 1023.0;
  t1 = t0 + (v - v0) / dv;
  v = temp2 * volt / 1023;
  t2 = t0 + (v - v0) / dv;
  Serial.println(String(t1) + " " + String(t2));
}

void loop() 
{
  if(analogRead(A0)>512)
  {
    digitalWrite(3,LOW);
    delay(2000);
    digitalWrite(3,HIGH);
  }  
}
