#ifndef PIN_MAP_H
#define PIN_MAP_H

enum GpioPin {
    KILLSWITCH_PIN = 50,
    LED_STAT_PIN   = 22,
    LED_CTRL_PIN   = 52,
    LIGHTS_PIN     = 45,
    ESC_S1_PIN     = 36,
    ESC_S2_PIN     = 39,
    ESC_S3_PIN     = 41,
    ESC_S4_PIN     = 47,
    ESC_S5_PIN     = 49,
    ESC_S6_PIN     = 53,
    VOLT_PIN       = 10,
};

enum PwmPin {
    MOVE_PIN       = 13,
    STRAFE_PIN     = 12,
    DIVE_PIN       = 11,
    YAW_PIN        = 9,
    PITCH_PIN      = 8,
    ROLL_PIN       = 7,
};

#endif