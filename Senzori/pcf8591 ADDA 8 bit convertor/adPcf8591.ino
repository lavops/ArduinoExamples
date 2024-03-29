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
   void setup()
   {
     Serial.begin(9600);
     Wire.begin();
     Serial.println("ADC Test");
   }
   void loop()
   {
     adc_value = getADC(PCF8591_ADC_CH3); //Channel 3 is the pot
     Serial.println(adc_value);
     delay(200);
   }
