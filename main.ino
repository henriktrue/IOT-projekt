#include "ThingSpeak/ThingSpeak.h"

TCPClient client;

//reading AC-unit webhook channel
unsigned long LEDS_ChannelNumber = 574957;
const char * myReadAPIKey = "3ZJRY2P0QFQDGRYV";

//GPIO pins
int heater = D2;
int light = D3;
int heaterADC = A3;
int lightADC = A4;

void setup()
{
      pinMode(heater, OUTPUT);               // sets pin as output
      pinMode(light, OUTPUT);               // sets pin as output
      ThingSpeak.begin(client);
}

void loop()
{
    AC_unit();
    lights();
    thermister_temp(analogRead(heaterADC));
    thermister_light(analogRead(lightADC));
    delay(10000); 
}

//function to read temperature
void thermister_temp(int val)
{
 String temp = String(val);
 Spark.publish("temp", temp, PRIVATE);
}

//function to read light
void thermister_light(int val)
{
 String light = String(val);
 Spark.publish("light", light, PRIVATE);
}

//function to turn AC unit on/off
void AC_unit()
{
    int led1 = ThingSpeak.readIntField(LEDS_ChannelNumber, 1, myReadAPIKey);
    String led_1 = String(led1);

    //NOTICE 2 is on, 1 os off, 0 is not an option

    if(led1 != 0)
    {
        //turns the LED on
        if(led1 == 2)
        {
            digitalWrite(heater, HIGH);
            Spark.publish("LED-AC-unit", led_1, PRIVATE);
        }
        
        //turns the LED off
        else if(led1 == 1)
        {
            digitalWrite(heater, LOW);
            Spark.publish("LED-AC-unit", led_1, PRIVATE);
        }
    
    }
    
}

//function to turn AC unit on/off
void lights()
{
    int led2 = ThingSpeak.readIntField(LEDS_ChannelNumber, 2, myReadAPIKey);
    String led_2 = String(led2);

    //NOTICE 2 is on, 1 os off, 0 is not an option

    if(led2 != 0)
    {
        //turns the LED on
        if(led2 == 2)
        {
            digitalWrite(light, HIGH);
            Spark.publish("LED-lights", led_2, PRIVATE);
        }
        
        //turns the LED off
        else if(led2 == 1)
        {
            digitalWrite(light, LOW);
            Spark.publish("LED-lights", led_2, PRIVATE);
        }
    
    }
    
}

