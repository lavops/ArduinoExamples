const int pobuda = 3;
const int ref = 0;
int n, m;

void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    n = analogRead(ref);
    m = map(n, 0, 1023, 0, 255);
    analogWrite(pobuda, m);
}
