#define trigPin 5
#define echoPin 6
#define led 9

void setup() 
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 4)
  {
    Serial.println("Out of range");
  }
  else 
  {
    digitalWrite(led, HIGH);
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
} 
