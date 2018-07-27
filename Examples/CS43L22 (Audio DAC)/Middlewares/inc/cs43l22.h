#include "stdint.h"

#define CS43L22_DEVICE_ADDR (uint8_t)0x4A

#define CHIP_ID_REG                 (uint8_t)0x01
#define POWER_CONTROL_1             (uint8_t)0x02
#define POWER_CONTROL_2             (uint8_t)0x04
#define CLOCKING_CONTROL            (uint8_t)0x05
#define INTERFACE_CONTROL_1         (uint8_t)0x06
#define INTERFACE_CONTROL_2         (uint8_t)0x07
#define PASS_A                      (uint8_t)0x08
#define PASS_B                      (uint8_t)0x09
#define ANALOG_ZC_SR                (uint8_t)0x0A
#define PASSTHROUGH_GANG_CONTROL    (uint8_t)0x0C
#define PLAYBACK_CONTROL_1          (uint8_t)0x0D
#define MISC_CONTROLS               (uint8_t)0x0E
#define PLAYBACK_CONTROL_2          (uint8_t)0x0F
#define PASS_A_VOLUME               (uint8_t)0x14
#define PASS_B_VOLUME               (uint8_t)0x15
#define PCMA_VOLUME                 (uint8_t)0x1A
#define PCMB_VOLUME                 (uint8_t)0x1B
#define BEEP_FREQUENCY_AND_ON_TIME  (uint8_t)0x1C
#define BEEP_VOLUME_AND_OFF_TIME    (uint8_t)0x1D
#define BEEP_AND_TONE_CONFIG        (uint8_t)0x1E
#define TONE_CONTROL                (uint8_t)0x1F
#define MASTER_VOLUME_CONTROL_A     (uint8_t)0x20
#define MASTER_VOLUME_CONTROL_B     (uint8_t)0x21
#define HEADPHONE_VOLUME_CONTROL_A  (uint8_t)0x22
#define HEADPHONE_VOLUME_CONTROL_B  (uint8_t)0x23
#define SPEAKER_VOLUME_CONTROL_A    (uint8_t)0x24
#define SPEAKER_VOLUME_CONTROL_B    (uint8_t)0x25
#define PCM_CHANNEL_SWAP            (uint8_t)0x26
#define LIMITER_CONTROL_1           (uint8_t)0x27
#define LIMITER_CONTROL_2           (uint8_t)0x28
#define LIMITER_ATTACK_RATE         (uint8_t)0x29
#define STATUS                      (uint8_t)0x2E
#define BATTERY_COMPENSATION        (uint8_t)0x2F
#define VP_BATTERY_LEVEL            (uint8_t)0x30
#define SPEAKER_STATUS              (uint8_t)0x31
#define TEMPERATURE_MONITOR_CONTROL (uint8_t)0x32
#define THERMAL_FOLDBACK            (uint8_t)0x33
#define CHARGE_PUMP_FREQUENCY       (uint8_t)0x34

void CS43L22_GPIO_Init(void);
void CS43L22_PowerUp(void);
void CS43L22_PowerDown(void);
void CS43L22_Headphone_Mute(void);
void CS43L22_Headphone_Unmute(void);
void CS43L22_Speaker_Mute(void);
void CS43L22_Speaker_Unmute(void);
void CS43L22_Set_MSTA(uint8_t);
void CS43L22_Set_MSTB(uint8_t);
void CS43L22_Config_DSPEngine(void);
void CS43L22_Config_BeepGenerator(void);
