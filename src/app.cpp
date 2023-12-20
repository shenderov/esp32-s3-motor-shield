#include <Arduino.h>
#include <nrf24.h>
#include <motion-control.h>
#include <motor-control.h>
#include <esp32-s3-motor-shield-1.0-pin-mapping.h>

void setup() {
  Serial.begin(115200);
  setupNRF24();
  setupMotorControl();
  Serial.println("Initialized");

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
}

void loop() {
  loopNRF24();
  delay(20);
  // digitalWrite(LED_1, HIGH);
  // digitalWrite(LED_2, LOW);
  // delay(50);
  // digitalWrite(LED_1, LOW);
  // digitalWrite(LED_2, HIGH);
  // delay(50);
}
