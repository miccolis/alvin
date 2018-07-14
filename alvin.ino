#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <MFRC522.h>
#include "./images.h"
#include "./item.h"

// Declare the wiring
MFRC522 mfrc522(7, 8);
Adafruit_PCD8544 display = Adafruit_PCD8544(18, 20, 19);
const uint8_t blPin = 10;

// Global state
MFRC522::Uid activeUid;

const uint8_t availableItemsLen = 4;
Item availableItems[availableItemsLen];

const uint8_t patternLen = 8;
uint8_t pattern[patternLen];
uint8_t gameStep = 0;
uint8_t gamelevel = 0;

void setup() {

  pinMode(blPin, OUTPUT);
  analogWrite(blPin, 100);

  loadItems(availableItems);

  display.begin();
  display.setRotation(2);
  display.setContrast(60);
  display.clearDisplay();

  for (int i = 0; i < 4; i++) {
      showItem(1);
      delay(1000);
  }

  display.fillScreen(WHITE);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Ready!");
  display.display();
  delay(2000);

  newPattern(pattern, patternLen);

  mfrc522.PCD_Init();

  Serial.begin(9600);
  //mfrc522.PCD_DumpVersionToSerial();
}

void loop() {
    static uint8_t selectedIdx;

    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
            return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
            return;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    //mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));

    copyUid(&(mfrc522.uid), &activeUid);
    mfrc522.PICC_HaltA();

    display.clearDisplay();

    selectedIdx = findItemByUid(availableItems, availableItemsLen, &activeUid);
    if (selectedIdx > availableItemsLen) {
        display.println("Not found!");
        printUid(&activeUid);
        display.display();
    } else {
        showItem(selectedIdx);
    }

    delay(2000);

    display.clearDisplay();
    display.println("Ready!");
    display.display();

}

void copyUid(MFRC522::Uid* src, MFRC522::Uid* dest) {
    dest->size = src->size;
    dest->sak = src->sak;
    for(uint8_t i = 0; i < src->size; i++) {
        dest->uidByte[i] = src->uidByte[i];
    }
}

void printUid(MFRC522::Uid* uid) {
    display.print(F("Card UID:"));
    for (uint8_t i = 0; i < uid->size; i++) {
        if(uid->uidByte[i] < 0x10)
            display.print(F(" 0"));
        else
            display.print(F(" "));
        display.print(uid->uidByte[i], HEX);
    }
    display.println();
}

void showItem(uint8_t i) {
    uint16_t w = availableItems[i].dim[0];
    uint16_t h = availableItems[i].dim[1];

    display.fillScreen(WHITE);
    if (i == 0) {
        display.drawBitmap(0, 0, blackCar, w, h, BLACK);
    } else if (i == 1) {
        display.drawBitmap(0, 0, datsun, w, h, BLACK);
    } else if (i == 2) {
        display.drawBitmap(0, 0, redCar, w, h, BLACK);
    } else if (i == 3) {
        display.drawBitmap(0, 0, snowplow, w, h, BLACK);
    }
    display.display();
}

void newPattern(uint8_t pattern[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++){
        pattern[i] = random(0, availableItemsLen);
    }
}

