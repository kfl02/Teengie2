#include <cstdint>
#include <algorithm>

#include "dsp.h"
#include "preferences.h"

static uint8_t poly_flip = 0;
static int oct[CHANNELS];
static int midi_val[CHANNELS][POTS][BYTES];
static int cave_freq_midi_value[CHANNELS][VOICES][BYTES];
static int a3_freq_midi_value[CHANNELS];
static int cm_freq[CHANNELS][CAVES][VOICES];
static float a3_freq;

static const auto CC_CAVE_FREQ_1_MSB = 23;
static const auto CC_CAVE_FREQ_1_LSB = 55;
static const auto CAVE_LOWEST_FREQ = 8;
static const auto CAVE_HIGHEST_FREQ = 15999;

static const auto CC_MIDI_CH_L = 20;
static const auto CC_MIDI_CH_R = 21;
static const auto CC_MIDI_CH_BOTH = 22;
static const auto CC_A3_FREQ_MSB = 23;
static const auto CC_A3_FREQ_LSB = 55;

void handleNoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity) {
    if(velocity) {
        if(channel == prefs.midi_ch_l) {
            setDspMidiPitch(LEFT, mode[0], pitch);
        } else if(channel == prefs.midi_ch_r) {
            setDspMidiPitch(RIGHT, mode[1], pitch);
        } else if(channel == prefs.midi_ch_both) {
            setDspMidiPitch(poly_flip, mode[poly_flip], pitch);
            poly_flip = 1 - poly_flip;
        }
    }
}

void handleControlChange(uint8_t channel, uint8_t number, uint8_t value) {
    if(channel == prefs.midi_ch_l) {
        setDspMidiParam(LEFT, number, value);
    } else if(channel == prefs.midi_ch_r) {
        setDspMidiParam(RIGHT, number, value);
    } else if(channel == prefs.midi_ch_both) {
        setDspMidiParam(LEFT, number, value);
        setDspMidiParam(RIGHT, number, value);
    } else if(channel == 14 || channel == 15) { // TODO: const in globals
        int ch = channel - 14; // TODO: const in globals
        int cave = oct[ch] + 1;

        if(mode[ch] == CAVE_MODE) {
            for(int v = 0; v < VOICES; v++) {
                if ((number == CC_CAVE_FREQ_1_MSB + v) || (number == CC_CAVE_FREQ_1_LSB + v)) {
                    if(number == CC_CAVE_FREQ_1_MSB + v) {
                        cave_freq_midi_value[ch][v][MSB] = value;

                        int midi_value_14bit = (cave_freq_midi_value[ch][v][MSB] << 7) | cave_freq_midi_value[ch][v][LSB];

                        midi_value_14bit = std::max(midi_value_14bit, CAVE_LOWEST_FREQ);
                        midi_value_14bit = std::min(midi_value_14bit, CAVE_HIGHEST_FREQ);

                        cm_freq[ch][cave][v] = midi_value_14bit;

                        setDspCaveFreq(ch, v, cm_freq[ch][cave][v]);
                    } else {
                        cave_freq_midi_value[ch][v][LSB] = value;
                    }
                }
            }
        }
    } else if(channel == 16) {
        switch(number) {
          case CC_MIDI_CH_L:
            prefs.midi_ch_l = value;
            break;

          case CC_MIDI_CH_R:
            prefs.midi_ch_r = value;
            break;

          case CC_MIDI_CH_BOTH:
            prefs.midi_ch_both = value;
            break;

          case CC_A3_FREQ_MSB: {
                a3_freq_midi_value[MSB] = value;

                int midi_value_14bit = (a3_freq_midi_value[MSB] << 7) | a3_freq_midi_value[LSB];
                float freq_offset = (float)midi_value_14bit / 100.0f - 81.92f;

                a3_freq = 440.0f + freq_offset;
                prefs.a3_freq_offset = freq_offset;

                setDspA3Freq(a3_freq);
            }
            break;

          case CC_A3_FREQ_LSB:
            a3_freq_midi_value[LSB] = value;
            break;

          default:
            break;
        }
    }
}
