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
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Get");
  display.println("Ready!");
  display.display();

  randomSeed(analogRead(21)); // Pin 21 (A3) is expected to be unconnected

  loadItems(availableItems);
  s.reset();

  delay(2000);

  mfrc522.PCD_Init();
}

void loop() {
    static uint8_t selectedIdx;
    static MFRC522::Uid activeUid;

    if (!s.playerTurn) {
        if (s.gameLevel == s.patternLen) {
            victoryAnimation();
            display.clearDisplay();
            display.setTextSize(2);
            display.println("You");
            display.println("win!");
            display.display();
            s.reset();
            delay(5000);
        } else {
            for (uint8_t l = 0; l <= s.gameLevel; l++) {
                display.fillScreen(WHITE);
                display.display();
                delay(1000);

                showItem(s.pattern[l]);
                display.setCursor(0, 40);
                display.println(l);
                delay(1000);
            }
            display.clearDisplay();
            display.setTextSize(2);
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

    copyUid(&(mfrc522.uid), &activeUid);
    mfrc522.PICC_HaltA();

    display.clearDisplay();

    selectedIdx = findItemByUid(availableItems, availableItemsLen, &activeUid);

    if (selectedIdx > availableItemsLen) {
        display.setTextSize(1);
        display.println("Not found!");
        printUid(&activeUid);
        display.display();
        delay(2000);
    } else if (selectedIdx == s.pattern[s.gameStep]) {
        showItem(selectedIdx);
        display.setCursor(0, 40);
        display.setTextSize(1);
        display.println("Great!");
        display.display();

        s.gameStep++;

        delay(1000);

        display.fillScreen(WHITE);
        display.setTextSize(2);
        display.println("Go!");
        display.display();

        if (s.gameStep > s.gameLevel) {
            s.gameLevel++;
            s.gameStep = 0;
            s.attempt = 0;
            s.playerTurn = false;
        }
        return;
    } else {
        showItem(selectedIdx);
        s.attempt++;
        if (s.attempt >= 3) {
            delay(2000);
            s.reset();
            display.clearDisplay();
            display.setTextSize(2);
            display.println("Game");
            display.println("over!");
            display.display();
            delay(2000);
            return;
        }
        s.gameStep = 0;
        display.setCursor(0, 40);
        display.setTextSize(1);
        display.println("Try again...");
        display.display();
        delay(1000);

        display.fillScreen(WHITE);
        display.display();
        delay(1000);

        s.playerTurn = false;
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
    showItem(i, 0, 0);
}

void showItem(uint8_t i, int16_t x, int16_t y) {
    uint16_t w = availableItems[i].dim[0];
    uint16_t h = availableItems[i].dim[1];

    display.fillScreen(WHITE);
    if (i == 0) {
        display.drawBitmap(x, y, blackCar, w, h, BLACK);
    } else if (i == 1) {
        display.drawBitmap(x, y, datsun, w, h, BLACK);
    } else if (i == 2) {
        display.drawBitmap(x, y, redCar, w, h, BLACK);
    } else if (i == 3) {
        display.drawBitmap(x, y, snowplow, w, h, BLACK);
    }
    display.display();
}

void victoryAnimation() {
    cruiseAninmation(2, 700);
    cruiseAninmation(1, 1000);
    cruiseAninmation(0, 1000);
    cruiseAninmation(3, 1500);
}

void cruiseAninmation(uint8_t car, uint16_t ms) {
    uint8_t steps = 20;
    uint16_t adjust = (84 * 2) / steps;
    uint16_t wait = ms / steps;

    int16_t x = 84;
    for (int8_t i = steps + 2; i > 0; i--) { // plus one to get item off screen,
                                             // plus two for looks.
        showItem(car, x, 0);
        x = x - adjust;
        delay(wait);
    }
    return;
}
