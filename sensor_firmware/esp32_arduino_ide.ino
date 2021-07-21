/*
  Modified by Markus Kreitzer
  From: https://www.esp32.com/viewtopic.php?f=19&t=6533
*/

const byte        interruptPin = 12;              // Assign the interrupt pin
const byte        outPin = 22;                    // Pin used to trigger relay
volatile uint64_t StartValue = 0;                 // First interrupt value
volatile uint64_t PeriodCount;                    // period in counts 
volatile uint64_t prev_period = 60;               // Not used, but if used (for filtering...)
//float             Freq;                           // frequency
hw_timer_t * timer = NULL;                        // pointer to a variable of type hw_timer_t


void IRAM_ATTR handleInterrupt()
{
  uint64_t TempVal = timerRead(timer);            // value of timer at interrupt
  PeriodCount = TempVal - StartValue;             // period count between rising edges
  StartValue = TempVal;                           // puts latest reading as start for next calculation
}


void setup()
{
  pinMode(interruptPin, INPUT);                                       // sets pin as input
  pinMode(outPin,OUTPUT);
  Serial.begin(115200);
  
  attachInterrupt(interruptPin, handleInterrupt, FALLING);            // attaches pin to interrupt on Falling Edge
  timer = timerBegin(0, 1, true);                                     // configure timer 
  // 0 = first timer
  // 2 is prescaler so 80 MHZ divided by 2 = 40 MHZ signal
  // true - counts up
  timerStart(timer);                                                  // starts the timer
}

float filtered(float period_val, float previous_period){
  float alpha = 0.7;
  return alpha * period_val + (1.0 - alpha) * previous_period;
}

float get_period(){
  for(int cnt = 0; cnt < 10; cnt--){
    float period = filtered(PeriodCount, prev_period);
    prev_period = PeriodCount;
    return period;
  }
}


void loop()
{
  float period = PeriodCount/40.0; // Divide by 40 to get accurate count.
  delay(100); // 100 ms
}
