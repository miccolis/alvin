## Circuit

7 - SS RFID
8 - RST RFID
20 (A2) - SCE Screen
19 (A1) - RST Screen
18 (A0) - D/C Screen
15 - SCLK Screen & RFID
14 - MISO RFID
16 - MOSI Screen & RFID
10 - LED Screen Backlight (PWM) (w/ 330 Ohm resistor)

## Dependencies

Install the following Libraries using the Arduino IDE

1. "Adafruit GFX Library" 
2. "Adafruit PCD8544 Nokia 5110 LCD library"
3. "MFRC522"

## Graphics

Images must be less that 84x48 pixels and monochrome. Images were created using Gimp and coverted to the appropriate binary format using http://javl.github.io/image2cpp/

## Debug output

minicom -D /dev/tty.usbmodem1412241 -b 9600

## Links

https://github.com/miguelbalboa/rfid

https://github.com/adafruit/Adafruit-GFX-Library

https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library

