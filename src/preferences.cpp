#include <Arduino.h>
#include <EEPROM.h>

#include "preferences.h"

constexpr uint32_t teengie_preferences_init_magic = 0xFEEDBACC;

const TeengiePreferences default_prefs = {
    teengie_preferences_init_magic,
    1, // uint8_t midi_ch_l;
    2, // uint8_t midi_ch_r;
    3, // uint8_t midi_ch_both;
    0.0f, // float a3_freq_offset;
    0.2475f, // float pre_clip_gain;
    0.825f, // float post_clip_gain;
    0.4125f, // float left_thresh;
    0.4125f, // float right_thresh;
    0, // uint8_t left_mode;
    0, // uint8_t right_mode;
    {
        {
            {62, 115, 218, 411, 777, 1500, 2800, 5200, 11000},
            {205, 304, 370, 523, 540, 800, 913, 1568, 2400},
            {212, 425, 531, 637, 1168, 2017, 2336, 2654, 3693}
        },
        {
            {62, 115, 218, 411, 777, 1500, 2800, 5200, 11000},
            {205, 304, 370, 523, 540, 800, 913, 1568, 2400},
            {212, 425, 531, 637, 1062, 2017, 2336, 2654, 3693}
        }
    }, // uint16_t cm_freq[2][3][9];
    {
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
        }
    } // uint8_t cm_ms[2][3][9];
};

TeengiePreferences prefs;

const bool TeengiePreferences::isInitialized() {
    return init == teengie_preferences_init_magic;
}

bool operator==(const TeengiePreferences &lhs, const TeengiePreferences &rhs) {
    if(lhs.init != rhs.init
        || lhs.midi_ch_l != rhs.midi_ch_l
        || lhs.midi_ch_r != rhs.midi_ch_r
        || lhs.midi_ch_both != rhs.midi_ch_both
        || lhs.a3_freq_offset != rhs.a3_freq_offset
        || lhs.pre_clip_gain != rhs.pre_clip_gain
        || lhs.post_clip_gain != rhs.post_clip_gain
        || lhs.left_thresh != rhs.left_thresh
        || lhs.right_thresh != rhs.right_thresh
        || lhs.left_mode != rhs.left_mode
        || lhs.right_mode != rhs.right_mode
    ) {
        return false;
    }

    for(int ch = 0; ch < 2; ch++) {
        for (int cave = 0; cave < 3; cave++) {
            for (int v = 0; v < 9; v++) {
                if(lhs.cm_freq[ch][cave][v] != rhs.cm_freq[ch][cave][v]
                    || lhs.cm_ms[ch][cave][v] != rhs.cm_ms[ch][cave][v]) {
                        return false;
                    }
            }
        }
    }

    return true;
}
