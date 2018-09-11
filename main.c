#include <math.h>

void setup()
{
}

void loop()
{
 thermister_temp(analogRead(4));
 delay(20000);
}

void thermister_temp(int aval)
{
 String temp = String(aval);
 
 int humidity = aval * 3;
 
 String humid = String(humidity);
 
 // return degrees C
 Spark.publish("temp", temp, PRIVATE);
 
 Spark.publish("humid", humid, PRIVATE);
}