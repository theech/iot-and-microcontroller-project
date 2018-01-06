#include <Arduino.h>

#define TRIG 2
#define ECHO 3

void setup() {
    Serial.begin(9600);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

void loop() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    long distance = pulseIn(ECHO, HIGH) / 58.2;
    tone(8, 1000, 20);
    delay(100);
    Serial.print(distance);
    Serial.println(" cm");
    delay(distance * 10);
}