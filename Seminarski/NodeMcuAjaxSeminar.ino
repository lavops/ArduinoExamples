#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

ESP8266WebServer server;
char* ssid = "Ne Kradi WiFi";
char* password = "";

int sijalica = 0;
int temp = 0;
int humi = 0;
int udaljenostVal = 0;
int brojac = 0;

void setup() {
  WiFi.begin(ssid,password);
  Serial.begin(9600);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  //server.on("/",handleIndex);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/LED", HTTP_GET, handleLED);
  server.on("/LEDaction", handleLEDaction);
  server.on("/POT",HTTP_GET, handlePOT);
  server.on("/POTaction", handlePOTaction);
  server.on("/ULT",HTTP_GET, handleULT);
  server.on("/ULTaction", handleULTaction);
  server.on("/DHT",HTTP_GET, handleDHT);
  server.on("/DHTaction", handleDHTaction);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleIndex(){
  DynamicJsonDocument doc(1024);
  int gas = 0, distance = 0;
  doc["type"] = "request";
  serializeJson(doc,Serial);
  boolean messageReady = false;
  String message = "";
  while(messageReady == false){
    if(Serial.available()){
      message = Serial.readString();
      messageReady = true;
    }
  }
  DeserializationError error = deserializeJson(doc,message);
  if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
  }
  distance = doc["distance"];
  gas = doc["gas"];
  String output = "distance: " + String(distance) + " gas:" + String(gas);
  server.send(200,"text/plain",output);
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
  //HTML DEO
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  //pocetna += "<meta http-equiv="refresh" content="30">"
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 500px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>LED turn on/off</h2>";
  pocetna += "<img width=\"100\" src=\"https://i.ya-webdesign.com/images/light-bulb-on-off-png-4.png\" id=\"image\"/><br>";
  pocetna += "<br><button id=\"dugme\" onclick=\"myFunction()\">Toggle</button>";
  pocetna += "<br><br><form action=\"/\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"Nazad\">&nbsp</form>";
  pocetna += "<h4>Studenti:</h4><p>Djordje Milicevic 79-2016, Nikola Bojovic 46-2016,</br>Nikola Bacanin 47-2016, Igor Stevanovic 94-2016</p>";
  pocetna += "</div></body>";
  pocetna += "<script>";
  pocetna += "function myFunction(){";
  pocetna += "var xhr = new XMLHttpRequest(); var url = \"LEDaction\";";
  pocetna += "xhr.onreadystatechange = function (){";
  pocetna += "if(this.readyState == 4 && this.status == 200){";
  pocetna += "if(parseInt(this.responseText) == 1) {document.getElementById(\"image\").src=\"https://pluspng.com/img-png/light-bulb-png-light-bulb-png-file-png-image-1200.png\";";
  pocetna += "document.getElementById(\"dugme\").innerHTML=\"Turn Off\";}";
  pocetna += "else {document.getElementById(\"image\").src=\"https://i.ya-webdesign.com/images/light-bulb-on-off-png-4.png\";";
  pocetna += "document.getElementById(\"dugme\").innerHTML=\"Turn On\";}";
  pocetna += "}};xhr.open(\"GET\",url,true);xhr.send();}";
  pocetna += "document.addEventListener('DOMContentLoaded',myFunction,false);";
  pocetna += "</script></html>";
  server.send(200, "text/html", pocetna);
}

void handleLEDaction() {
  DynamicJsonDocument doc(1024);
  doc["type"] = "request";
  doc["senzor"] = "changeLED";
  serializeJson(doc,Serial);
  boolean messageReady = false;
  String message = "";
  while(messageReady == false){
    if(Serial.available()){
      message = Serial.readString();
      messageReady = true;
    }
  }
  DeserializationError error = deserializeJson(doc,message);
  if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
  }
  sijalica = doc["LED"];
  server.send(200, "text/plain",String(sijalica));
}

void handlePOT() {
  
  //HTML DEO
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  //pocetna += "<meta http-equiv=\"refresh\" content=\"1\">";
  pocetna += "<script type=\"text/javascript\" src=\"https://bernii.github.io/gauge.js/dist/gauge.min.js\"></script>";
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 500px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>Potenciometar</h2>";
  pocetna += "<h3 id=\"nesto\">Brojac = "+String(brojac)+"</h3>";
  pocetna += "<canvas id=\"foo\"></canvas></br>";
  pocetna += "<br><form action=\"/\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"Nazad\">&nbsp</form>";
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
  pocetna += "function myFunction(){";
  pocetna += "var xhr = new XMLHttpRequest();var url = \"POTaction\";";
  pocetna += "xhr.onreadystatechange = function (){";
  pocetna += "if(this.readyState == 4 && this.status == 200){";
  pocetna += "var res = this.responseText;";
  pocetna += "gauge.set(parseInt(res));";
  pocetna += "document.getElementById('nesto').innerHTML = \"Brojac = \" +res;";
  pocetna += "}}; xhr.open(\"GET\",url,true);xhr.send();";
  pocetna += "setTimeout('myFunction()', 3000);} myFunction();";
  pocetna += "</script></html>";
  server.send(200, "text/html", pocetna);
}

void handlePOTaction(){
  DynamicJsonDocument doc(1024);
  doc["type"] = "request";
  doc["senzor"] = "potenciometar";
  serializeJson(doc,Serial);
  boolean messageReady = false;
  String message = "";
  while(messageReady == false){
    if(Serial.available()){
      message = Serial.readString();
      messageReady = true;
    }
  }
  DeserializationError error = deserializeJson(doc,message);
  if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
  }
  brojac = doc["brojac"];
  server.send(200, "text/plain",String(brojac));
}

void handleDHT() {
  
  //HTML DEO
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  //pocetna += "<meta http-equiv=\"refresh\" content=\"5\">";
  pocetna += "<script type=\"text/javascript\" src=\"https://bernii.github.io/gauge.js/dist/gauge.min.js\"></script>";
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 500px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>DHT senzor Temperature i Vlaznosti vazduha</h2>";
  pocetna += "<p id=\"sth\">Temperature: " + String(temp) + " C";
  pocetna += "&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp";
  pocetna += "Humidity:" + String(humi) + " %</p>";
  pocetna += "<canvas id=\"foo1\"></canvas>";
  pocetna += "<canvas id=\"foo2\"></canvas></br>";
  pocetna += "<br><form action=\"/\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"Nazad\">&nbsp</form>";
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
  pocetna += "function myFunction(){";
  pocetna += "var xhr = new XMLHttpRequest();var url = \"DHTaction\";";
  pocetna += "xhr.onreadystatechange = function (){";
  pocetna += "if(this.readyState == 4 && this.status == 200){";
  pocetna += "var str = this.responseText;console.log(str); var res = str.split(\".\");";
  pocetna += "gauge.set(parseInt(res[0])); gauge2.set(parseInt(res[1]));";
  pocetna += "document.getElementById('sth').innerHTML = \"Temperature: \" + res[0] +\"";
  pocetna += "&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp";
  pocetna += "Humidity:\" + res[1] +\" %\";";
  pocetna += "}}; xhr.open(\"GET\",url,true);xhr.send();";
  pocetna += "setTimeout('myFunction()', 5000);} myFunction();";
  pocetna += "</script></html>";
  server.send(200, "text/html", pocetna);
}

void handleDHTaction(){
  DynamicJsonDocument doc(1024);
  doc["type"] = "request";
  doc["senzor"] = "DHT";
  serializeJson(doc,Serial);
  boolean messageReady = false;
  String message = "";
  while(messageReady == false){
    if(Serial.available()){
      message = Serial.readString();
      messageReady = true;
    }
  }
  DeserializationError error = deserializeJson(doc,message);
  if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
  }
  temp = doc["temp"];
  humi = doc["humi"];
  String temphumi = String(temp) + "." + String(humi);
  server.send(200, "text/plain",temphumi);
}

void handleULT() {
  
  //HTML DEO
  String pocetna = "<!DOCTYPE html><html><head>";
  pocetna += "<title>IoT 2020 februar</title>";
  //pocetna += "<meta http-equiv=\"refresh\" content=\"2\">";
  pocetna += "</head><body style=\"background-color: blue;font-family: arial;color: white;text-align: center;\">";
  pocetna += "<div style=\"background-color: yellow;color: black;width: 600px;height: 350px;position: relative;margin: auto;border-radius: 10px;padding: 10px;\">";
  pocetna += "<h1>IOT seminarski rad NodeMCU</h1>";
  pocetna += "<h2>Ultrasonic Distance Detector</h2>";
  pocetna += "<p id=\"nesto\">" + String(udaljenostVal) + " cm</p>";
  pocetna += "<meter style=\"width: 300px;\" id=\"metar\" min=\"0\" low=\"20\" high=\"95\" max=\"100\" value=\""+String(udaljenostVal)+"\"></meter></br>";
  pocetna += "<br><form action=\"/\" method=\"GET\" style=\"display: inline;\"><input type=\"submit\" value=\"Nazad\">&nbsp</form>";
  pocetna += "<h4>Studenti:</h4><p>Djordje Milicevic 79-2016, Nikola Bojovic 46-2016,</br>Nikola Bacanin 47-2016, Igor Stevanovic 94-2016</p>";
  pocetna += "</div></body>";
  pocetna += "<script>";
  pocetna += "function myFunction(){";
  pocetna += "var xhr = new XMLHttpRequest();var url = \"ULTaction\";";
  pocetna += "xhr.onreadystatechange = function (){";
  pocetna += "if(this.readyState == 4 && this.status == 200){";
  pocetna += "var res = this.responseText;";
  pocetna += "document.getElementById(\"metar\").value = parseInt(res);";
  pocetna += "document.getElementById(\"nesto\").innerHTML = parseInt(res) + \" cm\";";
  pocetna += "}}; xhr.open(\"GET\",url,true);xhr.send();";
  pocetna += "setTimeout('myFunction()', 3000);} myFunction();";
  pocetna += "</script></html>";
  server.send(200, "text/html", pocetna);
}

void handleULTaction(){
  DynamicJsonDocument doc(1024);
  doc["type"] = "request";
  doc["senzor"] = "ultrasonic";
  serializeJson(doc,Serial);
  boolean messageReady = false;
  String message = "";
  while(messageReady == false){
    if(Serial.available()){
      message = Serial.readString();
      messageReady = true;
    }
  }
  DeserializationError error = deserializeJson(doc,message);
  if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
  }
  udaljenostVal = doc["distance"];
  server.send(200, "text/plain",String(udaljenostVal));
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found");
}
