// BAG SECURITY  v2.1
// SENSOR + GPS
// berhasil

#include <CapacitiveSensor.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

CapacitiveSensor cs_7_6 = CapacitiveSensor(7,6); // 1 megohm resistor between pins 7 & 6, pin 6 is sensor pin, add wire, foil

int ldrPin[6] = {A0,A1,A2,A3,A4,A5}; // select the input pin for LDR
int ldrValue[6] = {0,0,0,0,0,0}; // variable to store the value coming from the sensor
int flag = 0;
int n = 0;

SoftwareSerial GpsSs(4, 5); // The serial connection to the GPS device
TinyGPSPlus gps;  // The TinyGPS++ object
float latitude=0 , longitude=0;
String lat_str="", lng_str="";

void setup(){
  Serial.begin(115200);
  
  cs_7_6.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example

  GpsSs.begin(9600);
}

void loop(){
  long total = cs_7_6.capacitiveSensor(30);
  Serial.println(total); // print sensor output
  if(total >= 21){
    flag = flag + 3;
  }
  
  for(int a=0 ; a<=5 ; a++){
    ldrValue[a] = analogRead(ldrPin[a]); // read the value from the sensor
    Serial.print(ldrValue[a]); //prints the values coming from the sensor on the screen
    Serial.print("\t");
    if(ldrValue[a] > 25){
      flag++;
    }else if(ldrValue[a] > 45){
      flag = flag + 2;
    }
  }



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

    //perhitungan kondisi
  n++;
  if(n >= 5){
    if(flag >= 8 && latitude != 0){
      String pesan = "SMS Peringatan Bag Security. Latitude / Longitude = ";
      pesan += lat_str;
      pesan += " / ";
      pesan += lng_str;
      pesan += " . ";
      pesan += "http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
      pesan += lat_str;
      pesan += "+";
      pesan += lng_str;
      Serial.println();
      Serial.println(pesan);
      delay(1000);
    }
  flag = 0;
  n = 0;
  }
  
  Serial.println();
  Serial.println();
  delay(200);
}

// REFERENSI :
// https://www.instructables.com/id/Capacitive-Sensing-for-Dummies/
// https://circuitdigest.com/microcontroller-projects/interfacing-gps-with-nodemcu-esp12
