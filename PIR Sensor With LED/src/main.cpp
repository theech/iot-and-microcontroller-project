
#include <Arduino.h>

int LED = 13;
int inputPin = 2;
int pirState = LOW;
int val = 0;

void setup() {
    pinMode (LED, OUTPUT);
    pinMode (inputPin, INPUT);

    Serial.begin(9600);
}

void loop() {
    val = digitalRead(inputPin);
    if(val == HIGH)
    {
        digitalWrite(LED, HIGH);
        if (pirState == LOW)
        {
            Serial.println("Motion Detected");
            pirState = HIGH;
        }
    }
    else 
    {
        digitalWrite(LED, LOW);
        if (pirState == HIGH)
        {
            Serial.println("Motion ended");
            pirState = LOW;
        }
    }
}