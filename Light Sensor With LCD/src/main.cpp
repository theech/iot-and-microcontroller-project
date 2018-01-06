#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

void setup() {
    lcd.begin(16,2);
    lcd.print("Hi There!!");
}

void loop() {
    lcd.setCursor(0, 1);
    lcd.print(analogRead(A0));
    delay(200);
}