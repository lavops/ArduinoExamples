#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(6,5,7);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () 
{
    Serial.begin(9600);    

    Rtc.Begin();

       if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }
   
}

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    delay(3000);
}

void printDateTime(RtcDateTime dt)
{
  Serial.println("Godina: " + String(dt.Year()));
  Serial.println("Mesec: " + String(dt.Month()));
  Serial.println("Dan: " + String(dt.Day()));
  Serial.println("Sat: " + String(dt.Hour()));
  Serial.println("Minut: " + String(dt.Minute()));
  Serial.println("Sekund: " + String(dt.Second()));
}
