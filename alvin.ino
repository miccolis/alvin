#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <MFRC522.h>

MFRC522 mfrc522(7, 8);

Adafruit_PCD8544 display = Adafruit_PCD8544(18, 20, 19);

const int blPin = 10;

void setup() {

  pinMode(blPin, OUTPUT);
  analogWrite(blPin, 100);

  display.begin();
  display.setRotation(2);

  display.setContrast(60);

  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();

  Serial.begin(9600);
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Ready!");
  display.display();
  delay(2000);
}

void loop() {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
            return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
            return;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
