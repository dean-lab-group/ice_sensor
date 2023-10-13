// SYSTEM_MODE(SEMI_AUTOMATIC)
#define CPU_PERIOD 8.3333

const int pinInt  = D1;
const int pinTrig = D0;
volatile float ratio;
volatile uint32_t trig;
volatile uint32_t start;
volatile uint32_t period;
//uint32_t correct;

//uint32_t ms;

void ISR()
{
  trig = System.ticks();
  period = trig - start;
  start = trig;
}

void setup()
{
  Particle.variable("ratio", ratio);
  Serial.begin(115200);
  pinMode(pinInt, INPUT);
  pinMode(pinTrig, OUTPUT);
  //pinMode(D7, OUTPUT);
  start = System.ticks();
  attachInterrupt(pinInt, ISR, RISING);
}

void loop()
{
  if (trig != 0)
  {
    digitalWrite(pinTrig, HIGH);
    delay(200);
    uint32_t period_high = period;
    //Serial.println(period*CPU_PERIOD);
    delay(1000);
    digitalWrite(pinTrig, LOW);
    delay(200);
    uint32_t period_low = period;
    //Serial.println(period*CPU_PERIOD);
    delay(1000);
    ratio = 15.0 * ((float)period_high / (float)period_low);
    Particle.publish("ratio", String(ratio), PUBLIC);
    Serial.println(ratio);
    delay(10000);
    
  }

}