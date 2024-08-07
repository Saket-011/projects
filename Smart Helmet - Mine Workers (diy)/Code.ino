/* Arduino Smart Working Helmet - License: Attribution Non-commercial Share Alike (by-nc-sa)
   Smart Helmet can read temperature, dangerous gas or smoke and room/area brightness.
   In the top of this code you can adjust values of maxTemp, dGas and bValue.
   How it works:
   * if dangerous gas (or smoke) detected, make a sound and blink red led
   * if high temp detected, make a sound (different from 1st case) and blink red led
   * if room/area brightness is too low, open helmet light
   Dev: Marianna Miliori & Antonis Damigos // Date: 6/6/2015 
   More info can be found here: www.ardumotive.com                                           */                   
   
//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>

//Contants
const int pResistor = A0;   // Photoresistor pin to Arduino analog A1 pin
const int buzzer= 7;        // Buzzer pin to Arduino pin 7
const int gasSensor= A1;    // Gas sensor MQ-2 signal pin to Arduino analog A0 pin
const int hLight= 8;        // Helmet light to Arduino pin 4
const int redLed=9;         // Red led pin to Arduino pin 5

/* Temp sensor DS18B20 to Arduino pin 2 */
#define ONE_WIRE_BUS 11
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/* Change values if you want */
////////////////////
int dTemp = 35;  // Default temperature
int dGas = 400;    // Default Air value (0-1023)
int bValue= 10;   // Brightness value (0-1023)
///////////////////

//Variables
int gasValue;
int lightValue;
int tempValue;

void setup(void)
{
  //Serial monitor setup
  //Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
  pinMode(hLight,OUTPUT);
  pinMode(redLed, OUTPUT);
  sensors.begin();
  delay(10000);//mq-2 warmup delay (60sec)
}

void loop(void)
{ 
  // Read and store values to aditional variables 
  gasValue   = analogRead(gasSensor);
  lightValue = analogRead(pResistor);
  sensors.requestTemperatures();  
  tempValue  = sensors.getTempCByIndex(0); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  
  Serial.print(gasValue);  Serial.print(" ");
  Serial.print(lightValue);Serial.print(" ");
  Serial.println(tempValue);
  // Dangerous gas if
  if (gasValue >= dGas+100 && gasValue < dGas+200){
    tone(buzzer, 1000);
    digitalWrite(redLed,HIGH);
    delay(150);
    tone(buzzer, 350);
    digitalWrite(redLed,LOW);
    delay(150);
  }
    else if (gasValue >= dGas+200 && gasValue < dGas+300){
    tone(buzzer, 1000);
    digitalWrite(redLed,HIGH);
    delay(100);
    tone(buzzer, 350);
    digitalWrite(redLed,LOW);
    delay(100);
  }
    else if (gasValue >= dGas+300 && gasValue < dGas+400){
    tone(buzzer, 1000);
    digitalWrite(redLed,HIGH);
    delay(75);
    tone(buzzer, 350);
    digitalWrite(redLed,LOW);
    delay(75);
  }
    else if (gasValue >= dGas+400 && gasValue < dGas+500){
    tone(buzzer, 1000);
    digitalWrite(redLed,HIGH);
    delay(50);
    tone(buzzer, 350);
    digitalWrite(redLed,LOW);
    delay(50);
  }
    else if (gasValue >= dGas+500 && gasValue < dGas+600){
    tone(buzzer, 1000);
    digitalWrite(redLed,HIGH);
    delay(25);
    tone(buzzer, 350);
    digitalWrite(redLed,LOW);
    delay(25);
  }
    else if (gasValue >= dGas+600){
    tone(buzzer, 1000);
    digitalWrite(redLed,HIGH);
  }
    else if (tempValue < dTemp+15 ){
    noTone(buzzer);
    digitalWrite(redLed,LOW);
  }
    else{}
  // High temperature
  if (tempValue >= dTemp+15 && tempValue<16 ){
    tone(buzzer, 600);
    digitalWrite(redLed, HIGH);
    delay(150);
    tone(buzzer, 250);
    digitalWrite(redLed, LOW);
    delay(150);
  }
    else if (tempValue >= dTemp+16 && tempValue<17){
    tone(buzzer, 600);
    digitalWrite(redLed, HIGH);
    delay(125);
    tone(buzzer, 250);
    digitalWrite(redLed, LOW);
    delay(125);
  }
    else if (tempValue >= dTemp+17 && tempValue<18){
    tone(buzzer, 600);
    digitalWrite(redLed, HIGH);
    delay(100);
    tone(buzzer, 250);
    digitalWrite(redLed, LOW);
    delay(100);
  }
    else if (tempValue >= dTemp+18 && tempValue<19){
    tone(buzzer, 600);
    digitalWrite(redLed, HIGH);
    delay(75);
    tone(buzzer, 250);
    digitalWrite(redLed, LOW);
    delay(75);
  }
      else if (tempValue >= dTemp+19){
    tone(buzzer, 600);
    digitalWrite(redLed, HIGH);
  }
  else if(gasValue <= 700){
    noTone(buzzer);
    digitalWrite(redLed, LOW);
  }
  else {}
  // Room/area light - brightness
  if (lightValue > bValue){
    digitalWrite(hLight, LOW);
  }
  else{
    digitalWrite(hLight, HIGH);
  }
}
