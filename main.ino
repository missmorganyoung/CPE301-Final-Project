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
