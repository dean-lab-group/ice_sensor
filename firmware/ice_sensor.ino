// SYSTEM_MODE(SEMI_AUTOMATIC)
const float CPU_PERIOD = 8.3333;
const int R1 = 27010;
const int R2 = 9120000;
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
    delay(500);
    uint32_t period_high = period;
    Serial.println(period*CPU_PERIOD);
    delay(1000);
    digitalWrite(pinTrig, LOW);
    delay(500);
    uint32_t period_low = period;
    Serial.println(period*CPU_PERIOD);
    delay(1000);
    ratio = 1/(R_RATIO * ((float)period_high / (float)period_low));
    Particle.publish("ratio", String(ratio), PUBLIC);
    //if(ratio > 0.1){
    //    Serial.print("Air ");
    //}
    //if(ratio < 0.1){
    //    Serial.print("Water ");
    //}
    //if(ratio < 0.01){
    //   Serial.print("Ice");
    //}
    Serial.println(ratio);
    delay(1000);
  }
}