//https://arduino.stackexchange.com/questions/12984/capacitive-sensor-gets-stuck
#include <CapacitiveSensor.h>

CapacitiveSensor   cs_7_6 = CapacitiveSensor(7,6);  // 1M resistor between pins 7 & 6, pin 6 is sensor pin

void setup()                    
{
   //cs_7_6.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(115200);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_7_6.capacitiveSensor(5);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.println("\t");

    delay(200);                             // arbitrary delay to limit data to serial port 
}
