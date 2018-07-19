#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <MFRC522.h>
#include "./images.h"
#include "./item.h"
#include "./game.h"

// Declare the wiring
MFRC522 mfrc522(7, 8);
Adafruit_PCD8544 display = Adafruit_PCD8544(18, 20, 19);
const uint8_t blPin = 10;

// Global state
const uint8_t availableItemsLen = 4;
Item availableItems[availableItemsLen];

GameState s;

void setup() {

  pinMode(blPin, OUTPUT);
  analogWrite(blPin, 100);

  display.begin();
  display.setRotation(2);
  display.setContrast(60);
  display.display();
  delay(1000);
  display.clearDisplay();

  display.fillScreen(WHITE);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Preparing...");
  display.display();

  randomSeed(analogRead(21)); // Pin 21 (A3) is expected to be unconnected

  loadItems(availableItems);
  s.reset();

  delay(2000);

  mfrc522.PCD_Init();

  Serial.begin(9600);
  //mfrc522.PCD_DumpVersionToSerial();
}

void loop() {
    static uint8_t selectedIdx;
    static MFRC522::Uid activeUid;

    if (!s.playerTurn) {
        Serial.println("machine goes");
        Serial.println(s.gameLevel);
        if (s.gameLevel == s.patternLen) { // untested
            display.println("You Won!");
            display.display();
            s.reset();
            delay(2000);
        } else {
            for (uint8_t l = 0; l <= s.gameLevel; l++) {
                showItem(s.pattern[l]);
                display.setCursor(0, 40);
                display.println(l);
                Serial.println(l);
                Serial.println(s.pattern[l]);
                delay(1000);

                display.fillScreen(WHITE);
                display.display();
                delay(200);
            }
            display.clearDisplay();
            display.println("Go!");
            display.display();
            s.playerTurn = true;
        }
        return;
    }

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

    Serial.println("human went");
    Serial.println(selectedIdx);
    Serial.println(s.pattern[s.gameStep]);
    if (selectedIdx > availableItemsLen) {
        display.println("Not found!");
        printUid(&activeUid);
        display.display();
        delay(2000);
    } else if (selectedIdx == s.pattern[s.gameStep]) {
        showItem(selectedIdx);
        display.setCursor(0, 40);
        display.println("Excellent!");
        display.display();

        Serial.println("Advance step");
        s.gameStep++;

        if (s.gameStep > s.gameLevel) {
            Serial.println("Advance level");
            s.gameLevel++;
            s.gameStep = 0;
            s.attempt = 0;
            s.playerTurn = false;
            delay(2000);
        }
        return;
    } else {
        showItem(selectedIdx);
        s.attempt++;
        if (s.attempt >= 3) {
            delay(2000);
            s.reset();
            display.clearDisplay();
            display.println("Game over!");
            display.display();
            delay(2000);
            return;
        }
        s.gameStep = 0;
        display.setCursor(0, 40);
        display.println("Try again!");
        display.display();
        delay(2000);

        display.clearDisplay();
        display.println("Go!");
        display.display();
        return;
    }
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



