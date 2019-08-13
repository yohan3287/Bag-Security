//https://www.instructables.com/id/Capacitive-Sensing-for-Dummies/
#include <CapacitiveSensor.h>

CapacitiveSensor cs_7_6 = CapacitiveSensor(7,6); // 1 megohm resistor between pins 7 & 6, pin 6 is sensor pin, add wire, foil

void setup(){
  cs_7_6.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(115200);
}

void loop(){
  long total = cs_7_6.capacitiveSensor(30);
  Serial.println(total); // print sensor output
  delay(50); // arbitrary delay to limit data to serial port
}
