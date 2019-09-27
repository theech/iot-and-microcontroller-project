#include <Arduino.h>
#include "DHT.h"
#include <MicroGear.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>

const char *ssid = "WiFiName";
const char *password = "Password";

#define APPID "ProjectName"
#define KEY "DeviceKey"
#define SECRET "DeviceSecret"

#define ALIAS "NodeMCU1"
#define FEEDID "Melon"

#define INTERVAL 15000
#define T_INCREMENT 200
#define T_RECONNECT 5000
#define BAUD_RATE 115200
#define MAX_TEMP 100
#define MAX_HUMID 100

WiFiClient client;

int timer = 0;
char str[32];

#define DHTTYPE DHT11     //Define sensor type
#define DHTPIN D4         // Define sensor pin
DHT dht(DHTPIN, DHTTYPE); //Initialize DHT sensor

#define LIGHT A0

float humid;
float temp;
float light;

MicroGear microgear(client);

// when the other thing send a msg to this board
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
    dht.begin();

    microgear.on(MESSAGE, onMsghandler);
    microgear.on(CONNECTED, onConnected);

    Serial.begin(BAUD_RATE);
    Serial.println("Starting...");

    if (WiFi.begin(ssid, password))
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
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
        Serial.print("*");
        microgear.loop();
        if (timer >= INTERVAL)
        {
            humid = dht.readHumidity();
            temp = dht.readTemperature();
            light = (analogRead(LIGHT) / 1024.0) * 100;

            Serial.print("\nHumidity: ");
            Serial.print(humid);
            Serial.print(" %\t");
            Serial.print("Temperature: ");
            Serial.print(temp);
            Serial.print(" C\n");
            Serial.print("Light: ");
            Serial.print(light);
            Serial.print(" %\n");

            // Sending to the Feed
            String data = "{\"humid\":";
            data += humid;
            data += ", \"temp\":";
            data += temp;
            data += ", \"light\":";
            data += light;
            data += "}";

            // Showing Gauage on Freeboard
            String str = (String)humid + ", " + (String)temp + ", " + (String)light + ", ";
            microgear.publish("/dht", str);
            Serial.println(str);

            if (isnan(humid) || isnan(temp) || humid >= MAX_HUMID || temp >= MAX_TEMP)
            {
                Serial.println("Failed to read from DHT sensor!");
            }
            else
            {
                Serial.print("Sending -->");
                Serial.println((char *)data.c_str());
                microgear.writeFeed(FEEDID, data); //YOUR  FEED ID, API KEY
            }
            timer = 0;
        }
        else
            timer += T_INCREMENT;
    }
    else
    {
        Serial.println("connection lost, reconnect...");
        if (timer >= T_RECONNECT)
        {
            microgear.connect(APPID);
            timer = 0;
        }
        else
            timer += T_INCREMENT;
    }
    delay(200);
}