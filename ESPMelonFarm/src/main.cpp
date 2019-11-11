#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <MicroGear.h>

// connect to netpie
// const char *ssid = "iMac";
// const char *password = "123456789";
const char *ssid = "Guest.Conference";
const char *password = "ceitap123";

#define APPID "SMARTMELON"
#define KEY "h2qfmSSoDABtXv6"
#define SECRET "ThJoHwtrBYIgUCw5lhv62ROsM"

#define ALIAS "NodeMCU"
#define FEEDID "SMARTMELONFEED"
#define FREEBOARDID "SMARTMELONFREEBOARD"

#define INTERVAL 15000
#define T_INCREMENT 200
#define T_RECONNECT 5000
#define BAUD_RATE 115200
#define MAX_TEMP 100
#define MAX_HUMID 100

WiFiClient client;

int timer = 0;
char str[128];

MicroGear microgear(client);

#define BAUD_RATE 115200

SoftwareSerial swSer(14, 12, false, 256); // 14 = D5(RX) ; 12 = D6(TX) NodeMCU

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

String MyinputString = "";
char inChar;

// in and out humd, temp variable
int inHumd = 0;
int inTemp = 0;
int outHumd = 0;
int outTemp = 0;
int inLight = 0;
int outLight = 0;
int mois0 = 0;
int mois1 = 0;
int mois2 = 0;

// call function
void communi();
void netpieCon();
void debuging();

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("Smart Melon Farm [NODE]");
  Serial.println("Starting...");
  swSer.begin(BAUD_RATE);

  // netpie setup
  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);

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

  // serial port communications setup
  while (!swSer)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop()
{ // run over and over
  // communications with arduino MEGA
  communi();
  // connect to netpie
  netpieCon();
  // print to serial monitor
  debuging();
}

// communications function
void communi()
{
  while (swSer.available())
  {
    inChar = (char)swSer.read(); // get the new byte:
    MyinputString += inChar;     // add it to the inputString:
    //Serial.println(inChar);

    if (MyinputString[0] == 'H') // check array [0] is H
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        inHumd = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48); // change Char to Integer
        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'T') // check array [0] is T
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        inTemp = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);
        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'I') // check array [0] is I
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        outHumd = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);
        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'U') // check array [0] is U
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        outTemp = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);
        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'L') // check array [0] is L
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        inLight = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);
        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'M') // check array [0] is M
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        outLight = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);
        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'N') // check array [0] is N
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        mois0 = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);
        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'O') // check array [0] is O
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        mois1 = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);
        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'P') // check array [0] is P
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {
        mois2 = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);
        MyinputString = "";
      }
    }
    else
    {
      MyinputString = "";
    }
  }
}

// connect to netpie
void netpieCon()
{
  if (microgear.connected())
  {
    Serial.print("Connected");
    microgear.loop();
    if (timer >= INTERVAL)
    {
      // communications function
      communi();
      // Sending to the Feed
      String data = "{\"inHumd\":";
      data += inHumd;
      data += ", \"inTemp\":";
      data += inTemp;
      data += ", \"inLight\":";
      data += inLight;
      data = "{\"outHumd\":";
      data += outHumd;
      data += ", \"outTemp\":";
      data += outTemp;
      data += ", \"outLight\":";
      data += outLight;
      data = "{\"mois1\":";
      data += mois0;
      data += ", \"mois2\":";
      data += mois1;
      data += ", \"mois3\":";
      data += mois2;
      data += "}";

      //sending data to freeboard
      String str = (String)inHumd + ", " + (String)inTemp + ", " + (String)inLight + ", " + (String)outHumd + ", " + (String)outTemp + ", " + (String)outLight + ", " + (String)mois0 + ", " + (String)mois1 + ", " + (String)mois2 + ", ";
      microgear.publish("/sensors",str);
      Serial.println(str);

      if (isnan(inHumd) || isnan(inTemp) || inHumd >= MAX_HUMID || inTemp >= MAX_TEMP)
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

// debuging monitor
void debuging()
{
  Serial.println("\t\t\tSmart Melon Farm [ESP]");
  Serial.println("------------------------------------------------------------------------");
  // show in MG module as realtime
  Serial.print("Inside Humidity: \t");
  Serial.print(inHumd);
  Serial.print(" %\t|\t");
  Serial.print("Inside Temperature: \t");
  Serial.print(inTemp);
  Serial.println(" *C \t|");
  // Serial.println("------------------------------------------------------------------------");
  Serial.print("Outside Humidity: \t");
  Serial.print(outHumd);
  Serial.print(" %\t|\t");
  Serial.print("Outside Temperature: \t");
  Serial.print(outTemp);
  Serial.println(" *C \t|");
  Serial.println("------------------------------------------------------------------------");
  // showing status in monitor
  Serial.print("Inside Light: \t\t");
  Serial.print(inLight);
  Serial.print("\t|\tOutside Light: \t\t");
  Serial.print(outLight);
  Serial.println("\t|");
  Serial.println("------------------------------------------------------------------------");
  // showing each moisture sensors to screen
  Serial.print("Soil moisture one \t");
  Serial.print(mois0);
  Serial.print("\t|\t");
  Serial.print("Soil moisture two \t");
  Serial.print(mois1);
  Serial.print("\t|\t");
  Serial.print("Soil moisture three \t");
  Serial.print(mois2);
  Serial.println("\t|\t");
  Serial.println("----------------------------------------------------------------------------------------------------------------- \n\n");

  //delay(2000);
}