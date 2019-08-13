//https://circuitdigest.com/microcontroller-projects/interfacing-gps-with-nodemcu-esp12

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial GpsSs(4, 5); // The serial connection to the GPS device
TinyGPSPlus gps;  // The TinyGPS++ object

float latitude , longitude;
String lat_str , lng_str;

void setup()
{
  Serial.begin(9600);
  GpsSs.begin(9600);
}

void loop(){
  while (GpsSs.available() > 0){
    if (gps.encode(GpsSs.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);

        Serial.print(lat_str);
        Serial.print("\t");
        Serial.println(lng_str);
        break;
      }
    }
  }
  delay(100);
  Serial.println("done");
}
