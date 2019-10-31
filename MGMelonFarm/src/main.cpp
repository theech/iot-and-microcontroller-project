#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
// what digital pin we're connected to
#define inDHT 8 
#define outDHT 9
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define inDHTTYPE DHT22 // DHT 22  (AM2302), AM2321
#define outDHTTYPE DHT22
// photoresistor are defined
#define inLight A8
#define outLight A9
// define moisPin0 for Soil moisture sensor one
// define moisPin1 for Soil moisture sensor two
// define moisPin2 for Soil moisture sensor three
#define moisPin0 A0
#define moisPin1 A1
#define moisPin2 A2
// Define status variable to stall the realtime data from inDHT & outDHT
float inHumdStatus = .0;
float outHumdStatus = .0;
float inTempStatus = .0;
float outTempStatus = .0;
// inLightStaus and outLightStatus are Read value from sensor directly.
unsigned int inLightStatus = 0;
unsigned int outLightStatus = 0;
// Standard photoresistor value is 1024 that mean it will start from 0 to 1023
int lightMin = 0;
int lightMax = 1023;
// define status variable to stall the realtime data form moisture sensor 1, 2, and 3;]
float moisStatus0 = .0;
float moisStatus1 = .0;
float moisStatus2 = .0;
// Sending str to Nodemcu
String str;

// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht1(inDHT, inDHTTYPE);
DHT dht2(outDHT, outDHTTYPE);

//calling function
void humidTemp();
void photoresis();
void soilMoisture();
void comnuni();

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("Smart Melon Farm");
  // DHT22 begin
  dht1.begin();
  dht2.begin();
  // inform the MCU that photoresistor is an input
  pinMode(inLight, INPUT);
  pinMode(inLight, INPUT);
  // inform the MCU that Soil Moisture is an input
  pinMode(moisPin0, INPUT);
  pinMode(moisPin1, INPUT);
  pinMode(moisPin2, INPUT);
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);
  // humidity and Temperature
  humidTemp();
  // photoresistor
  photoresis();
  // soil Moisture
  soilMoisture();
  // show in Nodemcu by serial Monitor as realtime
  comnuni();
}

// humidity and Temperature function
void humidTemp() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  inHumdStatus = dht1.readHumidity();
  outHumdStatus = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  inTempStatus = dht1.readTemperature();
  outTempStatus = dht2.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(inHumdStatus) || isnan(inTempStatus))
  {
    Serial.println("Failed to read from Inside DHT22 sensor!");
    return;
  }
  if (isnan(outHumdStatus) || isnan(outTempStatus))
  {
    Serial.println("Failed to read from Outside DHT22 sensor!");
    return;
  }

  // show in MG module as realtime
  Serial.print("Inside Humidity: \t");
  Serial.print(inHumdStatus);
  Serial.print(" %\t|\t");
  Serial.print("Inside Temperature: \t");
  Serial.print(inTempStatus);
  Serial.println(" *C ");
  Serial.println("------------------------------------------------------------------------");
  Serial.print("Outside Humidity: \t");
  Serial.print(outHumdStatus);
  Serial.print(" %\t|\t");
  Serial.print("Outside Temperature: \t");
  Serial.print(outTempStatus);
  Serial.println(" *C ");
  Serial.println("------------------------------------------------------------------------");
}

// photoresistor function
void photoresis() {
   // Reading the value from sensor directly.
  inLightStatus = analogRead(inLight);
  outLightStatus = analogRead(outLight);
  // if inLightStatus is less than 0, set it equal 0, but if greater than 1023 set it equal 1023
  if (inLightStatus < lightMin)  inLightStatus = lightMin;
  else if (inLightStatus > lightMax)  inLightStatus = lightMax;
  // if outLightstatus is less than 0, set it equal 0, but if greater than 1023, set it equal 1023
  if (outLightStatus < lightMin)  outLightStatus = lightMin;
  else if (outLightStatus > lightMax)  outLightStatus = lightMax;
  // showing status in monitor
  Serial.print("Inside Light: \t\t");
  Serial.print(inLightStatus);
  Serial.print("\t|\tOutside Light: \t\t");
  Serial.println(outLightStatus);
  Serial.println("------------------------------------------------------------------------");
}

// Soil moisture function
void soilMoisture() {
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
  Serial.println("----------------------------------------------------------------------------------------------------------------- \n\n");
}

// Serial Communication function
void comnuni() {
  str = String("Inside Humidity: \t") 
        +String(inHumdStatus)
        +String("\t|\tInside Temperature: \t")
        +String(inTempStatus)
        +String("\t|\nOutside Humidity: \t")
        +String(outHumdStatus)
        +String("\t|\tOutside Temperature: \t")
        +String(outHumdStatus)
        +String("\t|\nInside Light: \t\t")
        +String(inLightStatus)
        +String("\t|\tOutside Light: \t\t")
        +String(outLightStatus)
        +String("\t|\nSoil moisture one: \t")
        +String(moisStatus0)
        +String("\t|\tSoil moisture two: \t")
        +String(moisStatus1)
        +String("\t|\tSoil moisture three: \t")
        +String(moisStatus2)
        +String("\n--------------------------------------------------------------------------------------------------------------");

  Serial1.println(str);
}