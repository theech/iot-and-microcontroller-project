#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

// what digital pin we're connected to
#define inDHT 8
#define outDHT 9

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define inDHTTYPE DHT22 // DHT 22  (AM2302), AM2321
#define outDHTTYPE DHT22
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Define status variable to stall the realtime data from inDHT & outDHT
float inHumdStatus = .0;
float outHumdStatus = .0;
float inTempStatus = .0;
float outTempStatus = .0;

DHT dht1(inDHT, inDHTTYPE);
DHT dht2(outDHT, outDHTTYPE);

void setup()
{
  Serial.begin(115200);
  Serial.println("DHT22 test!");
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

  //Check if any reads failed and exit early (to try again).
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

  // Debuging the value in Serial monitor
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
}