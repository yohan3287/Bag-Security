// http://www.labelektronika.com/2018/01/cara-program-gsm-module-sim800l-Kirim-SMS-Menggunakan-Arduino.html
// send SMS ---SUKSES---

#include <SoftwareSerial.h>

#define SIM800_TX_PIN 2
#define SIM800_RX_PIN 3

SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  //Memulai Komunikasi Serial Arduino  dengan SIM800
  serialSIM800.begin(9600);
  delay(1000);
  
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
  
  //No tujuan SMS (Ganti dengan Nomor Penerima SMS)
  serialSIM800.write("AT+CMGS=\"081298889184\"\r\n");
  delay(1000);
  
  //Isi SMS
  String b="b";
  String pesan = "pesan print"+b;
  serialSIM800.print(pesan);
  delay(1000);
  
  serialSIM800.write((char)26);
  delay(1000);
  
  Serial.println("SMS Terkirim !");
}

void loop() {
}
