#include <cstdint>

#include "globals.h"
#include "audio_patch.h"
#include "fscale.h"

static int current_poly[CHANNELS] = { 0, 0 };
static bool mode_change_from_midi[CHANNELS] = { false, false };
static bool startup = true;
static int midi_val[CHANNELS][POTS][BYTES];

static constexpr auto CC_MODE = 0;
static constexpr auto CC_MIX = 11;
static constexpr auto CC_DECAY = 1;
static constexpr auto CC_VOL = 7;

const void setDspMidiPitch(const uint8_t ch, const Mode mode, const uint8_t pitch) {
    switch(mode) {
      case STRING_MODE:
      case BAR_MODE:
        if(ch == LEFT) {
            wingie2_1.setParamValue("note0", pitch);
        } else {
            wingie2_1.setParamValue("note1", pitch);
        }
        break;

      case POLY_MODE:
        switch(current_poly[ch]) {
          case 0:
            current_poly[ch] = 1;

            if(ch == 0) {
                wingie2_1.setParamValue("/Wingie/left/poly_note_0", pitch);
            } else {
                wingie2_1.setParamValue("/Wingie/right/poly_note_0", pitch);
            }
            break;

          case 1:
            current_poly[ch] = 2;

            if(ch == 0) {
                wingie2_1.setParamValue("/Wingie/left/poly_note_1", pitch);
            } else {
                wingie2_1.setParamValue("/Wingie/right/poly_note_1", pitch);
            }
            break;

          case 2:
            current_poly[ch] = 0;

            if(ch == 0) {
                wingie2_1.setParamValue("/Wingie/left/poly_note_2", pitch);
            } else {
                wingie2_1.setParamValue("/Wingie/right/poly_note_2", pitch);
            }
            break;
        }
        break;

      default:
        break;
    }
}

const void setDspMidiParam(const uint8_t ch, const uint8_t number, const uint8_t value) {
    switch(number) {
      case CC_MODE: {
            Mode modeFromMidi = (value >> 5);

            if(mode[ch] != modeFromMidi) {
                mode[ch] = modeFromMidi;
                mode_change_from_midi[ch] = true;
            }
        }
        break;

      case CC_MIX: {
            realtime_value_valid[MIX] = false;
            pot_val_sampled[MIX] = pot_val_realtime[MIX];
            midi_val[ch][MIX][MSB] = value;

            int midi_val_14_bit = (midi_val[ch][MIX][MSB] << 7) | midi_val[ch][MIX][LSB];
            float v = midi_val_14_bit / 16383.0f;

            if(ch == LEFT) {
                wingie2_1.setParamValue("mix0", v);
            } else {
                wingie2_1.setParamValue("mix1", v);
            }
        }
        break;

      case CC_MIX + 32:
        realtime_value_valid[MIX] = false;
        pot_val_sampled[MIX] = pot_val_realtime[MIX];
        midi_val[ch][MIX][LSB] = value;
        break;

      case CC_DECAY: {
            realtime_value_valid[DECAY] = false;
            pot_val_sampled[DECAY] = pot_val_realtime[MIX];
            midi_val[ch][DECAY][MSB] = value;

            int midi_val_14_bit = (midi_val[ch][DECAY][MSB] << 7) | midi_val[ch][DECAY][LSB];
            float v = (midi_val_14_bit / 16383.0f) * 9.9f + 0.1f;

            v = fscale(0.1f, 10.0f, 0.1f, 10.0f, v, -3.25f);

            if(!startup) {
                if(ch == LEFT) {
                    wingie2_1.setParamValue("/Wingie/left/decay", v);
                } else {
                    wingie2_1.setParamValue("/Wingie/right/decay", v);
                }
            }
        }
        break;

      case CC_DECAY + 32:
        realtime_value_valid[DECAY] = false;
        pot_val_sampled[DECAY] = pot_val_realtime[MIX];
        midi_val[ch][DECAY][LSB] = value;
        break;

      case CC_VOL: {
            realtime_value_valid[VOL] = false;
            pot_val_sampled[VOL] = pot_val_realtime[MIX];
            midi_val[ch][VOL][MSB] = value;

            int midi_val_14_bit = (midi_val[ch][VOL][MSB] << 7) | midi_val[ch][VOL][LSB];
            float v = midi_val_14_bit / 16383.0f;

            if(ch == LEFT) {
                wingie2_1.setParamValue("volume0", v);
            } else {
                wingie2_1.setParamValue("volume1", v);
            }
        }
        break;

      case CC_VOL + 32:
        realtime_value_valid[VOL] = false;
        pot_val_sampled[VOL] = pot_val_realtime[MIX];
        midi_val[ch][VOL][LSB] = value;
        break;

      default:
        break;
    }
}

const void setDspMute(const uint8_t kb, const uint8_t voice, const bool state) {
    char buff[100];

    if(kb == LEFT) {
        snprintf(buff, sizeof(buff), "/Wingie/left/mute_%d", voice);
    } else {
        snprintf(buff, sizeof(buff), "/Wingie/right/mute_%d", voice);
    }

    const std::string str = buff;

    wingie2_1.setParamValue(str, state);
}

const void setDspCaveFreq(const uint8_t kb, const uint8_t voice, const int freq) {
    char buff[100];

    if(kb == LEFT) {
        snprintf(buff, sizeof(buff), "/Wingie/left/cave_freq_%d", voice);
    } else {
        snprintf(buff, sizeof(buff), "/Wingie/right/cave_freq_%d", voice);
    }

    const std::string str = buff;

    wingie2_1.setParamValue(str, freq);
}

const void setDspA3Freq(const float a3_freq) {
    wingie2_1.setParamValue("/Wingie/left/a3_freq", a3_freq);
    wingie2_1.setParamValue("/Wingie/right/a3_freq", a3_freq);
}

const void setDspMix(const float mix) {
    wingie2_1.setParamValue("mix0", mix);
    wingie2_1.setParamValue("mix1", mix);
}

const void setDspDecay(const float decay) {
    wingie2_1.setParamValue("/Wingie/left/decay", decay);
    wingie2_1.setParamValue("/Wingie/left/decay", decay);
}

const void setDspVolume(const float vol) {
    wingie2_1.setParamValue("volume0", vol);
    wingie2_1.setParamValue("volume1", vol);
}
