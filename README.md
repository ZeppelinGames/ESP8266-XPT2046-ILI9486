# XPT2046 ILI9486 ESP8266  
ESP8266 + TFT XPT2046 ILI9486 touchscreen display. Tested with a [3.5" Raspberry Pi touchscreen from Jaycar](https://www.jaycar.com.au/raspberry-pi-3-5in-touchscreen-lcd-with-stylus-and-enclosure/p/XC4631)

## Required Libraries  
[Bodmer's TFT eSPI](https://github.com/Bodmer/TFT_eSPI) - Manages drawing graphics to display  
[ardnew's XPT2046 Calibrated](https://github.com/ardnew/XPT2046_Calibrated) - Manages calibration of touchscreen (could also be swapped out for [Paul Stoffregen's library](https://github.com/PaulStoffregen/XPT2046_Touchscreen)  

## Setup  
Bodmer's TFT library requires prior setup. Replace the `User_Setup.h` in `/Arduino/Libraries/TFT_eSPI/` (location of where your arduino libraries are installed) with the one in this repo. This sets up the ESP8266 pinout and screen frequency.
