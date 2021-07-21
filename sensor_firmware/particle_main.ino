// SYSTEM_MODE(SEMI_AUTOMATIC)

//
// Written by Markus Kreitzer and Emily Weaver
//

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

void ISR()
// Interrupt Service Routine
{
  trig = System.ticks();
  period = trig - start;
  start = trig;
}

void setup(){
  Particle.variable("ratio", ratio);
  //Particle.variable("detection", detect);
  Serial.begin(115200);
  pinMode(pinInt, INPUT);
  pinMode(pinTrig, OUTPUT);
  start = System.ticks();
  attachInterrupt(pinInt, ISR, RISING);
}

void loop(){
  if (trig != 0){

    digitalWrite(pinTrig, HIGH);
    delay(1000);
    uint32_t period_high = period;
    Serial.println(period*CPU_PERIOD);
    //Particle.publish("period_high", String(period_high), PUBLIC);
    delay(1000);

    digitalWrite(pinTrig, LOW);
    delay(1000);
    uint32_t period_low = period;
    Serial.println(period*CPU_PERIOD);
    //Particle.publish("period_low", String(period_low), PUBLIC);
    delay(1000);


    ratio = 1/(R_RATIO * ((float)period_high / (float)period_low));
    //Particle.publish("ratio", String(ratio), PUBLIC);
    Particle.publish("sensor_data", String(period_high) + ", " + String(period_low) + ", " + String(ratio));
    if(ratio < 1.6){
        Serial.print("Air ");
    }
    else if(ratio < 2.1){
        Serial.print("Water ");
    }
    else{
       Serial.print("Ice ");
    }
    Serial.println(ratio);
    delay(11000);
  }
}