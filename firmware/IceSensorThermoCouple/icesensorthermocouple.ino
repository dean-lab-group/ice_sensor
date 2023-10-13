#include <Adafruit_MAX31855.h>
#include "math.h"
#include <ThingSpeak.h>

// Resistors in the circuit.
const int R1 = 27380;
const int R2 = 9200000;

// Update these to talk to ThingSpeak
const unsigned long myChannelNumber = 1660146;
const char * myWriteAPIKey = "HRICAG2H4F37Z4TM";

// Pins used in the circuit
const int pinInt  = D1;
const int pinTrig = D3;
const int thermoCLK = A3;
const int thermoCS = A2;
const int thermoDO = A4;

const float CPU_PERIOD = 8.33333333;
const int R_freq_high = R1;
const int R_freq_low = R2 + R1;
const float R_RATIO = (float)(R_freq_low)/(float)(R_freq_high);

volatile float ratio;
volatile uint32_t trig;
volatile uint32_t start;
volatile uint32_t period;
volatile float period_high;
volatile float period_low;
volatile float temp = 0;
volatile bool do_publish_particle = true;
volatile bool do_publish_thingspeak = true;

TCPClient client;
Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);


void ISR()
{
  trig = System.ticks();
  period = trig - start;
  start = trig;
}


void setup() {
  pinMode(pinInt, INPUT);
  pinMode(pinTrig, OUTPUT);
  start = System.ticks();
  attachInterrupt(pinInt, ISR, RISING);
  
  Serial.begin(115200);
  //while(!Serial.available()) SPARK_WLAN_Loop();

  Particle.variable("ratio", ratio);
  Particle.variable("temp", temp);
  Particle.variable("period_high", period_high);
  Particle.variable("period_low", period_low);

  ThingSpeak.begin(client);
  Particle.publish("Setup loop completed");
  delay(1000);
}

void loop(){
  if (trig != 0){

    // Measure low frequencies
    digitalWrite(pinTrig, HIGH);
    // Delay helps oscillator stabilize on new frequency.
    delay(2000);
    period_high = period*CPU_PERIOD;
    
    Serial.print("Period Low: ");
    Serial.println(" us");
    
    Serial.print("Freq High: ");
    Serial.print(1e6/((float) period_high));
    Serial.println(" kHz");
    Serial.println("");
    delay(1000);
    
    // Measure high frequencies
    digitalWrite(pinTrig, LOW);
    // Delay helps oscillator stabilize on new frequency.
    delay(2000);

    period_low = period*CPU_PERIOD;
    Serial.print("Period Low: ");
    Serial.print(period_low);
    Serial.println(" us");
    
    Serial.print("Freq High: ");
    Serial.print(1e9/((float) period_low));
    Serial.println(" Hz");
    Serial.println("");
    
    ratio = 1/(R_RATIO * ((float)period_high / (float)period_low));
    Serial.print("Ratio: ");
    Serial.println(ratio);
    delay(1000);

    do {
        temp = thermocouple.readCelsius();
        Serial.println("Something wrong with thermocouple!");
        delay(500);
    } while(isnan(temp));
    
    Serial.printf("Temp: %0.2f", temp);

    // Allows us to run in Serial-only mode and not pollute ThingSpeak.
    if (do_publish_particle){
        Particle.publish("period_high", String(period_high), PUBLIC);
        Particle.publish("period_low", String(period_low), PUBLIC);
        Particle.publish("ratio", String(ratio), PUBLIC);
        Particle.publish("temp", String(temp), PUBLIC);
    }
    
    if (do_publish_thingspeak){
        ThingSpeak.setField(1, period_high);
        ThingSpeak.setField(2, period_low);
        ThingSpeak.setField(3, ratio);
        ThingSpeak.setField(4, temp);
        ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    }
    
    delay(120000);
  }
}