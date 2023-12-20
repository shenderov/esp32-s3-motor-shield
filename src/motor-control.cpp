#include <Arduino.h>
#include <esp32-s3-motor-shield-1.0-pin-mapping.h>
#include <motor-control.h>

#define DEBUG_MOTOR false

void motorControl(int16_t pin1, int16_t pin2, int16_t en, bool isReverse, int16_t speed);
void motorControlDebug(char motorSide, bool isReverse, int16_t speed);

void setupMotorControl() {
  pinMode(MOTOR_CTRL_LEFT_ENA, OUTPUT);
  pinMode(MOTOR_CTRL_LEFT_ENB, OUTPUT);
  pinMode(MOTOR_CTRL_RIGHT_ENA, OUTPUT);
  pinMode(MOTOR_CTRL_RIGHT_ENB, OUTPUT);
  pinMode(MOTOR_CTRL_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_CTRL_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_CTRL_LEFT_IN3, OUTPUT);
  pinMode(MOTOR_CTRL_LEFT_IN4, OUTPUT);  
  pinMode(MOTOR_CTRL_RIGHT_IN1, OUTPUT);
  pinMode(MOTOR_CTRL_RIGHT_IN2, OUTPUT);
  pinMode(MOTOR_CTRL_RIGHT_IN3, OUTPUT);
  pinMode(MOTOR_CTRL_RIGHT_IN4, OUTPUT);
}

void motorControlLoop() {
    updateMotorSpeedLeft(false, 100);
    updateMotorSpeedRight(false, 100);
    delay(2000);
    updateMotorSpeedLeft(false, 255);
    updateMotorSpeedRight(false, 255);
    delay(2000);
    updateMotorSpeedLeft(false, 0);
    updateMotorSpeedRight(false, 0);
    delay(2000);
    updateMotorSpeedLeft(true, 100);
    updateMotorSpeedRight(true, 100);
    delay(2000);
    updateMotorSpeedLeft(true, 255);
    updateMotorSpeedRight(true, 255);
    delay(2000);
    updateMotorSpeedLeft(false, 0);
    updateMotorSpeedRight(false, 0);
    delay(2000);
    updateMotorSpeedLeft(true, 100);
    updateMotorSpeedRight(false, 100);
    delay(2000);
    updateMotorSpeedLeft(false, 100);
    updateMotorSpeedRight(true, 100);
    delay(2000);
    updateMotorSpeedLeft(false, 0);
    updateMotorSpeedRight(false, 0);
    delay(2000);
}

void updateMotorSpeedLeft(bool isReverse, int16_t speed){
  motorControl(MOTOR_CTRL_LEFT_IN1, MOTOR_CTRL_LEFT_IN2, MOTOR_CTRL_LEFT_ENA, !isReverse, speed);
  motorControl(MOTOR_CTRL_LEFT_IN3, MOTOR_CTRL_LEFT_IN4, MOTOR_CTRL_LEFT_ENB, !isReverse, speed);
  if (DEBUG_MOTOR) {
    motorControlDebug('L', !isReverse, speed);
  }
}

void updateMotorSpeedRight(bool isReverse, int16_t speed){
  motorControl(MOTOR_CTRL_RIGHT_IN1, MOTOR_CTRL_RIGHT_IN2, MOTOR_CTRL_RIGHT_ENA, !isReverse, speed);
  motorControl(MOTOR_CTRL_RIGHT_IN3, MOTOR_CTRL_RIGHT_IN4, MOTOR_CTRL_RIGHT_ENB, !isReverse, speed);
  if (DEBUG_MOTOR) {
    motorControlDebug('R', !isReverse, speed);
  }
}

void motorControl(int16_t pin1, int16_t pin2, int16_t en, bool isReverse, int16_t speed) {
  if (speed == 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    return;
  } else if (!isReverse) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  } else if (isReverse) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    
  }
  analogWrite(en, speed);
}

void motorControlDebug(char motorSide, bool isReverse, int16_t speed) {
  Serial.print("Motor ");
  Serial.print(motorSide);
  Serial.print(" speed: ");
  Serial.print(speed);
  Serial.print(", direction: ");
  if (speed == 0) {
    Serial.println("STOP");
    return;
  } else if (!isReverse) {
    Serial.println("FORWARD");
  } else if (isReverse) {
    Serial.println("REVERSE");
  }
  delay(100);
}