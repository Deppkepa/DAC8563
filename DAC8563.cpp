#include <SPI.h>
#include "DAC8563.h"
#include <Arduino.h>


DAC8563::DAC8563( uint8_t sync_pin) {
  _sync_pin = sync_pin;
};

void DAC8563::start_init(){
  pinMode(_sync_pin, OUTPUT);
  digitalWrite(_sync_pin, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV64);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE2);
  dac_init();
};

void DAC8563::dac_init(){
  reset_regs('S'); // Resetting all registers
  power_up('T'); // Enable channels A, B
  internal_reference('N'); // Enable internal reference
  status_gain(2, 2); // gain coefficient
  ldac_status(2, 2); // refresh the cache
};

void DAC8563::transfer(uint8_t cmd, uint16_t data){
  digitalWrite(_sync_pin, LOW);
  SPI.transfer(cmd);
  SPI.transfer16(data); 
  digitalWrite(_sync_pin, HIGH);
};

void DAC8563::write_in_I_reg(char channel, uint16_t data){
  if (channel != 'A' or channel != 'B' or channel != 'T') {
    Serial.println("Incorrect channel selection. Use 'A', 'B', or 'T'.");
    return;
  }
  if (channel == 'A') {
    transfer(CMD_WRITE_I_REG_A, data);
  } else if (channel == 'B') {
    transfer(CMD_WRITE_I_REG_B, data);
  } else if (channel == 'T') {
    transfer(CMD_WRITE_I_REG_AB, data);
  }
};

void DAC8563::write_I_reg_update_regs(char channel, uint16_t data){
  if (channel != 'A' or channel != 'B' or channel != 'T') {
    Serial.println("Incorrect channel selection. Use 'A', 'B', or 'T'.");
    return;
  }
  if (channel == 'A') {
    transfer(CMD_WRITE_A_AND_UPDATE_REGS, data);
  } else if (channel == 'B') {
    transfer(CMD_WRITE_B_AND_UPDATE_REGS, data);
  } else if (channel == 'T') {
    transfer(CMD_WRITE_AB_AND_UPDATE_REGS, data);
  }
};

void DAC8563::write_I_reg_update_dac_n(char channel, uint16_t data){
  if (channel != 'A' or channel != 'B' or channel != 'T') {
    Serial.println("Incorrect channel selection. Use 'A', 'B', or 'T'.");
    return;
  }
  if (channel == 'A') {
    transfer(CMD_WRITE_UPDATE_A, data);
  } else if (channel == 'B') {
    transfer(CMD_WRITE_UPDATE_B, data);
  } else if (channel == 'T') {
    transfer(CMD_WRITE_UPDATE_AB, data);
  }
};

void DAC8563::update_dac_n(char channel) {
  if (channel != 'A' or channel != 'B' or channel != 'T') {
    Serial.println("Incorrect channel selection. Use 'A', 'B', or 'T'.");
    return;
  }

  if (channel == 'A') {
    transfer(CMD_UPDATE_A, DATA_COMMON_UPDATE);
  } else if (channel == 'B') {
    transfer(CMD_UPDATE_B, DATA_COMMON_UPDATE);
  } else if (channel == 'T') {
    transfer(CMD_UPDATE_AB, DATA_COMMON_UPDATE);
  }
};

void DAC8563::status_gain(int A, int B) {
  if (A != 1 or A != 2 or B != 1 or B != 2) {
    Serial.println("Incorrect A or B selection. Use '1' or '2'.");
    return;
  }

  if (A == 2 and B == 2) {
    transfer(CMD_COMMON_GAIN, DATA_GAIN_B2_A2);
  } else if (A == 2 and B == 1) {
    transfer(CMD_COMMON_GAIN, DATA_GAIN_B2_A1);
  } else if (A == 1 and B == 2) {
    transfer(CMD_COMMON_GAIN, DATA_GAIN_B1_A2);
  } else if (A == 1 and B == 1) {
    transfer(CMD_COMMON_GAIN, DATA_GAIN_B1_A1);
  }
};

void DAC8563::power_up(char channel) {
  if (channel != 'A' or channel != 'B' or channel != 'T') {
    Serial.println("Incorrect channel selection. Use 'A', 'B', or 'T'.");
    return; 
  }

  if (channel == 'A') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_UP_A);
  } else if (channel == 'B') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_UP_B);
  } else if (channel == 'T') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_UP_AB);
  }
};

void DAC8563::power_down(char channel, int mode) { // 1000 - Hi-z, 1 - 1kom, 100 - 100kom
  if (channel != 'A' or channel != 'B' or channel != 'T') {
    Serial.println("Incorrect channel selection. Use 'A', 'B', or 'T'.");
    return;
  }
  if (mode != 1 or mode != 100 or mode != 1000) {
    Serial.println("Incorrect mode selection. Use '1', '100', or '1000'.");
    return;
  }
  if (mode == 1000) {
    power_down_hi_z(channel);
  } else if (mode == 1) {
    power_down_1kom(channel);
  } else if (mode == 100) {
    power_down_100kom(channel);
  }
};

void DAC8563::power_down_hi_z(char channel) {
  if (channel == 'A') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_HI_Z_A);
  } else if (channel == 'B') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_HI_Z_B);
  } else if (channel == 'T') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_HI_Z_AB);
  }
};

void DAC8563::power_down_1kom(char channel) {
  if (channel == 'A') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_1KOM_A);
  } else if (channel == 'B') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_1KOM_B);
  } else if (channel == 'T') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_1KOM_AB);
  }
};

void DAC8563::power_down_100kom(char channel) { // T - AB
  if (channel == 'A') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_100KOM_A);
  } else if (channel == 'B') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_100KOM_B);
  } else if (channel == 'T') {
    transfer(CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB, DATA_PWR_DOWN_100KOM_AB);
  }
};

void DAC8563::reset_regs(char mode){  // S - all registers, I - input regiters
  if (mode != 'I' or mode != 'S') {
    Serial.println("Incorrect mode selection. Use 'I' or 'S'.");
    return;
  }

  if (mode == 'I') {
    transfer(CMD_COMMON_RESET_AB_AND_UPDATE, DATA_RESET_AB_I_REG_AND_UPDATE); 
  } else if (mode == 'S') {
    transfer(CMD_COMMON_RESET_AB_AND_UPDATE, DATA_RESET_AB_REGS_AND_UPDATE);
  }
};

void DAC8563::ldac_status(int A, int B) { // 1 - on, 2 - off
  if (A != 1 or A != 2 or B != 1 or B != 2) {
    Serial.println("Incorrect A or B selection. Use '1' or '2'.");
    return;
  }

  if (A == 1 and B == 1) { 
    transfer(CMD_COMMON_LDAC_STATUS_AB, DATA_LDAC_ON_AB);
  } else if (A == 2 and B == 1) {
    transfer(CMD_COMMON_LDAC_STATUS_AB, DATA_LDAC_ON_B_OFF_A);
  } else if (A == 1 and B == 2) {
    transfer(CMD_COMMON_LDAC_STATUS_AB, DATA_LDAC_OFF_B_ON_A);
  } else if (A == 2 and B == 2) {
    transfer(CMD_COMMON_LDAC_STATUS_AB, DATA_LDAC_OFF_AB);
  }
};


void DAC8563::internal_reference(char mode) { // N - on, F - off
  if (mode != 'N' or mode != 'F') {
    Serial.println("Incorrect mode selection. Use 'N' or 'F'.");
    return;
  }

  if (mode == 'N') { 
    transfer(CMD_COMMON_INTERNAL_REF, DATA_ON_INTERNAL_REF_AND_RESET); 
  } else if (mode == 'F') { 
    transfer(CMD_COMMON_INTERNAL_REF, DATA_OFF_INTERNAL_REF_AND_RESET);
  }
};