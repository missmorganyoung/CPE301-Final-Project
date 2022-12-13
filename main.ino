// CPE 301 Final Project
// Fall 2022
// Morgan Young & Dylan Perkins
// Group 404

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
