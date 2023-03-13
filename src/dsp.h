#pragma once

#ifndef TEENGIE2_DSP_H
#define TEENGIE2_DSP_H

#include <cstdint>

#include "globals.h"

void setDspMidiPitch(uint8_t ch, Mode mode, uint8_t pitch);
void setDspMidiParam(uint8_t ch, uint8_t number, uint8_t value);
void setDspMute(uint8_t kb, uint8_t voice, bool state);
void setDspCaveFreq(uint8_t kb, uint8_t voice, int freq);
void setDspA3Freq(float a3_freq);
void setDspMix(float mix);
void setDspDecay(float decay);
void setDspVolume(float vol);

#endif // TEENGIE2_DSP_H