// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_MAX31855.h>

// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>

// SYSTEM_MODE(SEMI_AUTOMATIC)
/*
This is a new ice sensor app that will talk to thingspeak.com
MK
*/

const float CPU_PERIOD = 8.3333;
const int R1 = 81982;
const int R2 = 11955055;
const int R_freq_high = R1;
const int R_freq_low = R2 + R1;
const float R_RATIO = (float)(R_freq_low)/(float)(R_freq_high);
const int pinInt  = D1;
const int pinTrig = D3;
volatile float ratio;
volatile uint32_t trig;
volatile uint32_t start;
volatile uint32_t period;
volatile long temp = 0;

TCPClient client;

unsigned long myChannelNumber = 1660146;
const char * myWriteAPIKey = "41AQ9ZTJB8SLJ6NU";


void ISR()
{
  trig = System.ticks();
  period = trig - start;
  start = trig;
}

void setup(){
  //Particle.variable("ratio", ratio);
  //Particle.variable("detection", detect);
  //ThingSpeak.begin(client);
  Serial.begin(115200);
  pinMode(pinInt, INPUT);
  pinMode(pinTrig, OUTPUT);
  start = System.ticks();
  attachInterrupt(pinInt, ISR, RISING);
}

void loop(){
  if (trig != 0){
    
    digitalWrite(pinTrig, HIGH);
    delay(2000);
    long period_high = period;
    Serial.print("Period Low: ");
    Serial.print(period*CPU_PERIOD);
    Serial.println(" us");
    
    Serial.print("Freq High: ");
    Serial.print(1e6/(period*CPU_PERIOD));
    Serial.println(" kHz");
    Serial.println("");
    // Particle.publish("period_high", String(period_high), PUBLIC);
    delay(10000);
    
    digitalWrite(pinTrig, LOW);
    delay(2000);
    long period_low = period;
    Serial.print("Period High: ");
    Serial.print(period*CPU_PERIOD);
    Serial.println(" us");
    
    Serial.print("Freq Low: ");
    Serial.print(1e9/(period*CPU_PERIOD));
    Serial.println(" Hz");
    Serial.println("");

    //Particle.publish("period_low", String(period_low), PUBLIC);
    
    ratio = 1/(R_RATIO * ((float)period_high / (float)period_low));
    Serial.print("Ratio: ");
    Serial.println(ratio);
    delay(10000);

    //ThingSpeak.setField(1, period_high);
    //ThingSpeak.setField(2, period_low);
    //ThingSpeak.setField(3, ratio);
    //ThingSpeak.setField(4, temp);
    //ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    // if(ratio < 1.6){
    //     Serial.print("Air ");
    // }
    // else if(ratio < 2.1){
    //     Serial.print("Water ");
    // }
    // else{
    //   Serial.print("Ice ");
    // }
    // Serial.println(ratio);
    delay(11000);
  }
}