/*
Format upita: 

Temperatura: 
T 

Svetlost (Photo)
P

Mikrofon 
M

Slider (potenciometar)
S

Buttons
B

Joystick
J

Akcelerometar
A

Led dioda
Lrrrgggbbbsssspppp
rrr, ggg, bbb 000 - 255 (boje)
ssss 0000 - 1023 (trajanje svetla u mS)
pppp 0000 - 1023 (trajanje pauze u mS)

toN
Nffffsssspppp
ffff 0000 - 9999 (frekvencija Hz)
ssss 0000 - 1023 (trajanje signala u mS)
pppp 0000 - 1023 (trajanje pauze u mS)

*/
 
#include <Esplora.h>

const int lMax = 15;
char izbor, single;
int celsius, fahrenheit, light, microphone,ax, ay, az, slider, jx, jy, l;
bool rightButton, leftButton, upButton, downButton, joystickButton;
int r, g, b, sl, pl, note, st, pt, sln = -1, pln = -1, stn, ptn;
String rs, gs, bs, sls, pls, sts, pts, output;
bool rgb, sound, rgbOn, toneOn;
void setup()  
{
  // Open serial communications and wait for port to open:
  //Serial.begin(9600);

  //while (!Serial) {
     // wait for serial port to connect. Needed for Leonardo/Esplora
  //}


  //Serial.println("Hello IDE Serial Monitor");

  // set the data rate for the SoftwareSerial port
  Serial.begin(9600);
  //Serial1.println("Hello PuTTY Terminal");
}

void loop() // run over and over
{
/*  
  if (Serial1.available())
    Serial.write(Serial1.read());

  if (Serial.available())
    Serial1.write(Serial.read());
  delay(1);
*/ 

  if (Serial.available())
  {    
    izbor = Serial.read();    
    //Serial.println(izbor);
    //Serial1.println(izbor);
    
     switch (izbor)
     {
       case 'T':            
         celsius = Esplora.readTemperature(DEGREES_C); 
         output = "T," + String(celsius) + ",";
         fahrenheit = Esplora.readTemperature(DEGREES_F);
         output = output + String(fahrenheit);
         stars();         
         break; 
       case 'P':                 
         light = Esplora.readLightSensor();
         output = "P," + String(light);
         stars();
         break;
       case 'M':
         microphone = Esplora.readMicrophone();
         output = "M," + String(microphone);
         stars();
         break;
       case 'S':         
         slider = Esplora.readSlider();
         output = "S," + String(slider);
         stars();
         break;
       case 'B':         
         rightButton = Esplora.readButton(SWITCH_RIGHT); 
         output = "B," + String(rightButton) + ",";         
         leftButton = Esplora.readButton(SWITCH_LEFT);  
         output = output + String(leftButton) + ",";         
         upButton = Esplora.readButton(SWITCH_UP);    
         output = output + String(upButton) + ",";     
         downButton = Esplora.readButton(SWITCH_DOWN);
         output = output + String(downButton);
         stars();
         break;
       case 'J':         
         jx = Esplora.readJoystickX();   
         output = "J," + String(jx) + ",";       
         jy = Esplora.readJoystickY(); 
         output = output + String(jy) + ",";
         joystickButton = Esplora.readJoystickSwitch();
         output = output + String(joystickButton);
         stars();
         break;
       case 'A':     
         ax = Esplora.readAccelerometer(X_AXIS);
         output = "A," + String(ax) + ",";                  
         ay = Esplora.readAccelerometer(Y_AXIS);
         output = output + String(ay) + ",";         
         az = Esplora.readAccelerometer(Z_AXIS); 
         output = output + String(az);         
         stars();
         break;       
       case 'L':      
         r = 0;         
         while(!Serial.available()){}
         r = r + (Serial.read() - 48)*100;
         //single = Serial1.read();
         //r = r + single * 100;
         //Serial.print(r);
         while(!Serial.available()){}
         //single = Serial1.read();
         r = r + (Serial.read() - 48)*10;
         //Serial.print(r);
         
         while(!Serial.available()){}
         r = r + (Serial.read() - 48);
         //Serial.print(r);
         
         //r = rs.toInt(); 
        
         g = 0;
         while(!Serial.available()){}
         g = g + (Serial.read() - 48)*100;
         //Serial.println(g);
         while(!Serial.available()){}
         g = g + (Serial.read() - 48)*10;
         //Serial.println(g);
         while(!Serial.available()){}
         g = g + (Serial.read() - 48);
         //Serial.println(g);
         //r = rs.toInt();          
         
         b = 0;
         while(!Serial.available()){}
         b = b + (Serial.read() - 48)*100;
         //Serial.println(b);
         while(!Serial.available()){}
         b = b + (Serial.read() - 48)*10;
         //Serial.println(r);
         while(!Serial.available()){}
         b = b + (Serial.read() - 48);
         //Serial.println(b);
         //r = rs.toInt();           
         
         sl = 0;
         while(!Serial.available()){}
         sl = sl + (Serial.read() - 48)*1000;
         //Serial.println(sl);
         while(!Serial.available()){}
         sl = sl + (Serial.read() - 48)*100;
         //Serial.println(sl);
         while(!Serial.available()){}
         sl = sl + (Serial.read() - 48)*10;
         //Serial.println(sl);
         while(!Serial.available()){}
         sl = sl + (Serial.read() - 48);
         //Serial.println(sl);
         
         pl = 0;
         while(!Serial.available()){}
         pl = pl + (Serial.read() - 48)*1000;
         //Serial.println(pl);
         while(!Serial.available()){}
         pl = pl + (Serial.read() - 48)*100;
         //Serial.println(pl);
         while(!Serial.available()){}
         pl = pl + (Serial.read() - 48)*10;
         //Serial.println(pl);
         while(!Serial.available()){}
         pl = pl + (Serial.read() - 48);
         //Serial.println(pl);
         
         sln = 0;
         pln = 0;
         rgbOn = true;
         
         //Esplora.writeRed(r);
         output = "L OK";
         stars();
         break;
        
         case 'N':
           note = 0;
           while(!Serial.available()){}
           note = note + (Serial.read() - 48)*1000;
           //Serial1.println(note);
           while(!Serial.available()){}
           note = note + (Serial.read() - 48)*100;
           //Serial1.println(note);
           while(!Serial.available()){}
           note = note + (Serial.read() - 48)*10;
           //Serial1.println(note);
           while(!Serial.available()){}
           note = note + (Serial.read() - 48);
           //Serial1.println(note);
           
           st = 0;
           while(!Serial.available()){}
           st = st + (Serial.read() - 48)*1000;
           //Serial1.println(st);
           while(!Serial.available()){}
           st = st + (Serial.read() - 48)*100;
           //Serial1.println(st);
           while(!Serial.available()){}
           st = st + (Serial.read() - 48)*10;
           //Serial1.println(st);
           while(!Serial.available()){}
           st = st + (Serial.read() - 48);
           //Serial1.println(st);
         
           pt = 0;
           while(!Serial.available()){}
           pt = pt + (Serial.read() - 48)*1000;
           //Serial1.println(pt);
           while(!Serial.available()){}
           pt = pt + (Serial.read() - 48)*100;
           //Serial1.println(pt);
           while(!Serial.available()){}
           pt = pt + (Serial.read() - 48)*10;
           //Serial1.println(pt);
           while(!Serial.available()){}
           pt = pt + (Serial.read() - 48);
           //Serial1.println(pt);
                      
           stn = 0;
           ptn = 0;
           toneOn = true;
           
           output = "N OK";
           stars();
           break;   
       
       default: 
          Serial.print(izbor);
          //Serial.print(izbor);
          break;
      }    
    
    }
    
    if(rgbOn && sln >=0)
      {
        if(sln < sl)        
         sln = sln + 1;                 
        else
        {
         sln = 0 ;
         rgbOn = false;
         Esplora.writeRGB(0, 0, 0);
         //Esplora.tone(r);
         //Serial.println("OFF");
        }
      }
      
      if(!rgbOn && pln >= 0)
      {
        if(pln < pl)
         pln = pln + 1;
        else
        {
         pln = 0 ;
         rgbOn = true;
         //Esplora.noTone();
         Esplora.writeRGB(r, g, b);
         //Esplora.noTone();
         //Esplora.tone(r);
         //Serial.println("ON");
        }
      }
      
      if(toneOn && stn >=0)
      {
        if(stn < st)
         stn = stn + 1;
        else
        {
         stn = 0 ;
         toneOn = false;
         Esplora.noTone();
         //Serial.println("OFF");
        }
      }
      
      if(!toneOn && ptn >= 0)
      {
        if(ptn < pt)
         ptn = ptn + 1;
        else
        {
         ptn = 0 ;
         toneOn = true;
         Esplora.tone(note);
         //Serial.println("ON");
        }
      }
    delay(1);
    //Serial.write(Serial1.read());
}

void stars()
{
  //Serial.print(output);
  Serial.println(output);
}
