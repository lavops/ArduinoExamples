int trigPin = 5;
int echoPin = 6;
long duration, distance = 0;

unsigned long ulTimeCurrent;
unsigned long ulTimeLast = 0;

int pinLatch = 4;
int pinClock = 7;
int pinData  = 8;

unsigned char ucCharacterMap[]     = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
unsigned char ucCharacterBuffer[]  = {0xF1, 0xF2, 0xF4, 0xF8};

bool work = false, a1, a1old = true, a2, a2old = true, a3, a3old = true;
int n;
int intervals[] = {50, 100, 200, 500, 1000};
float unit;
float units[] = {2.91, 29.1};
int interval, i, j;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
  pinMode(pinData,  OUTPUT); 
  
  Serial.begin(9600);
  
  i = 0;
  j = 0;
}

void loop()
{
  unit = units[i];
  interval = intervals[j];
  
  n = analogRead(1);
  if(n > 511)
    a1 = true;
  else
    a1 = false;
  if(!a1 and a1old)
  {
    work = !work;
  }
  a1old = a1;
  
  n = analogRead(2);
  if(n > 511)
    a2 = true;
  else
    a2 = false;
  if(!a2 and a2old)
  {
    if(i == 0)
      i = 1;
    else 
      i = 0;
  }
  a2old = a2;
  
  n = analogRead(3);
  if(n > 511)
    a3 = true;
  else
    a3 = false;
  if(!a3 and a3old)
  {
    if(j < 4)
      j++; 
    else 
      j = 0;
  }
  a3old = a3;
  
  if(work)
  {
    ulTimeCurrent = millis();
    if (ulTimeCurrent - ulTimeLast > interval) 
    {    
      digitalWrite(trigPin, LOW);  
      delayMicroseconds(2); 
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); 
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/2) / unit;
      if (distance >= 4000 || distance <= 20)
        Serial.println("Out of range");
      else 
        Serial.println(distance);        
      ulTimeLast = ulTimeCurrent;
    } 
  }
  ledNumberWrite(distance);  
}

void ledNumberWrite(int dst)
{
  ledSegmentWrite(0, dst / 1000);        
  ledSegmentWrite(1, dst % 1000 / 100);
  ledSegmentWrite(2, dst % 100 / 10);
  ledSegmentWrite(3, dst % 10);          
}

void ledSegmentWrite(byte bSegmentNo, byte bDigitValue)
{
  digitalWrite(pinLatch, LOW); 
  shiftOut(pinData, pinClock, MSBFIRST, ucCharacterMap[bDigitValue]);
  shiftOut(pinData, pinClock, MSBFIRST, ucCharacterBuffer[bSegmentNo] );
  digitalWrite(pinLatch, HIGH);    
}
