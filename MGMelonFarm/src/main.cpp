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
int inHumdStatus = 0;
int outHumdStatus = 0;
int inTempStatus = 0;
int outTempStatus = 0;
// inLightStaus and outLightStatus are Read value from sensor directly.
int inLightStatus = 0;
int outLightStatus = 0;
// Standard photoresistor value is 1024 that mean it will start from 0 to 1023
int lightMin = 0;
int lightMax = 1023;
// define status variable to stall the realtime data form moisture sensor 1, 2, and 3;]
int moisStatus0 = 0;
int moisStatus1 = 0;
int moisStatus2 = 0;
// Sending str to Nodemcu
// String str;
// Communication String
String strInH;
String strInT;
String strOutH;
String strOutT;
String strInLig;
String strOutLig;
String strMois0;
String strMois1;
String strMois2;
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
  Serial.println("Smart Melon Farm [MEGE]");
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
void humidTemp()
{
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

  Serial.println("\t\t\tSmart Melon Farm [MEGE]");
  Serial.println("------------------------------------------------------------------------");

  // show in MG module as realtime
  Serial.print("Inside Humidity: \t");
  Serial.print(inHumdStatus);
  Serial.print(" %\t|\t");
  Serial.print("Inside Temperature: \t");
  Serial.print(inTempStatus);
  Serial.println(" *C\t|");
  Serial.print("Outside Humidity: \t");
  Serial.print(outHumdStatus);
  Serial.print(" %\t|\t");
  Serial.print("Outside Temperature: \t");
  Serial.print(outTempStatus);
  Serial.println(" *C\t|");
  Serial.println("------------------------------------------------------------------------");
}

// photoresistor function
void photoresis()
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
  Serial.print("Inside Light: \t\t");
  Serial.print(inLightStatus);
  Serial.print("\t|\tOutside Light: \t\t");
  Serial.print(outLightStatus);
  Serial.println("\t|");
  Serial.println("------------------------------------------------------------------------");
}

// Soil moisture function
void soilMoisture()
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
  Serial.println("----------------------------------------------------------------------------------------------------------------- \n\n");
}

// Serial Communication function
void comnuni()
{
  // in and out dht communication sending string
  strInH = String('H') + String(inHumdStatus);
  strInT = String('T') + String(inTempStatus);
  strOutH = String('I') + String(outHumdStatus);
  strOutT = String('U') + String(outTempStatus);
  Serial1.println(strInH);
  Serial1.println(strInT);
  Serial1.println(strOutH);
  Serial1.println(strOutT);
  // in and out light communication sending string
  strInLig = String('L') + String(inLightStatus);
  strOutLig = String('M') + String(outLightStatus);
  Serial1.println(strInLig);
  Serial1.println(strOutLig);
  //mois 1, 2, and 3 communication sending string
  strMois0 = String('N') + String(moisStatus0);
  strMois1 = String('O') + String(moisStatus1);
  strMois2 = String('P') + String(moisStatus2);
  Serial1.println(strMois0);
  Serial1.println(strMois1);
  Serial1.println(strMois2);
}