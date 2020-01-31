#include <Ethernet.h>
#include <DHT.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,2,177);

EthernetServer server(80);

#define DHTPIN 2     
#define DHTTYPE DHT11   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600); 
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println("DHT11 measurement");
   
  dht.begin();
}

void loop() 
{
  EthernetClient client = server.available();
  if (client) 
  {   
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        Serial.write(c);        
        if (c == '\n' && currentLineIsBlank) 
        {         
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 1");
          client.println();                                                                              
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");                                     
          client.println("<h1>");
          client.print("{");  
          float h = dht.readHumidity();
          float t = dht.readTemperature();                              
          client.print("LabTemp:"); 
          //client.print("\"");
          client.print(t);
          //client.print("\"");       
          client.print(",");
          client.print("LabHum:");  
          //client.print("\"");
          client.print(h);
          //client.print("\""); 
          //client.println();
          client.println("}");
          client.println("</h1>");
          client.println("</html>");
          break;
        }
        if (c == '\n')  
          currentLineIsBlank = true;         
        else if (c != '\r')         
          currentLineIsBlank = false;       
      }
    }
    delay(1);
    client.stop();    
  }   
}
