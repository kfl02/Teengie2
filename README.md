Teengie2
========

A Wingie2 clone based on the Teensy 4.0 microcontroller.

Wingie2 home page: https://www.mengqimusic.com/wingie2-introduction
Wingie2 firmware: https://github.com/mengqimusic/Wingie2
Wingie2 alternative Blippoo firmware: https://github.com/mengqimusic/bfw

The original Wingie2 is based on the Espressif ESP32 microcontroller. None of the special features of the ESP32 are used (Wifi, Bluetooth). The hardware of the Wingie2 is not open source, the two official firmwares from Meng Qi Music are.

This project is an attempt to build a Wingie2 clone based on the Teensy 4.0 microcontroller. The Teensy microcontroller are THE choice for audio projects, because of the powerful hardware and the excellent Audio library provided by the producer.

The firmware has been completely rewritten to accommommdate the use of quasi standardized Arduino/Teensyduino framework libraries, rather than the original's bare bone approach. At first, the original firmware will be emulated. The goal is, to also provide the alternative Blippoo firmware and be able to switch between those.

The Wingie2 provides two audio sources (MEMS microphones and line in) and one audio output (line out) and a TRS MIDI input. The Teengie2 will additionally provide USB audio input and output and USB MIDI input, because it is easy to do so.

Thanks to André Laska of TubeOhm (https://www.tubeohm.com/) for support.