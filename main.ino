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
