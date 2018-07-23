Alvin
-----

A memory game with matchbox cars, an interactive game for a computer with no buttons. Players need to remember the order that cars are shown and present the correct cars to the computer in order.

The project requires some wires and just a few other parts;

1. Sparkfun "Pro Micro" Arduino compatible board.
2. Nokia 5510 LCD screen. Available from Adafruit or Sparkfun.
3. MFRC522 reader. Available from Amazon.
4. 330 Ohm resistor.
5. Matchbox cars with plastic bottoms, metal parts interfere with the RFID antenna and will not work.
6. Some Mifare classic RFID stickers.

## Circuit

- 7 - SS RFID
- 8 - RST RFID
- 20 (A2) - SCE Screen
- 19 (A1) - RST Screen
- 18 (A0) - D/C Screen
- 15 - SCLK Screen & RFID
- 14 - MISO RFID
- 16 - MOSI Screen & RFID
- 10 - LED Screen Backlight (PWM) (w/ 330 Ohm resistor)

## Dependencies

Install the following Libraries using the Arduino IDE;

1. "Adafruit GFX Library" 
2. "Adafruit PCD8544 Nokia 5110 LCD library"
3. "MFRC522"

## Graphics

Images must be less that 84x48 pixels and monochrome. Included images were created using Gimp and coverted to the appropriate binary format using http://javl.github.io/image2cpp/

Note: images must have an width that is a multiple of eight. Not sure entirely why, mostly likely has to do with byte alignment.

## Debug output

minicom -D /dev/tty.usbmodem1412241 -b 9600

## Links

https://github.com/miguelbalboa/rfid

https://github.com/adafruit/Adafruit-GFX-Library

https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library

