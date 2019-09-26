#include <Arduino.h>
#include <MicroGear.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>

const char *ssid = "WifiName";
const char *password = "Password";

#define APPID "ProjectName"
#define KEY "DeviceKey"
#define SECRET "DeviceSecret"

#define ALIAS "NodeMCU1"
#define TargetWeb "HTML_web"

#define FEEDID "Microproject2019"

// int timer = 0;
// char str[32];

#define D4 2                  // TXD1
#define DHTPIN D4             // what digital pin we're connected to
#define DHTTYPE DHT11         // DHT 11 if DHT 22 must be changed to DHT22
DHT dht(DHTPIN, DHTTYPE, 15); // Intialize DHT sensor

// int humid;
// int temp;

#define LIGHT A0 // Define light sensor pin

WiFiClient client;

MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t *msg, unsigned int msglen)
{
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}

void onConnected(char *attribute, uint8_t *msg, unsigned int msglen)
{
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}

void setup()
{
    /* Event listener */
    microgear.on(MESSAGE, onMsghandler);
    microgear.on(CONNECTED, onConnected);

    dht.begin();
    Serial.begin(115200);
    Serial.println("Starting...");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY, SECRET, ALIAS);
    microgear.connect(APPID);
}

void loop()
{
    if (microgear.connected())
    {
        microgear.loop();
        Serial.println("connected");

        float Humid = dht.readHumidity();
        float Temp = dht.readTemperature();       // Read temperature as Celsius (the default)
        float LightData = analogRead(LIGHT);      // Light fetch from sensor
        float Light = (LightData / 1024.0) * 100; //Light in percentage

        // Send data to show on feed
        String data = "\"Humid\":";
        data += Humid;
        data += ", \"Temp\":";
        data += Temp;
        data += ", \"Light\":";
        data += Light;
        data += "}";
        microgear.writeFeed(FEEDID, data);

        char msg[128];
        data.toCharArray(msg, data.length());
        Serial.println(msg);
        microgear.chat(TargetWeb, msg);
    }

    else
    {
        Serial.println("connection lost, reconnect...");
        microgear.connect(APPID);
    }
    delay(1000);
}
