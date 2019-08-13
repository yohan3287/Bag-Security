// BAG SECURITY  v2.0
// SENSOR ONLY
// BERHASIL

#include <CapacitiveSensor.h>

CapacitiveSensor cs_7_6 = CapacitiveSensor(7,6); // 1 megohm resistor between pins 7 & 6, pin 6 is sensor pin, add wire, foil

int ldrPin[6] = {A0,A1,A2,A3,A4,A5}; // select the input pin for LDR
int ldrValue[6] = {0,0,0,0,0,0}; // variable to store the value coming from the sensor
int flag = 0;
int n = 0;

void setup(){
  cs_7_6.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(115200);
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

  //perhitungan kondisi
  n++;
  if(n >= 5){
    if(flag >= 8){
      Serial.print("\t-- WARNING --");
    }
    flag = 0;
    n = 0;
  }
  
  Serial.println();
  delay(100);
}

// REFERENSI :
// https://www.instructables.com/id/Capacitive-Sensing-for-Dummies/
