#include "ThingSpeak/ThingSpeak.h"

TCPClient client;

//reading AC-unit webhook channel
unsigned long AC_UNIT_LEDS_ChannelNumber = 574957;
unsigned long LIGHTS_LEDS_ChannelNumber = 583357;

const char * myReadAPIKey1 = "3ZJRY2P0QFQDGRYV"; //lights
const char * myReadAPIKey2 = "K3BCBMP406BH3CBJ"; //AC unit

//GPIO pins
int heater = D2;
int light = D3;
int heaterADC = A3;
int lightADC = A4;
int counter = 0;
int avtemp = 0; 
int avlight = 0;

void setup()
{
    pinMode(heater, OUTPUT);               // sets pin as output
    pinMode(light, OUTPUT);               // sets pin as output
    ThingSpeak.begin(client);
}

void loop()
{
    counter++;
    Particle.publish("counter", String(counter), PRIVATE);
    
    AC_unit();
    lights();
    
    avtemp = analogRead(heaterADC) + avtemp;
    avlight = analogRead(lightADC) + avlight;
    
    Particle.publish("average-light", String(avlight), PRIVATE);
    Particle.publish("average-temp", String(avtemp), PRIVATE);
    
    if (counter >= 120)
    {
        avtemp = avtemp / counter;
        avlight = avlight / counter;
        
        Particle.publish("light", String(avlight), PRIVATE);
        Particle.publish("temp", String(avtemp), PRIVATE);
        
        counter = 1;
        avtemp = 0;
        avlight = 0;
    }
    
    System.sleep(D0, RISING, 8);
}

//function to turn AC unit on/off
void AC_unit()
{
    int led1 = ThingSpeak.readIntField(AC_UNIT_LEDS_ChannelNumber, 1, myReadAPIKey2);
    String led_1 = String(led1);

    //NOTICE 2 is on, 1 os off, 0 is not an option
    if(led1 != 0)
    {
        //turns the LED on
        if(led1 == 2)
        {
            digitalWrite(heater, HIGH);
            Particle.publish("LED-AC-unit", led_1, PRIVATE);
        }
        
        //turns the LED off
        else if(led1 == 1)
        {
            digitalWrite(heater, LOW);
            Particle.publish("LED-AC-unit", led_1, PRIVATE);
        }
    
    }
    
}

//function to turn lights on/off
void lights()
{
    int led2 = ThingSpeak.readIntField(LIGHTS_LEDS_ChannelNumber, 1, myReadAPIKey1);
    String led_2 = String(led2);

    //NOTICE 2 is on, 1 os off, 0 is not an option
    if(led2 != 0)
    {
        //turns the LED on
        if(led2 == 2)
        {
            digitalWrite(light, HIGH);
            Particle.publish("LED-lights", led_2, PRIVATE);
        }
        
        //turns the LED off
        else if(led2 == 1)
        {
            digitalWrite(light, LOW);
            Particle.publish("LED-lights", led_2, PRIVATE);
        }
    
    }
    
}

