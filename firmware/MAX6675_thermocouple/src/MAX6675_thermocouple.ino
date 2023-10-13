// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_MAX6675.h"
#include "math.h"

int thermoCLK = A3;
int thermoCS = A2;
int thermoDO = A4;

//Adafruit_MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
Adafruit_MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  // open serial terminal and press ENTER to start
  Serial.begin(115200);
  while(!Serial.available()) SPARK_WLAN_Loop();

  Serial.println("MAX6675");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
   

   float f = thermocouple.readFahrenheit();
   if (isnan(f)) {
     //Serial.println("Something wrong with thermocouple!");
   } else {
     Serial.printf("F = %0.2f deg F\n\r", f);
   }
   
   delay(1000);
}