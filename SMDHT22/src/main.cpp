#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(19, 18); // RX, TX Mega

#define inDHT 8 // what digital pin we're connected to
#define outDHT 9

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define inDHTTYPE DHT22 // DHT 22  (AM2302), AM2321
#define outDHTTYPE DHT22
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

String strInH;
String strInT;
String strOutH;
String strOutT;

// Define status variable to stall the realtime data from inDHT & outDHT
float inHumdStatus = .0;
float outHumdStatus = .0;
float inTempStatus = .0;
float outTempStatus = .0;

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht1(inDHT, inDHTTYPE);
DHT dht2(outDHT, outDHTTYPE);

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  Serial.println("SMART MELON FARM");
  Serial.println("DHTxx test!");
  dht1.begin();
  dht2.begin();
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  inHumdStatus = dht1.readHumidity();
  outHumdStatus = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  inTempStatus = dht1.readTemperature();
  outTempStatus = dht2.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht1.readTemperature(true);

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

  Serial.print("Inside Humidity: \t");
  Serial.print(inHumdStatus);
  Serial.print(" %\t\t");
  Serial.print("Inside Temperature: \t");
  Serial.print(inTempStatus);
  Serial.println(" *C ");
  Serial.print("Outside Humidity: \t");
  Serial.print(outHumdStatus);
  Serial.print(" %\t\t");
  Serial.print("Outside Temperature: \t");
  Serial.print(outTempStatus);
  Serial.println(" *C ");

  strInH = String('H') + String(inHumdStatus);
  strInT = String('T') + String(inTempStatus);

  strOutH = String('I') + String(outHumdStatus);
  strOutT = String('U') + String(outTempStatus);

  mySerial.println(strInH);
  mySerial.println(strInT);
  mySerial.println(strOutH);
  mySerial.println(strOutT);
}