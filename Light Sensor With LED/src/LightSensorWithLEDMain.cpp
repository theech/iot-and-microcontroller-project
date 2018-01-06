#include <Arduino.h>

const int LED = 13;
const int sl = A0;


void setup() {
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
}

void loop() {
    
    int SS = analogRead(sl);
    Serial.println(SS);

    if ( SS <= 321)
      digitalWrite(LED, HIGH);
    else 
      digitalWrite(LED, LOW);
    
      delay(100);
}