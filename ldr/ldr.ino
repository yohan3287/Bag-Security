int ldrPin[6] = {A0,A1,A2,A3,A4,A5}; // select the input pin for LDR
int ldrValue[6] = {0,0,0,0,0,0}; // variable to store the value coming from the sensor
int flag = 0;
int n = 0;
void setup() {
  Serial.begin(115200); //sets serial port for communication
}

void loop() {
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
  delay(200);
}
