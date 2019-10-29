#include <Arduino.h>

// photoresistor are defined
#define inLight A8
#define outLight A9

// inLightStaus and outLightStatus are Read value from sensor directly.
unsigned int inLightStatus = 0;
unsigned int outLightStatus = 0;

// Standard photoresistor value is 1024 that mean it will start from 0 to 1023
int lightMin = 0;
int lightMax = 1023;

void setup()
{
  Serial.begin(115200);

  // inform the MCU that photoresistor is an input
  pinMode(inLight, INPUT);
  pinMode(inLight, INPUT);
}

void loop()
{
  // Reading the value from sensor directly.
  inLightStatus = analogRead(inLight);
  outLightStatus = analogRead(outLight);

  // if inLightStatus is less than 0, set it equal 0, but if greater than 1023 set it equal 1023
  if (inLightStatus < lightMin)
    inLightStatus = lightMin;
  else if (inLightStatus > lightMax)
    inLightStatus = lightMax;
  // if outLightstatus is less than 0, set it equal 0, but if greater than 1023, set it equal 1023
  if (outLightStatus < lightMin)
    outLightStatus = lightMin;
  else if (outLightStatus > lightMax)
    outLightStatus = lightMax;

  // showing status in monitor
  Serial.print("Light Inside the House: ");
  Serial.print(inLightStatus);
  Serial.print("\t Light Outside the House: ");
  Serial.println(outLightStatus);

  delay(2000);
}