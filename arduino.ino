

#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0; 
int sensormos = A1;  
int sensorValue = 0;    
// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 7       // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(LED,OUTPUT);  
  pinMode(sensormos, INPUT);
  Serial.begin(9600);  
  dht.begin();
  Serial.println("Soil test experiment!");    //Test the serial monitor
}

void loop() {
  // Turn off the display:
  lcd.setCursor(0, 0);
  lcd.print("pH");
  //delay(500);
  lcd.setCursor(5,0);
  lcd.print("Mos");
  //delay(500);
  lcd.setCursor(11,0);
  lcd.print("Tem(C)");
  
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
        //Serial.print("Voltage:");
        //Serial.print(voltage,2);
        //Serial.print("    pH value: ");
        Serial.print(pHValue,2);
        Serial.print("|");
        lcd.setCursor(0, 1);
        lcd.print(pHValue,1);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
  }

  sensorValue = analogRead(sensormos);
  //sensorValue = map(sensorValue,550,0,0,100);
  lcd.setCursor(5,1);
  lcd.print(sensorValue);
//  Serial.print("|");
  Serial.print(sensorValue,2);
  delay(500);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  lcd.setCursor(11,1);
  lcd.print(t);
Serial.print("|");
Serial.print(t,2);
Serial.print("|");
}


double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
//    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i]; 
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;

}

#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0; 
int sensormos = A1;  
int sensorValue = 0;    
// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 7       // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(LED,OUTPUT);  
  pinMode(sensormos, INPUT);
  Serial.begin(9600);  
  dht.begin();
  Serial.println("Soil test experiment!");    //Test the serial monitor
}

void loop() {
  // Turn off the display:
  lcd.setCursor(0, 0);
  lcd.print("pH");
  //delay(500);
  lcd.setCursor(5,0);
  lcd.print("Mos");
  //delay(500);
  lcd.setCursor(11,0);
  lcd.print("Tem(C)");
  
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
        //Serial.print("Voltage:");
        //Serial.print(voltage,2);
        //Serial.print("    pH value: ");
        Serial.print(pHValue,2);
        Serial.print("|");
        lcd.setCursor(0, 1);
        lcd.print(pHValue,1);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
  }

  sensorValue = analogRead(sensormos);
  //sensorValue = map(sensorValue,550,0,0,100);
  lcd.setCursor(5,1);
  lcd.print(sensorValue);
//  Serial.print("|");
  Serial.print(sensorValue,2);
  delay(500);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  lcd.setCursor(11,1);
  lcd.print(t);
Serial.print("|");
Serial.print(t,2);
Serial.print("|");
}


double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
//    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i]; 
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;

}

#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0; 
int sensormos = A1;  
int sensorValue = 0;    
// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 7       // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(LED,OUTPUT);  
  pinMode(sensormos, INPUT);
  Serial.begin(9600);  
  dht.begin();
  Serial.println("Soil test experiment!");    //Test the serial monitor
}

void loop() {
  // Turn off the display:
  lcd.setCursor(0, 0);
  lcd.print("pH");
  //delay(500);
  lcd.setCursor(5,0);
  lcd.print("Mos");
  //delay(500);
  lcd.setCursor(11,0);
  lcd.print("Tem(C)");
  
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
        //Serial.print("Voltage:");
        //Serial.print(voltage,2);
        //Serial.print("    pH value: ");
        Serial.print(pHValue,2);
        Serial.print("|");
        lcd.setCursor(0, 1);
        lcd.print(pHValue,1);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
  }

  sensorValue = analogRead(sensormos);
  //sensorValue = map(sensorValue,550,0,0,100);
  lcd.setCursor(5,1);
  lcd.print(sensorValue);
//  Serial.print("|");
  Serial.print(sensorValue,2);
  delay(500);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  lcd.setCursor(11,1);
  lcd.print(t);
Serial.print("|");
Serial.print(t,2);
Serial.print("|");
}


double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
//    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i]; 
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;

}

#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0; 
int sensormos = A1;  
int sensorValue = 0;    
// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 7       // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(LED,OUTPUT);  
  pinMode(sensormos, INPUT);
  Serial.begin(9600);  
  dht.begin();
  Serial.println("Soil test experiment!");    //Test the serial monitor
}

void loop() {
  // Turn off the display:
  lcd.setCursor(0, 0);
  lcd.print("pH");
  //delay(500);
  lcd.setCursor(5,0);
  lcd.print("Mos");
  //delay(500);
  lcd.setCursor(11,0);
  lcd.print("Tem(C)");
  
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
        //Serial.print("Voltage:");
        //Serial.print(voltage,2);
        //Serial.print("    pH value: ");
        Serial.print(pHValue,2);
        Serial.print("|");
        lcd.setCursor(0, 1);
        lcd.print(pHValue,1);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
  }

  sensorValue = analogRead(sensormos);
  //sensorValue = map(sensorValue,550,0,0,100);
  lcd.setCursor(5,1);
  lcd.print(sensorValue);
//  Serial.print("|");
  Serial.print(sensorValue,2);
  delay(500);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  lcd.setCursor(11,1);
  lcd.print(t);
Serial.print("|");
Serial.print(t,2);
Serial.print("|");
}


double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
//    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i]; 
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;

}
