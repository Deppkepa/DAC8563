#include <DAC8563.h>

#define SYNC_PIN PA4
#define SCLK_PIN PA5 
#define MOSI_PIN PA7 // DIN

DAC8563 dac = DAC8563(SYNC_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dac.start_init();
  
}
int count = 0;
void loop() {
  
  // put your main code here, to run repeatedly:
  uint16_t data = 49768;
  // dac.write_A();

  // dac.dac_init();
  //gain =  1
  // 43981 = 3.4 | 3.5
  // 32768 = 5.2 | 0
  // 49768 = 2.5 |5.4
  // 65536 = 0   |
  // 0 = 10.5    |

 
  // dac.transfer(CMD_WRITE_B, data);
  // dac.transfer(CMD_COMMON_POWER_UP_AND_POWER_DOWN_AB, DATA_POWER_DOWN_HI_Z_A);
  // dac.power_down('A', 1);
  //dac.write_in_I_reg('T', data);
  //dac.status_gain(1, 1); // 32768 = 2,5 В
  // dac.ldac_status(2, 2);
  dac.write_in_I_reg('T', data);
  delay(1000);
  Serial.println("Update");
  
  
  
  dac.power_down('A', 1);
  dac.power_down('B', 1000);
  dac.internal_reference('B');

  // dac.transfer(CMD_COMMON_POWER_UP_AND_POWER_DOWN_AB, DATA_POWER_UP_AB);
  delay(5000);
  // dac.transfer(CMD_COMMON_LDAC_STATUS_AB, DATA_LDAC_OFF_AB);
  
  // uint16_t mid_scale = 32768;
  // dac.transfer(CMD_WRITE_A, mid_scale);
}
