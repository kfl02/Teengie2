#include <Arduino.h>
#include <MIDI.h>
#include <Adafruit_MCP23X17.h>
#include <TeensyThreads.h>

#include "midi.h"

auto RW_MODE = false;
auto RO_MODE = true;

auto MODE_NUM = 3; // +1

auto BASE_NOTE = 48;
auto POLY_MODE_NOTE_ADD_L = 12;
auto POLY_MODE_NOTE_ADD_R = 24;
auto MIC_BOOST = 0xAAC4; // 0xFFC4 = 48dB, 0x99C4 = 30dB, 0x88C4 = 0dB
auto DAC_VOL = 0xA2A2; // 左右通道输出音量 A0 = 0dB, A2 = 1.5dB, A4 = 3dB

auto slider_movement_detect = 256;


struct MySettings : public midi::DefaultSettings
{
  static const unsigned SysExMaxSize = 16;
  static const bool UseRunningStatus = false;
  static const bool Use1ByteParsing = true;
  static const long BaudRate = 31250;
};


MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial2, MIDI, MySettings);

Adafruit_MCP23X17 mcp0;
Adafruit_MCP23X17 mcp1;

void setup() {
    Serial.begin(115200);

    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleControlChange(handleControlChange);
    MIDI.MidiInterface::turnThruOff();
}

void loop() {
    MIDI.read();
}