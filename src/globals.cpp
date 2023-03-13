#include "globals.h"

Mode mode[CHANNELS];
Source source;
bool realtime_value_valid[POTS] = { true, true, true };
int pot_val_realtime[POTS];
int pot_val_sampled[POTS];

