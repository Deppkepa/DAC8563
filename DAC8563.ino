#include <DAC8563.h>

#define SYNC_PIN PA4
#define SCLK_PIN PA5 
#define MOSI_PIN PA7 // DIN

DAC8563 dac = DAC8563(SYNC_PIN);

void setup() {
  Serial.begin(9600);
  dac.start_init();
}

void loop() {
  uint16_t data1 = 49768;
  uint16_t data2 = 32768;

  dac.write_in_I_reg('A', data1);
  delay(1000);
  dac.write_in_I_reg('B', data2);
  Serial.println("Update");
  delay(5000);
}
