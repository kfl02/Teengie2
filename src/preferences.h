#pragma once

#ifndef TEENGIE2_PREFERENCES_H
#define TEENGIE2_PREFERENCES_H

#include <cstdint>

#include "globals.h"

struct TeengiePreferences {
    uint32_t init;
    uint8_t midi_ch_l;
    uint8_t midi_ch_r;
    uint8_t midi_ch_both;
    float a3_freq_offset;
    float pre_clip_gain;
    float post_clip_gain;
    float left_thresh;
    float right_thresh;
    uint8_t left_mode;
    uint8_t right_mode;
    uint16_t cm_freq[CHANNELS][CAVES][VOICES];
    uint8_t cm_ms[CHANNELS][CAVES][VOICES];

    bool isInitialized();
};

bool operator==(const TeengiePreferences &lhs, const TeengiePreferences &rhs);

extern const TeengiePreferences default_prefs;
extern TeengiePreferences prefs;

#endif // TEENGIE2_PREFERENCES_H