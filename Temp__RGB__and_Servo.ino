
/* Topic: Temp, RBG, and Servo integration for Educational BoosterPack MK II
 * This is almost the final product
 */

//DEFINING VARIABLES 
#define USE_USCI_B1 
#include <Wire.h>                 //Adding more library functions 
#include "Adafruit_TMP006.h"      //Adding the temperature sensor library 
Adafruit_TMP006 tmp006;           //Declaring tmp006 sensor 

#include <Servo.h>                //Adding Servo library 
Servo myservo;  // Create servo object to control a servo 


int ledRed = 39;
int ledBlue = 37;
int ledGreen = 38; //LED connected to digital pin 9
int pos = 0;    //Variable to store the servo position 

void printFloat(float value, int places);   //Functions that are under printFloat 

void setup()
{
  Serial.begin(115200);                     //Initalizes the TMP006 for operation and for I2C communication
  myservo.attach(19);                      //Attaches the servo on pin 19 to the servo object 
  pinMode(ledBlue,OUTPUT);                //Blue LED Cool
  pinMode(ledGreen,OUTPUT);              //Green LED Warm
  pinMode(ledRed,OUTPUT);               //Red LED High
   
  if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {  //Debugging statement for temp sensor troubleshooting 
    Serial.println("No sensor found");      //Print statement for debug
    while (1);                            
  }
}

void loop()
{
  float exteriorCTemp = tmp006.readObjTempC();       
  float exteriorFTemp = exteriorCTemp*9/5+32;
  float chipCTemp = tmp006.readDieTempC(); 
  float chipFTemp = chipCTemp*9/5+32; 
  

 //CONDITION STATEMENTS 
 if (exteriorFTemp > 0 && exteriorFTemp < 80) {
  myservo.detach();
  delay(1000);
  Serial.print("Cool Temperature (BLUE): ");    //Print statement for surrounding temp
  Serial.print(exteriorFTemp);                 //Fahrenheit surrounding temp
  Serial.println("*F; ");                     //Unit Fahrenheit
  digitalWrite(ledBlue,HIGH);
  delay(2000);
  digitalWrite(ledBlue,LOW);
 }

 if (exteriorFTemp > 80 && exteriorFTemp < 100) {
  myservo.detach();
  delay (1000);
  Serial.print("Warm Temperature (GREEN): ");    //Print statement for surrounding temp
  Serial.print(exteriorFTemp);                 //Fahrenheit surrounding temp
  Serial.println("*F; ");                     //Unit Fahrenheit
  digitalWrite(ledGreen,HIGH);
  delay(2000);
  digitalWrite(ledGreen,LOW);
 }

  if (exteriorFTemp > 100) {
  myservo.attach(19);
  digitalWrite(ledRed,HIGH);
  Serial.print("Hot Temperature (RED): ");    //Print statement for surrounding temp
  Serial.print(exteriorFTemp);               //Fahrenheit surrounding temp
  Serial.println("*F; ");                   //Unit Fahrenheit
  delay(2000);
  digitalWrite(ledRed,LOW);

  for(pos = 0; pos < 180; pos += 1) {      //Goes from 0 degrees to 180 degrees, in steps of 1 degree
    myservo.write(pos);                   //Tell servo to go to position in variable 'pos' 
    delay(10);                           //Waits 10ms for the servo to reach the position 
    } 

  for(pos = 180; pos>=1; pos-=1) {       //Goes from 180 degrees to 0 degrees                                 
    myservo.write(pos);                 //Tell servo to go to position in variable 'pos' 
    delay(10);                         //Waits 10ms for the servo to reach the position  
    } 
  }
}
