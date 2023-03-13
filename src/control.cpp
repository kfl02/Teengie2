#include <Arduino.h>
#include <cstdlib>

#include "globals.h"
#include "dsp.h"
#include "fscale.h"

const void control() {
    // potentiometers

    for(int i = 0; i < POTS; i++) {
        pot_val_realtime[i]  = analogRead(pot_pins[i]);

        int difference = abs(pot_val_realtime[i] - pot_val_sampled[i]);

        if(!realtime_value_valid[i]) {
            if(difference > SLIDER_MOVEMENT_DETECT) {
                realtime_value_valid[i] = true;
            }
        }
    }

    float mix = pot_val_realtime[MIX] / 4095.0f;

    if(realtime_value_valid[MIX]) {
        setDspMix(mix);
    }

    float decay = (pot_val_realtime[DECAY] / 4095.0f) * 9.9f + 0.1f;

    decay = fscale(0.1, 10., 0.1, 10., decay, -3.25);

    if(realtime_value_valid[DECAY]) {
        setDspDecay(decay);
    }

    float vol = pot_val_realtime[VOL] / 4095.0f;

    if(realtime_value_valid[VOL]) {
        setDspVolume(vol);
    }

    // source

    // octave

    // mode

    // keys
}