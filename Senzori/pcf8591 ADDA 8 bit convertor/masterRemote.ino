#include <Wire.h>
 
// Define Slave I2C Address
#define SLAVE_ADDR 9
 
// Analog pin for potentiometer
int analogPin = 0;
// Integer to hold potentiometer value
int val = 0;
 
void setup() {
 
  // Initialize I2C communications as Master
  Wire.begin();
  
}
 
void loop() {
  delay(50);
  
  // Read pot value 
  // Map to range of 1-255 for flash rate
    val = map(analogRead(analogPin), 0, 1023, 255, 1);
    
  // Write a charatre to the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(val);
  Wire.endTransmission();
 
}