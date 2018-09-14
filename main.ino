#include "ThingSpeak/ThingSpeak.h"

TCPClient client;

//reading AC-unit webhook channel
unsigned long ACunit_ChannelNumber = 574957;
const char * myReadAPIKey = "3ZJRY2P0QFQDGRYV";

//GPIO pins
int heater = D2;
int heaterADC = 4;

void setup()
{
      pinMode(heater, OUTPUT);               // sets pin as output
      ThingSpeak.begin(client);
}

void loop()
{
    thermister_temp(analogRead(heaterADC));
    AC_unit();
    delay(10000); 
}

//function to read temperature
void thermister_temp(int aval)
{
 String temp = String(aval);
 Spark.publish("temp", temp, PRIVATE);
}

//function to turn AC unit on/off
void AC_unit()
{
    int led1 = ThingSpeak.readIntField(ACunit_ChannelNumber, 1, myReadAPIKey);
    String led_1 = String(led1);

    //NOTICE 2 is on, 1 os off, 0 is not an option

    //turns the LED on
    if(led1 == 2)
    {
        digitalWrite(heater, HIGH);
        Spark.publish("AC-unit", led_1, PRIVATE);
    }
    
    //turns the LED off
    else if(led1 == 1)
    {
        digitalWrite(heater, LOW);
        Spark.publish("AC-unit", led_1, PRIVATE);
    }
    
}
