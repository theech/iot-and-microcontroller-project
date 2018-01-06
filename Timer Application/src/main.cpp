#include <Arduino.h>
#include <SimpleTimer.h>


#define BUTTON 2 
#define ALARM 8
#define LED 12

SimpleTimer timer;
int pStattte = LOW;
boolean booked = false;

void setup() {
    pinMode (BUTTON, INPUT);
    pinMode (LED, OUTPUT);
}

void loop() {
    int state = digitalRead(BUTTON);

    if(pState == LOW && state == HIGH)
    {
        if (booked == false)
        {
            booked = true;
            digitalWrite(LED, HIGH);
            timer.setTimeout(5000, beep);
        }
    }

    pState = state;
    timer.run();
}