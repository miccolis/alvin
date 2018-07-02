#include <SPI.h>
#include "./vendor/LCD_Functions.h"
//#include "./vendor/rfid/src/MFRC522.h"

//constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
//constexpr uint8_t SS_PIN = 10;     // Configurable, see typical pin layout above
 
//MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

//MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
//byte nuidPICC[4];


const int pin = 17;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
}

void loop() {
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  
}
