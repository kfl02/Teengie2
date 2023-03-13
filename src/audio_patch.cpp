#include "audio_patch.h"

#include "Wingie2.h"

// GUItool: begin automatically generated code
AudioInputUSB            usb1;           //xy=209,147
AudioInputI2S2           i2s2_1;         //xy=211,99
AudioInputI2S            i2s1;           //xy=212,50
AudioMixer4              mixer1;         //xy=472,58
AudioMixer4              mixer2;         //xy=474,141
Wingie2                  wingie2_1;      //xy=692,97
AudioOutputI2S           i2s2;           //xy=970,87
AudioOutputUSB           usb2;           //xy=971,151
AudioConnection          patchCord1(usb1, 0, mixer1, 2);
AudioConnection          patchCord2(usb1, 1, mixer2, 2);
AudioConnection          patchCord3(i2s2_1, 0, mixer1, 1);
AudioConnection          patchCord4(i2s2_1, 1, mixer2, 1);
AudioConnection          patchCord5(i2s1, 0, mixer1, 0);
AudioConnection          patchCord6(i2s1, 1, mixer2, 0);
AudioConnection          patchCord7(mixer1, 0, wingie2_1, 0);
AudioConnection          patchCord8(mixer2, 0, wingie2_1, 1);
AudioConnection          patchCord9(wingie2_1, 0, i2s2, 0);
AudioConnection          patchCord10(wingie2_1, 0, usb2, 0);
AudioConnection          patchCord11(wingie2_1, 1, i2s2, 1);
AudioConnection          patchCord12(wingie2_1, 1, usb2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=267,298
// GUItool: end automatically generated code
