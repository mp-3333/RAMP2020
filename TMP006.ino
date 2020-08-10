
/* Topic: Infrared temp sensor TMP006 example for Educational BoosterPack MK II
 *  Object: Chip's surrounding temperature. 
 *  Die: The chip's temperature itself. 
 */
 
#include <Wire.h>
#include "Adafruit_TMP006.h"
#define USE_USCI_B1 

Adafruit_TMP006 tmp006;
void printFloat(float value, int places);

int ledRed = 39;
int ledBlue = 37;
int ledGreen = 38; // LED connected to digital pin 9

void setup()
{
  Serial.begin(115200); // Initalizes the TMP006 for operation and for I2C communication
  if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
    Serial.println("No sensor found");
    while (1);
  }
  pinMode(ledRed,OUTPUT);
  pinMode(ledBlue,OUTPUT);
  pinMode(ledGreen,OUTPUT);
}

void loop()
{
  float exteriorCTemp = tmp006.readObjTempC();       
  float exteriorFTemp = exteriorCTemp*9/5+32;

  float chipCTemp = tmp006.readDieTempC(); 
  float chipFTemp = chipCTemp*9/5+32; 
  
  Serial.print("Surrounding Temperature: ");    //Print statement for surrounding temp 
  Serial.print(exteriorFTemp);                 //Fahrenheit surrounding temp
  Serial.print("*F; ");                       //Unit Fahrenheit
  Serial.print(exteriorCTemp);               //Celcius surrounding temp
  Serial.print("*C");                       //Unit celcius
  
  Serial.println(" ");                   //Space
  
  
  Serial.print("Chip Temperature: "); 
  Serial.print(chipFTemp);             //Fahrenheit chip temp
  Serial.print("*F; ");               //Unit fahrenheit 
  Serial.print(chipCTemp);           //Celcius chip temp
  Serial.println("*C");             //Unit celcius
  Serial.println(" ");             //Space 
  delay(1000);                    //4 seconds per reading for 16 samples per reading

  //if (exteriorTemp*(9/5)+32)
}
