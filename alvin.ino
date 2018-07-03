#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
//#include "vendor/Adafruit-GFX-Library-1.2.3/Adafruit_GFX.h"
//#include "vendor/Adafruit-PCD8544-Nokia-5110-LCD-library/Adafruit_PCD8544.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(18, 20, 19);

const int blPin = 10;

void setup() {

  pinMode(blPin, OUTPUT);
  analogWrite(blPin, 100);

  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(60);

  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();

}

void loop() {
}
