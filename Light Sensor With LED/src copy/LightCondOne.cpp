#include <Arduino>

#define LED 11

void setup()
{
    digitialWrite(LED, OUTPUT);
}

void loop()
{
    pinMode(LED, HIGH);
}