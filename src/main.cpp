#include <Arduino.h>
#include <MIDI.h>
#include <Adafruit_MCP23X17.h>
#include <USBHost_t36.h>

#include "midi.h"

auto RW_MODE = false;
auto RO_MODE = true;

auto MODE_NUM = 3; // +1

auto BASE_NOTE = 48;
auto POLY_MODE_NOTE_ADD_L = 12;
auto POLY_MODE_NOTE_ADD_R = 24;

struct MySettings : public midi::DefaultSettings
{
    static const unsigned SysExMaxSize = 16;
    static const bool UseRunningStatus = false;
    static const bool Use1ByteParsing = true;
    static const long BaudRate = 31250;
};

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial2, MIDI, MySettings);

Adafruit_MCP23X17 mcp_left;
Adafruit_MCP23X17 mcp_right;

void setup() {
    Serial.begin(115200);

    myusb.begin();
    midi1.setHandleNoteOn(handleNoteOn);
    midi1.setHandleControlChange(handleControlChange);

    usbMIDI.setHandleNoteOn(handleNoteOn);
    usbMIDI.setHandleControlChange(handleControlChange);

    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleControlChange(handleControlChange);
    MIDI.MidiInterface::turnThruOff();
}

void loop() {
    MIDI.read();
}