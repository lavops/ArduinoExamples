String date;

void setup() 
{
  Serial.begin(9600); 
}

void loop() 
{
  date = __DATE__;
  Serial.println(date);
  Serial.println(__TIME__);
  delay(3000);
}
