
#include "application.h"

class Adafruit_MAX6675 {
 public:
  Adafruit_MAX6675(int8_t sclk_pin, int8_t cs_pin, int8_t miso_pin);


  double readCelsius(void);
  double readFahrenheit(void);
  // For compatibility with older versions:
  
 private:
  int8_t sclk, miso, cs;
  uint8_t spiread(void);
};