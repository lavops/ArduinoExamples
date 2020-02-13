   /**PCF8591 Module Analog to Digital test program.
    Essentially, this tests the I2C communications to the chip.
    The chip address is 0x90.
   */
   #include <Wire.h>
   #define PCF8591 (0x90 >> 1)      // Device address = 0       
   #define PCF8591_DAC_ENABLE 0x40
   #define PCF8591_ADC_CH0 0x40
   #define PCF8591_ADC_CH1 0x41
   #define PCF8591_ADC_CH2 0x42
   #define PCF8591_ADC_CH3 0x43
   byte adc_value;
   int d = 1000;
   char c;
   byte getADC(byte config)
   {
     Wire.beginTransmission(PCF8591);
     Wire.write(config);
     Wire.endTransmission();
     Wire.requestFrom((int) PCF8591,2);
     while (Wire.available()) 
     {
       adc_value = Wire.read(); //This needs two reads to get the value.
       adc_value = Wire.read();
     }
     return adc_value;
   }

  byte dac_value=0;
  void putDAC(byte dac_value)
  {
    Wire.beginTransmission(PCF8591);    //Calls the 8591 to attention.
    Wire.write(PCF8591_DAC_ENABLE);    //Send a DAC enable word.
    Wire.write(dac_value);            //Send the desired DAC value (0-255)
    Wire.endTransmission();
  }

   void setup()
   {
     Serial.begin(9600);
     Wire.begin();
     Serial.println("AD DA Test");
   }
   void loop()
   {
     if(Serial.available())
     {
       c = Serial.read();
       switch(c)
       {
         case 'd':
          d = Serial.parseInt();
          break;
         default: 
          Serial.println("Default");
          break;
       }
     }
     adc_value = getADC(PCF8591_ADC_CH0); //Channel 0 is the photo
     Serial.println("Photo: " + String(adc_value));
     adc_value = getADC(PCF8591_ADC_CH1); //Channel 1 is the termistor
     Serial.println("Termistor: " + String(adc_value));
     adc_value = getADC(PCF8591_ADC_CH2); //Channel 2 is free
     Serial.println("Free: " + String(adc_value));
     adc_value = getADC(PCF8591_ADC_CH3); //Channel 3 is the pot
     Serial.println("Potenciometer: " + String(adc_value));
     dac_value = adc_value;
     putDAC(dac_value); 
     delay(d);
   }
