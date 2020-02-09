#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <DHTesp.h>
ESP8266WiFiMulti wifiMulti;

ESP8266WebServer server(80);

//LED
const int led = 2;
boolean sijalica = false;

//Ultrasonic
#define trigPin 5
#define echoPin 16
String udaljenostStr;
String udaljenostVal;

//Potenciometar
int levi = 0, desni = 4, stanje = 0, faza = 0, brojac = 0;
const int brojacMax = 100, brojacMin = 0;
boolean levo, desno, smer;

//DHT11
DHTesp dht;
int temp, humi;

//Funkcije za stranice
void handleRoot(); 
void handleLED(); //pali gasi LED
void handleDHT(); //Ocitaj temp
void handlePOT(); //Potenciometar
void handleULT(); //Ultrasonicni senzor
void handleNotFound();

void setup(void){
  Serial.begin(9600);
  delay(10);
  Serial.println('\n');
  //otvori pinove
  pinMode(led, OUTPUT); //2
  pinMode(trigPin, OUTPUT); //5
  pinMode(echoPin, INPUT); //16
  pinMode(levi,INPUT); //4
  pinMode(desni, INPUT); //0
  dht.setup(14, DHTesp::DHT11);
  ///
  wifiMulti.addAP("Ne Kradi WiFi", "");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           

  if (MDNS.begin("esp8266")) {              
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/LED", HTTP_GET, handleLED);
  server.on("/LEDaction", HTTP_POST, handleLEDaction);
  server.on("/POT",HTTP_GET, handlePOT);
  server.on("/ULT",HTTP_GET, handleULT);
  server.on("/DHT",HTTP_GET, handleDHT);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
  //Ultrasonic distance
  //ultrasonic();
  //
  potenciometar();
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
    Serial.println("Out of range");
    udaljenostStr = "Out of range";
    udaljenostVal = "0";
  }
  else 
  {
    udaljenostStr = String(distance) + " cm";
    udaljenostVal = String(distance);
    Serial.print(distance);
    Serial.println(" cm");
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

    Serial.println(brojac);
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

  delay(1);
}

void readDHT(){
  delay(dht.getMinimumSamplingPeriod());
  temp = (int)dht.getTemperature();
  humi = (int)dht.getHumidity();
 
  Serial.println("Temp: " + String(temp) + " C");
  Serial.println("Humidity: " + String(humi) + " %");
}

void handleRoot() {
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  //pocetna += "<meta http-equiv="refresh" content="30">"
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 300px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>Izaberite senzor</h2>";
  pocetna += "<form action=\"/LED\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"LED\">&nbsp</form>";
  pocetna += "<form action=\"/POT\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"POTENCIOMETAR\">&nbsp</form>";
  pocetna += "<form action=\"/DHT\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"DHT\">&nbsp</form>";
  pocetna += "<form action=\"/ULT\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"ULTRASONIC DISTANCE\">&nbsp</form>";
  pocetna += "<h4>Studenti:</h4><p>Djordje Milicevic 79-2016, Nikola Bojovic 46-2016,</br>Nikola Bacanin 47-2016, Igor Stevanovic 94-2016</p>";
  pocetna += "</div></body></html>";
  server.send(200, "text/html", pocetna);
}

void handleLED(){
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  //pocetna += "<meta http-equiv="refresh" content="30">"
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 500px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>LED turn on/off</h2>";
  pocetna += "<img width=\"150\" src=\"https://lh3.googleusercontent.com/proxy/OhGAigSVZIiMr3JXuRydc9qT4RWEqt0dk2o8FYNVhF25WrRU5StS89Pbm2Y16NhlzJsgZpPJsEx9AqLmvmFCcIxDuim610vrWu2oua8fYa8iyPzz_Eexx2Q\" id=\"image\"/><br>";
  pocetna += "<br><form action=\"/LEDaction\" method=\"POST\"><input type=\"submit\" id=\"promena\" value=\"Turn On\">&nbsp</form>";
  pocetna += "<br><form action=\"/\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"Nazad\">&nbsp</form>";
  pocetna += "<h4>Studenti:</h4><p>Djordje Milicevic 79-2016, Nikola Bojovic 46-2016,</br>Nikola Bacanin 47-2016, Igor Stevanovic 94-2016</p>";
  pocetna += "</div></body>";
  pocetna += "<script>";
  pocetna += "if("+String(sijalica)+") {document.getElementById(\"image\").src=\"https://pluspng.com/img-png/light-bulb-png-light-bulb-png-file-png-image-1200.png\";";
  pocetna += "document.getElementById(\"promena\").value=\"Turn Off\";}";
  pocetna += "else {document.getElementById(\"image\").src=\"https://lh3.googleusercontent.com/proxy/OhGAigSVZIiMr3JXuRydc9qT4RWEqt0dk2o8FYNVhF25WrRU5StS89Pbm2Y16NhlzJsgZpPJsEx9AqLmvmFCcIxDuim610vrWu2oua8fYa8iyPzz_Eexx2Q\";";
  pocetna += "document.getElementById(\"promena\").value=\"Turn On\";}";
  pocetna += "";
  pocetna += "</script></html>";
  server.send(200, "text/html", pocetna);
}

void handleLEDaction() {
  digitalWrite(led,!digitalRead(led));
  sijalica = !sijalica;
  
  server.sendHeader("Location","/LED");
  server.send(303);
}

void handlePOT() {
  potenciometar();
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  pocetna += "<meta http-equiv=\"refresh\" content=\"1\">";
  pocetna += "<script type=\"text/javascript\" src=\"https://bernii.github.io/gauge.js/dist/gauge.min.js\"></script>";
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 500px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>Potenciometar</h2>";
  pocetna += "<h3>Brojac = "+String(brojac)+"</h3>";
  pocetna += "<canvas id=\"foo\"></canvas></br>";
  pocetna += "<form action=\"/\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"Nazad\">&nbsp</form>";
  pocetna += "<h4>Studenti:</h4><p>Djordje Milicevic 79-2016, Nikola Bojovic 46-2016,</br>Nikola Bacanin 47-2016, Igor Stevanovic 94-2016</p>";
  pocetna += "</div></body>";
  pocetna += "<script>";
  pocetna += "var opts = {angle: 0.35,lineWidth: 0.1,radiusScale: 1,pointer: {length: 0.6,strokeWidth: 0.035,color: '#000000'},limitMax: false,limitMin: false,colorStart: '#6F6EA0',colorStop: '#0902DB',strokeColor: '#EEEEEE',generateGradient: true,highDpiSupport: true,};";
  pocetna += "var target = document.getElementById('foo');";
  pocetna += "var gauge = new Donut(target).setOptions(opts);";
  pocetna += "gauge.maxValue = 100;";
  pocetna += "gauge.setMinValue(0);";
  pocetna += "gauge.animationSpeed = 1;";
  pocetna += "gauge.set("+String(brojac)+");";
  pocetna += "</script></html>";
  server.send(200, "text/html", pocetna);
}

void handleDHT() {
  readDHT();
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  pocetna += "<meta http-equiv=\"refresh\" content=\"5\">";
  pocetna += "<script type=\"text/javascript\" src=\"https://bernii.github.io/gauge.js/dist/gauge.min.js\"></script>";
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 500px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>DHT senzor Temperature i Vlaznosti vazduha</h2>";
  pocetna += "<p>Temperature: " + String(temp) + " C";
  pocetna += "&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp";
  pocetna += "Humidity:" + String(humi) + " %</p>";
  pocetna += "<canvas id=\"foo1\"></canvas>";
  pocetna += "<canvas id=\"foo2\"></canvas></br>";
  pocetna += "<form action=\"/\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"Nazad\">&nbsp</form>";
  pocetna += "<h4>Studenti:</h4><p>Djordje Milicevic 79-2016, Nikola Bojovic 46-2016,</br>Nikola Bacanin 47-2016, Igor Stevanovic 94-2016</p>";
  pocetna += "</div></body>";
  pocetna += "<script>";
  pocetna += "var opts1 = {angle: 0.15,lineWidth: 0.44,radiusScale: 1,pointer: {length: 0.6,strokeWidth: 0.035,color: '#000000'},limitMax: false,limitMin: false,colorStart: '#6F6EA0',colorStop: '#DB0202',strokeColor: '#EEEEEE',generateGradient: true,highDpiSupport: true,};";
  pocetna += "var opts2 = {angle: 0.15,lineWidth: 0.44,radiusScale: 1,pointer: {length: 0.6,strokeWidth: 0.035,color: '#000000'},limitMax: false,limitMin: false,colorStart: '#6F6EA0',colorStop: '#07DB00',strokeColor: '#EEEEEE',generateGradient: true,highDpiSupport: true,};";
  pocetna += "var target = document.getElementById('foo1');";
  pocetna += "var gauge = new Gauge(target).setOptions(opts1);";
  pocetna += "gauge.maxValue = 100;";
  pocetna += "gauge.setMinValue(0);";
  pocetna += "gauge.animationSpeed = 1;";
  pocetna += "gauge.set("+String(temp)+");";
  pocetna += "var target2 = document.getElementById('foo2');";
  pocetna += "var gauge2 = new Gauge(target2).setOptions(opts2);";
  pocetna += "gauge2.maxValue = 100;";
  pocetna += "gauge2.setMinValue(0);";
  pocetna += "gauge2.animationSpeed = 1;";
  pocetna += "gauge2.set("+String(humi)+");";
  pocetna += "</script></html>";
  server.send(200, "text/html", pocetna);
}

void handleULT() {
  ultrasonic();
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  pocetna += "<meta http-equiv=\"refresh\" content=\"2\">";
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 350px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>Ultrasonic Distance Detector</h2>";
  pocetna += "<p>" + udaljenostStr + "</p>";
  pocetna += "<input type=\"hidden\" name=\"vrednost\" id=\"vrednost\" value=\""+udaljenostVal+"\">";
  pocetna += "<p id=\"crtaj\">START||END("+udaljenostVal+")</p>";
  pocetna += "<meter style=\"width: 300px;\" id=\"metar\" min=\"0\" low=\"20\" high=\"95\" max=\"100\" value=\""+udaljenostVal+"\"></meter></br>";
  pocetna += "<form action=\"/\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"Nazad\">&nbsp</form>";
  pocetna += "<h4>Studenti:</h4><p>Djordje Milicevic 79-2016, Nikola Bojovic 46-2016,</br>Nikola Bacanin 47-2016, Igor Stevanovic 94-2016</p>";
  pocetna += "</div></body>";
  pocetna += "<script>";
  pocetna += "function crtaj(){ var vrednost = document.getElementById(\"vrednost\").value; console.log(vrednost);";
  pocetna += "var crtaj = document.getElementById(\"crtaj\").innerHTML; crtaj = \"START|\";";
  pocetna += "for(var i = 1; i<=vrednost;i++) crtaj+=\"-\";";
  pocetna += "crtaj+=\"|END("+udaljenostVal+")\"; document.getElementById(\"crtaj\").innerHTML = crtaj;} crtaj();";
  pocetna += "</script></html>";
  server.send(200, "text/html", pocetna);
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found");
}
