#include <Arduino.h>
#include <esp32-s3-motor-shield-1.0-pin-mapping.h>
#include <nrf24.h>
#include "motion-control.h"
#include "motor-control.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"
#include "SPI.h"

#define DEBUG_RADIO true

RF24 radio(NRF_24_CE, NRF_24_CSN);
byte address[][6] = { "pipe1", "pipe2" };

int16_t joystickValues[] = { 1, 1, 1, 1, 1, 1, 1, JOYSTICK_X_MID, JOYSTICK_Y_MID };

void setupNRF24() {
  Serial.println("Starting the Radio");
  radio.begin();
  if (!radio.begin()){ 
    Serial.println(F("radio hardware not responding!")); 
    while (1) {} // hold program in infinite loop to prevent subsequent errors 
  }
  radio.openReadingPipe(1, address[0]);  // Open reading pipe from address pipe 1
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);  // Set RF power output to minimum: RF24_PA_MIN (change to RF24_PA_MAX if required)
  radio.setRetries(3, 5);         // delay, count
  radio.setChannel(110);
  delay(2000);
  radio.startListening();
  Serial.println("Radio started");
  Serial.println(radio.isChipConnected());
}

void loopNRF24() {
  readRadio();
  // setMotorsSpeed(joystickValues);
}

void readRadio() {
  if (radio.available()) {
    radio.read(&joystickValues, sizeof(joystickValues));
    delay(20);
  }
  setMotorsSpeed(joystickValues);
  if (DEBUG_RADIO) {
    for (int i = 0; i < 9; i++) {
      Serial.print(joystickValues[i]);
      if (i < 8) {
        Serial.print(", ");
      }
      if (i == 8) {
        Serial.println();
      }
    }
  }
}
