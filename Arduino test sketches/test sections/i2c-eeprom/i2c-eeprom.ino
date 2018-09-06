/*
  Write and read 10 numbers to the I2C connected EEPROM
  Example found here: http://arduinolearning.com/learning/basics/interfacing-to-a-24lc256-eeprom.php
  
*/

#include <Wire.h>     // for I2C
 
#define eeprom_address 0x50    // device address 
byte d = 0;
byte b = 0;
int  i = 0;
 
void setup()
{
  Serial.begin(19200); // Initialize the serial
  Wire.begin();
  
  //check to see if this eeprom test has been done before
  d = readData(i+1);
  if (d > 0) b = d;
 
  //write data out
  Serial.println("Writing data.");
  for ( i = 0; i < 10; i++ )
  {
    writeData(i,i+b);
  }
  Serial.println("Complete");
  //read data back
  Serial.println("Reading data.");
  for ( i = 0; i < 10; i++ )
  {
    Serial.print(i);
    Serial.print(" : ");
    d = readData(i);
    Serial.println(d, DEC);
  }
  Serial.println("Complete");
 
}
 
// writes a byte of data in memory location eaddress
void writeData(unsigned int eaddress, byte data) 
{
  Wire.beginTransmission(eeprom_address);
  // set the pointer position
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}
 
// reads a byte of data from memory location eaddress
byte readData(unsigned int eaddress) 
{
  byte result;
  Wire.beginTransmission(eeprom_address);
  // set the pointer position
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(eeprom_address,1); // get the byte of data
  result = Wire.read();
  return result;
}
 
void loop()
{
}
