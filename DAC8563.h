#pragma once
#include <Arduino.h>

// Commands from the table

//______Запись в входной регистр DAC-n______
//______Writing to the DAC-n input register______

#define CMD_WRITE_I_REG_A 0x00
#define CMD_WRITE_I_REG_B 0x01
#define CMD_WRITE_I_REG_AB 0x07

//______Запись в входной регистр DAC-n и обновление регистров DACs______
//______Writing to the DAC-n input register and updating the DACs registers______

#define CMD_WRITE_A_AND_UPDATE_REGS 0x10
#define CMD_WRITE_B_AND_UPDATE_REGS 0x11
#define CMD_WRITE_AB_AND_UPDATE_REGS 0x17

//______Запись в входной регистр DAC-n и обновление DAC-n______
//______Writing to the DAC-n input register and updating DAC-n______

#define CMD_WRITE_UPDATE_A 0x18
#define CMD_WRITE_UPDATE_B 0x19
#define CMD_WRITE_UPDATE_AB 0x1F

//______Обновить канал DAC-n______
//______Update the DAC-n channel______

#define CMD_UPDATE_A 0x08
#define CMD_UPDATE_B 0x09
#define CMD_UPDATE_AB 0x0F

#define DATA_COMMON_UPDATE 0x0000

//______Коэффициент GAIN каждого канала DAC-n______
//______The GAIN coefficient of each DAC channel is DAC-n______

#define CMD_COMMON_GAIN 0x02

#define DATA_GAIN_B2_A2 0x0000
#define DATA_GAIN_B2_A1 0x0001
#define DATA_GAIN_B1_A2 0x0002
#define DATA_GAIN_B1_A1 0x0003

//______Включение (power up) канала DAC-n и энергорежим канала DAC-n______
//______Switching on (power up) the DAC-n channel and the power mode of the DAC-n channel______

#define CMD_COMMON_PWR_UP_AND_PWR_DOWN_AB 0x20

#define DATA_PWR_UP_A 0x0001
#define DATA_PWR_UP_B 0x0002
#define DATA_PWR_UP_AB 0x0003

#define DATA_PWR_DOWN_1KOM_A 0x0011
#define DATA_PWR_DOWN_1KOM_B 0x0012
#define DATA_PWR_DOWN_1KOM_AB 0x0013

#define DATA_PWR_DOWN_100KOM_A 0x0021
#define DATA_PWR_DOWN_100KOM_B 0x0022
#define DATA_PWR_DOWN_100KOM_AB 0x0023

#define DATA_PWR_DOWN_HI_Z_A 0x0031
#define DATA_PWR_DOWN_HI_Z_B 0x0032
#define DATA_PWR_DOWN_HI_Z_AB 0x0033

//______Сброс DAC-n входных регистров и обновление всех регистров DACs______
//______Reset DAC-n input registers and update all DACs registers______

#define CMD_COMMON_RESET_AB_AND_UPDATE 0x28

#define DATA_RESET_AB_I_REG_AND_UPDATE 0x0000
#define DATA_RESET_AB_REGS_AND_UPDATE 0x0001

//______Включить/Выключить пин LDAC для каналов DAC-n______
//______ON/OFF LDAP pin for DAC-n channels______

#define CMD_COMMON_LDAC_STATUS_AB 0x30

#define DATA_LDAC_ON_AB 0x0000
#define DATA_LDAC_ON_B_OFF_A 0x0001
#define DATA_LDAC_OFF_B_ON_A 0x0002
#define DATA_LDAC_OFF_AB 0x0003

//______Смена между внутренней и внешней опорой______
//______Switching between internal and external reference______

#define CMD_COMMON_INTERNAL_REF 0x38

#define DATA_OFF_INTERNAL_REF_AND_RESET 0x0000
#define DATA_ON_INTERNAL_REF_AND_RESET 0x0001


class DAC8563 {
  private:
    uint8_t _sync_pin;

    void dac_init();
    void transfer(uint8_t cmd, uint16_t data);
    void power_down_1kom(char channel);
    void power_down_100kom(char channel);
    void power_down_hi_z(char channel);

  public:
    DAC8563( uint8_t sync_pin );

    void start_init();
    void write_in_I_reg(char channel, uint16_t data);
    void write_I_reg_update_regs(char channel, uint16_t data);
    void write_I_reg_update_dac_n(char channel, uint16_t data);
    void update_dac_n(char channel);
    void status_gain(int A, int B);
    void power_up(char latter);
    void power_down(char channel, int mode);
    void reset_regs(char mode);
    void ldac_status(int A, int B);
    void internal_reference(char mode);
};