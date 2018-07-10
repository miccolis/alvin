#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <MFRC522.h>
#include "./images.h"

MFRC522 mfrc522(7, 8);

Adafruit_PCD8544 display = Adafruit_PCD8544(18, 20, 19);

const int blPin = 10;

MFRC522::Uid activeUid;

void setup() {

  pinMode(blPin, OUTPUT);
  analogWrite(blPin, 100);

  display.begin();
  display.setRotation(2);

  display.setContrast(60);
  
  display.clearDisplay();
  display.drawBitmap(0, 0, redDB, 72, 48, BLACK);
  display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Ready!");
  display.display();
  delay(2000);

  Serial.begin(9600);
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
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

    copyUid(&(mfrc522.uid), &activeUid);

    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

    delay(100);
    display.clearDisplay();
    display.println("Card read complete!");
    printUid(&activeUid);
    display.display();
    delay(2000);
    display.clearDisplay();
    display.println("Ready!");
    display.display();

}

void copyUid(MFRC522::Uid* src, MFRC522::Uid* dest) {
    dest->size = src->size;
    dest->sak = src->sak;
    for(int i = 0; i < src->size; i++) {
        dest->uidByte[i] = src->uidByte[i];
    }
}

void printUid(MFRC522::Uid* uid) {
    display.print(F("Card UID:"));
    for (byte i = 0; i < uid->size; i++) {
        if(uid->uidByte[i] < 0x10)
            display.print(F(" 0"));
        else
            display.print(F(" "));
        display.print(uid->uidByte[i], HEX);
    }
    display.println();
}
