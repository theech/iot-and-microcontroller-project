#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#define BAUD_RATE 115200

SoftwareSerial swSer(14, 12, false, 256); // 14 = D5(RX) ; 12 = D6(TX) NodeMCU

String MyinputString = "";
char inChar;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  swSer.begin(BAUD_RATE);

  while (!swSer)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop()
{ // run over and over
  while (swSer.available())
  {
    inChar = (char)swSer.read(); // get the new byte:
    MyinputString += inChar;     // add it to the inputString:
    //Serial.println(inChar);

    if (MyinputString[0] == 'H') // check array [0] is H
    {
      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {

        int inHumd = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48); // change Char to Integer

        Serial.print("inHumd: ");
        Serial.print(inHumd);

        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'T') // check array [0] is T
    {

      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {

        int inTemp = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);

        Serial.print("\t inTemp: ");
        Serial.println(inTemp);

        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'I') // check array [0] is I
    {

      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {

        int outHumd = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);

        Serial.print("OutHumd: ");
        Serial.print(outHumd);

        MyinputString = "";
      }
    }
    else if (MyinputString[0] == 'U') // check array [0] is U
    {

      if (inChar == 0x0D) // check received 'enter' (0x0D)
      {

        int OutTemp = ((MyinputString[1] - 48) * 10) + (MyinputString[2] - 48);

        Serial.print("\t OutTemp: ");
        Serial.println(OutTemp);

        MyinputString = "";
      }
    }
    else
    {
      MyinputString = "";
    }
  }
}