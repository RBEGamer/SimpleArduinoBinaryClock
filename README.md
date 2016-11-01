# SimpleArduinoBinaryClockhttps://github.com/RBEGamer/SimpleArduinoBinaryClock
Arduino based binary clock with hours and minutes display, nightmode and alarm.
It uses a Arsuino Nano and the WS2812 Leds,to show the time in a binary format.
The time, alarm time and nightmode time, can be set by the 4 switches on the back of the clock.
With the top button, you can change the color and stop the ringing alarm.

# PARTS

* WS2813 led strip with 16 leds
* Any Arduino based board, but use a small one for a small case
* I2C RTC module (i use the DS3231 or you can use the DS1307)
* 5V Power supply or you power it with usb
* 5 Pushbuttons
* mini speaker
A detailed partslist is located at to_bux.xlsx

# SOFTWARE SETUP

* Download the sketch, lpcated on /code
* Download the latest Arduino IDE
* Download the Adafruit-Neopixel libary

# BUILD YOUR CLOCK

* Cut the ES2812 into 4 strips with 4 leds each
* 

![Gopher image](BILDER/Foto 12.11.14 22 25 32.jpg)
![Gopher image](BILDER/Foto 11.11.14 00 32 51.jpg)
![Gopher image](BILDER/Foto 10.11.14 13 44 19.jpg)
