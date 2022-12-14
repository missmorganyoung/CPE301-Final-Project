// CPE 301 Final Project
// Fall 2022
// Morgan Young & Dylan Perkins
// Group 404

//Includes for temperature sensor, LCD and Time Sensor
#include "DHT.h"
#include "LiquidCrystal.h"
#include <Wire.h>
#include "RTClib.h"

//Time Sensor
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Temperature Sensor Pins
#define DHTPIN 3
#define SIGNAL_PIN A7
DHT dht(DHTPIN, DHTTYPE);
DHT dht(DHTPIN, DHTTYPE);

//LCD Pins
LiquidCrystal lcd(9, 8, 13, 12, 11, 10);

//LEDs, Motor and Button Pins
const int yellowLED = 26;
const int greenLED = 27;
const int blueLED = 28;
const int redLED = 29;
const int motor = 4;
const int button = 5;

//Threshold for Motor to activate
const int threshold = 100;

//State of button
int buttonState = 0;
int state = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  //Setting LEDS and motor to Outputs and the button to an Input
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(button, INPUT);

  dht.begin();

  //Turn off all LEDs when starting up
  digitalWrite(yellowLED,LOW);
  digitalWrite(greenLED,LOW);
  digitalWrite(blueLED,LOW);
  digitalWrite(redLED,LOW);
}


void loop() {
  delay(500);
  float humidity = dht.readHumidity();
  float tempF = dht.readTemperature(true);
  int value = analogRead(A5);
  buttonState = digitalRead(button);

  switch(state){
      // case 1 is the IDLE state (represented by the green LED)
      case 1:
      
          if(value < 150){
          
            state = 3;
            
          }
          
          else{
            
            if(tempF > 75){
              
              state = 2;
              
            }
            
            else{
            digitalWrite(yellowLED, LOW);     // The yellow led will turn off.
            digitalWrite(greenLED, HIGH);     // The green led will turn on.
            digitalWrite(blueLED, LOW);       // The blue led will turn off.
            digitalWrite(redLED, LOW);        // The red led will turn off.

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Temp: ");
            lcd.print(tempF);
            lcd.setCursor(0,1);
            lcd.print("Humidity: ");
            lcd.print(humidity);
            analogWrite(motor, 0);
            
            }
            
          }
          
      break;
      
      // case 2 is the RUNNING state (represented by the blue LED)
      case 2:
      
         if(tempF < 75){
           
           state = 1;
           
         }
         
         else{
           
            if(value < 150){
              
              state = 3;
            
            }
            
            else{
              
              digitalWrite(yellowLED, LOW);     // The yellow led will turn off.
              digitalWrite(greenLED, LOW);      // The green led will turn off.
              digitalWrite(blueLED, HIGH);       // The blue led will turn on.
              digitalWrite(redLED, LOW);       // The red led will turn off.
      
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Temp: ");
              lcd.print(tempF);
              lcd.setCursor(0,1);
              lcd.print("Humidity: ");
              lcd.print(humidity);
              analogWrite(motor, 200);
              
            } 
          
          }
          
      break;
      
      // case 3 is the ERROR state (represented by the Red LED)
      case 3:         
      
          if(value > 150){
            
            state = 1;
            
          }
          
          else{
            
            digitalWrite(yellowLED, LOW);     // The yellow led will turn off.
            digitalWrite(greenLED, LOW);      // The green led will turn off.
            digitalWrite(blueLED, LOW);       // The blue led will turn off.
            digitalWrite(redLED, HIGH);       // The red led will turn on.
    
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Error");
            analogWrite(motor, 0);

          }
          
      break;
      // the default case is the DISABLED state (represented by the yellow LED)
      default:
     
        if(buttonState == HIGH){
         
          state = 1;
         
        }
       
        else{
         
          digitalWrite(yellowLED, HIGH);    // The yellow led will turn on.
          digitalWrite(greenLED, LOW);      // The green led will turn off.
          digitalWrite(blueLED, LOW);       // The blue led will turn off.
          digitalWrite(redLED, LOW);        // The red led will turn off.
   
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Disabled");
          analogWrite(motor, 0);
         
        }
       
      break;
     
  }
 
}
