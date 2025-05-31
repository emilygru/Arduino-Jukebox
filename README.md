# Arduino-Jukebox
An Arduino-operated Jukebox

## Project Overview
Our Arduino based jukebox is a modern take on the classic coin-operated machines found in retro diners. With a practical and contemporary twist, this project allows users to select from a variety of songs and enjoy the nostalgic charm of musical entertainment blended with modern electronics and design.

## Features
- RFID system to scan and start the system instead of a coin-slot mechanism
- Keypad and LCD system for song selection
- Stereo speakers
- Volume control buttons/switch-track buttons
- LED light sequence

## Components
**Arduino Mega**
- 4x4 Keypad
- LCD Display
- DF Player
- Amplifier
- Two 32W speakers

**Arduino Uno**
- WS2812B LEDs

## How it Works
When the RFID keycard is scanned onto the RFID, the system is initialized. From there, the user can begin to type the short-number sequence that corresponds to their song of choice into the keypad. The enter button is the #, and after the user presses it, the song of choice will play. If there's a mistake while typing, the asterisk key will clear the input and 
the LCD display. It's also important to note that in order for the next song to be chosen, the previous song must go through the entirety of its duration.

As far as the internal sound system goes, there are two main components: the DF player and the amplifier. All the songs of choice are dowloaded onto an SD card as mp3 files. The program reads file 1, file 2, etc. in the order in which they are placed on the SD card. The DF player then extracts the files into sound and the amplifier then amplifies the audio to suit the larger speakers. There are manual volume buttons that can be connected to the DF player: long press of one or the other will increase or decrease volume; short press will switch between the tracks in either direction. 
