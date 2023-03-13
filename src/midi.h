#pragma once

#ifndef TEENGIE2_MIDI_H
#define TEENGIE2_MIDI_H

#include <cstdint>

void handleNoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity);
void handleControlChange(uint8_t channel, uint8_t number, uint8_t value);

#endif // TEENGIE2_MIDI_H