#include "DHT.h"
#include <ArduinoJson.h>

//JSON MESSAGE KOMUNIKACIJA
String message = "";
boolean messageReady = false;

//LED
const int led = 2;
boolean sijalica = false;

//Ultrasonic
#define trigPin 5
#define echoPin 6
String udaljenostStr;
String udaljenostVal;

//Potenciometar
int levi = 3, desni = 4, stanje = 0, faza = 0, brojac = 0;
const int brojacMax = 100, brojacMin = 0;
boolean levo, desno, smer;

//DHT
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int temp, humi;

//JSON
DynamicJsonDocument doc(1024);

void setup(){
    Serial.begin(9600);
    pinMode(led, OUTPUT); //2
    pinMode(trigPin, OUTPUT); //5
    pinMode(echoPin, INPUT); //6
    pinMode(levi,INPUT); //3
    pinMode(desni, INPUT); //4
}

void loop(){
    potenciometar();
    while(Serial.available()){
        message = Serial.readString();
        messageReady = true;
    }
    
    if(messageReady){
        DeserializationError error = deserializeJson(doc,message);
        if(error){
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            messageReady = false;
            return;
        }
        if(doc["type"] == "request"){
            doc["type"] = "response";
            if(doc["senzor"] == "readLED"){
              readLED();
              serializeJson(doc,Serial);
            }
            else if(doc["senzor"] == "changeLED"){
              changeLED();
              serializeJson(doc,Serial);
            }
            else if(doc["senzor"] == "DHT"){
              readDHT();
              serializeJson(doc,Serial);
            }
            else if(doc["senzor"] == "potenciometar"){
              potenciometar();
              serializeJson(doc,Serial);
            }
            else if(doc["senzor"] == "ultrasonic"){
              ultrasonic();
              serializeJson(doc,Serial);
            }
            
        }
        messageReady = false;
    }
}

void ultrasonic(){
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
    doc["distance"] = "0";
  }
  else 
  {
    doc["distance"] = String(distance);
  }
}

void potenciometar(){
  levo = digitalRead(levi);
  desno = digitalRead(desni);

  if(levo && desno && faza != 3)
    faza = 0;
    
  if(levo && desno && faza == 3)
  {
    faza = 0;
    if(smer)
    {
      if(brojac < brojacMax)
        brojac++;      
    }
    else
      if(brojac > brojacMin)
        brojac--;      

    
  }
  
  if(faza == 0 && !levo && desno)
  {
    smer = false;
    faza = 1;
  }

  if(faza == 0 && levo && !desno)
  {
    smer = true;
    faza = 1;
  }

  if(faza == 1 && !levo && !desno)
    faza = 2;

  if(faza == 2 && !smer && levo && !desno)
    faza = 3;

  if(faza == 2 && smer && !levo && desno)
    faza = 3;
  doc["brojac"] = String(brojac);
}

void readDHT(){
  delay(2000);
  temp = (int)dht.readTemperature();
  humi = (int)dht.readHumidity();
 
  doc["temp"] = String(temp);
  doc["humi"] = String(humi);
}

void readLED() {
  if(sijalica == true)
    doc["LED"] = "1";
  else
    doc["LED"] = "0";
}

void changeLED(){
  digitalWrite(led,!digitalRead(led));
  sijalica = !sijalica;
  if(sijalica == true)
    doc["LED"] = "1";
  else
    doc["LED"] = "0";
}
