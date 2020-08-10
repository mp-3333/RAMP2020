
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
  

 //CONDITION STATEMENTS 
 if (exteriorFTemp > 0 && exteriorFTemp < 80) {
  Serial.print("Cool Temperature (BLUE): ");    //Print statement for surrounding temp
  Serial.print(exteriorFTemp);                 //Fahrenheit surrounding temp
  Serial.println("*F; ");                       //Unit Fahrenheit
  digitalWrite(ledBlue,HIGH);
  delay(2000);
  digitalWrite(ledBlue,LOW);
 }

 if (exteriorFTemp > 80 && exteriorFTemp < 100) {
  Serial.print("Warm Temperature (GREEN): ");    //Print statement for surrounding temp
  Serial.print(exteriorFTemp);                 //Fahrenheit surrounding temp
  Serial.println("*F; ");     
  digitalWrite(ledGreen,HIGH);
  delay(2000);
  digitalWrite(ledGreen,LOW);
 }
 
  if (exteriorFTemp > 100) {
  digitalWrite(ledRed,HIGH);
  Serial.print("Hot Temperature (RED): ");    //Print statement for surrounding temp
  Serial.print(exteriorFTemp);                 //Fahrenheit surrounding temp
  Serial.println("*F; ");     
  delay(2000);
  digitalWrite(ledRed,LOW);
 }
}
