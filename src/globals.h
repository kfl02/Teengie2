#pragma once

#ifndef TEENGIE2_GLOBALS_H
#define TEENGIE2_GLOBALS_H

#include <cstdint>

enum Mode {
    POLY_MODE,
    STRING_MODE,
    BAR_MODE,
    CAVE_MODE
};

enum Source {
    MIC,
    LINE,
    USB
};

// array indices and limits

constexpr auto MSB = 0;
constexpr auto LSB = 1;
constexpr auto BYTES = 2;

constexpr auto LEFT = 0;
constexpr auto RIGHT = 1;
constexpr auto CHANNELS = 2;

constexpr auto VOICES = 9;
constexpr auto CAVES = 3;

constexpr auto MIX = 0;
constexpr auto DECAY = 1;
constexpr auto VOL = 2;
constexpr auto POTS = 3;

constexpr auto SLIDER_MOVEMENT_DETECT = 256;

// Teensy pins

constexpr uint8_t pot_pins[POTS] = { 14, 15, 16 };

// values

extern bool realtime_value_valid[POTS];
extern int pot_val_realtime[POTS];
extern int pot_val_sampled[POTS];

extern Mode mode[CHANNELS];
extern Source source;

#endif // TEENGIE2_GLOBALS_H
