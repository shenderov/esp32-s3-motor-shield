#include <Arduino.h>
#include "nrf24.h"
#include "motion-control.h"
#include "motor-control.h"

int16_t speedLeft = 0;
int16_t speedRight = 0;
bool isReverseLeft, isReverseRight;

void loopMotionControl() {
    // loopNRF24();
}

void setMotorsSpeed(int16_t *joystickValues) {
  if (joystickValues[8] > JOYSTICK_Y_MID + 10) {
    speedLeft = map(joystickValues[8], JOYSTICK_Y_MID + 1, 1023, 0, 255);
    speedRight = map(joystickValues[8], JOYSTICK_Y_MID + 1, 1023, 0, 255);
    isReverseLeft = false;
    isReverseRight = false;
    //checkDistance();
  } else if (joystickValues[8] < JOYSTICK_Y_MID - 10) {
    speedLeft = map(joystickValues[8], JOYSTICK_Y_MID - 10, 0, 0, 255);
    speedRight = map(joystickValues[8], JOYSTICK_Y_MID - 10, 0, 0, 255);
    isReverseLeft = true;
    isReverseRight = true;
  } else {
    speedLeft = 0;
    speedRight = 0;
    isReverseLeft = false;
    isReverseRight = false;
  }
  if (joystickValues[7] < JOYSTICK_X_MID - 10 && speedRight > 0) {  //left turn
    int16_t left = map(joystickValues[7], JOYSTICK_X_MID - 10, 0, 0, 150);
    if (speedRight >= left) {
      speedRight = speedRight - left;
    } else {
      speedRight = 0;
    }
  } else if (joystickValues[7] > JOYSTICK_X_MID + 10 && speedLeft > 0) {  //right turn
    int16_t right = map(joystickValues[7], JOYSTICK_X_MID + 10, 1023, 0, 150);
    if (speedLeft >= right) {
      speedLeft = speedLeft - right;
    } else {
      speedLeft = 0;
    }
  } else if (joystickValues[8] < JOYSTICK_Y_MID + 10 && joystickValues[8] > JOYSTICK_Y_MID - 10 && joystickValues[7] < JOYSTICK_X_MID - 10) {  //turn left on the spot
    int16_t left = map(joystickValues[7], JOYSTICK_X_MID - 10, 0, 0, 100);
    speedLeft = left;
    speedRight = left;
    isReverseRight = true;
  } else if (joystickValues[8] < JOYSTICK_Y_MID + 10 && joystickValues[8] > JOYSTICK_Y_MID - 10 && joystickValues[7] > JOYSTICK_X_MID + 10) {  //turn right on the spot
    int16_t right = map(joystickValues[7], JOYSTICK_X_MID + 10, 1023, 0, 100);
    speedLeft = right;
    speedRight = right;
    isReverseLeft = true;
  }
  updateMotorSpeedLeft(isReverseLeft, speedLeft);
  updateMotorSpeedRight(isReverseRight, speedRight);
}
