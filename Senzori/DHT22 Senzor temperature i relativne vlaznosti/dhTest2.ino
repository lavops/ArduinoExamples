#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
 
void setup()
{
  Serial.begin(9600);
}

void loop()
{
 float temp = dht.readTemperature();
 float humidity = dht.readHumidity();
 
 Serial.println("Temp: " + String(temp) + " C");
 Serial.println("Humidity: " + String(humidity) + " %");
 Serial.println(); 
 delay(3000);
}
