#pragma once

#ifndef TEENGIE2_DSP_H
#define TEENGIE2_DSP_H

#include <cstdint>

#include "globals.h"

const void setDspMidiPitch(const uint8_t ch, const Mode mode, const uint8_t pitch);
const void setDspMidiParam(const uint8_t ch, const uint8_t number, const uint8_t value);
const void setDspMute(const uint8_t kb, const uint8_t voice, const bool state);
const void setDspCaveFreq(const uint8_t kb, const uint8_t voice, const int freq);
const void setDspA3Freq(const float a3_freq);
const void setDspMix(const float mix);
const void setDspDecay(const float decay);
const void setDspVolume(const float vol);

#endif // TEENGIE2_DSP_H