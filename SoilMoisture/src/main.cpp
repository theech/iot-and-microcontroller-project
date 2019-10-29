#include <Arduino.h>

// define moisPin0 for Soil moisture sensor one
// define moisPin1 for Soil moisture sensor two
// define moisPin2 for Soil moisture sensor three
#define moisPin0 A0
#define moisPin1 A1
#define moisPin2 A2

// define status variable to stall the realtime data form moisture sensor 1, 2, and 3;]
float moisStatus0 = .0;
float moisStatus1 = .0;
float moisStatus2 = .0;

void setup()
{
  Serial.begin(115200);

  pinMode(moisPin0, INPUT);
  pinMode(moisPin1, INPUT);
  pinMode(moisPin2, INPUT);
}

void loop()
{
  // reading data from each moisture sensors directly
  moisStatus0 = analogRead(moisPin0);
  moisStatus1 = analogRead(moisPin1);
  moisStatus2 = analogRead(moisPin2);

  // showing each moisture sensors to screen
  Serial.print("Soil moisture one \t");
  Serial.print(moisStatus0);
  Serial.print("\t|\t");
  Serial.print("Soil moisture two \t");
  Serial.print(moisStatus1);
  Serial.print("\t|\t");
  Serial.print("Soil moisture three \t");
  Serial.print(moisStatus2);
  Serial.println("\t|\t");

  delay(2000);
}