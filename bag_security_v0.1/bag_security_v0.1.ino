// "BAG SECURITY PROJECT"

// GENERAL LIB
#include <SoftwareSerial.h>
#include <CapacitiveSensor.h>
#include <TinyGPS++.h>

int readyFlag = 0;

// CS
CapacitiveSensor cs = CapacitiveSensor(7,6); // 1 megohm resistor between pins 7 & 6, pin 6 is sensor pin, add wire, foil
// LDR
int ldrPin[6] = {A0,A1,A2,A3,A4,A5}; // select the input pin for LDR
int ldrValue[6] = {0,0,0,0,0,0}; // variable to store the value coming from the sensor
int flag = 0;
int n = 0;
// GPS
SoftwareSerial GpsSs(4, 5); // The serial connection to the GPS device
TinyGPSPlus gps;  // The TinyGPS++ object
float latitude , longitude;
String lat_str , lng_str;
// GSM
#define SIM800_TX_PIN 3
#define SIM800_RX_PIN 2
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

void setup() {
  Serial.begin(9600);

// CS
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example
// GPS
  GpsSs.begin(9600);
// GSM
  serialSIM800.begin(9600);
  delay(250);
}

void loop() {
// CS
  long CSvalue = cs.capacitiveSensor(30);
  Serial.println(CSvalue); // print sensor output
  if(CSvalue >= 60){
    flag = flag + 2;
  }

// LDR
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

// GPS
  while (GpsSs.available() > 0){
    if (gps.encode(GpsSs.read())){
      if (gps.location.isValid()){
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
        
        Serial.print(lat_str);
        Serial.print("\t");
        Serial.println(lng_str);
        readyFlag = 1;
        break;
      }
    }
  }

  //perhitungan kondisi
  n++;
  if(n >= 5){
    if(flag >= 7){
      Serial.print("\t-- WARNING --");
      // GSM kirim SMS
      serialSIM800.write("AT+CMGF=1\r\n");
      delay(1000);
      
      //No tujuan SMS (Ganti dengan Nomor Penerima SMS)
      serialSIM800.write("AT+CMGS=\"081298889184\"\r\n");
      delay(1000);
      
      //Isi SMS
      String pesan = "SMS Peringatan Bag Security. Latitude / Longitude = ";
      pesan += lat_str;
      pesan += " / ";
      pesan += lng_str;
      pesan += " . ";
      pesan += "http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
      pesan += lat_str;
      pesan += "+";
      pesan += lng_str;
      
      serialSIM800.write(&pesan);
      delay(1000);
      
      serialSIM800.write((char)26);
      Serial.println("SMS Terkirim ! Delay 5 detik");
      Serial.println();
      Serial.println(pesan);
      delay(5000);
    }
    flag = 0;
    n = 0;
  }
  
  Serial.println();
  delay(200);
}

// REFERENCES
// https://www.instructables.com/id/Capacitive-Sensing-for-Dummies/
// https://circuitdigest.com/microcontroller-projects/interfacing-gps-with-nodemcu-esp12
// http://www.labelektronika.com/2018/01/cara-program-gsm-module-sim800l-Kirim-SMS-Menggunakan-Arduino.html
