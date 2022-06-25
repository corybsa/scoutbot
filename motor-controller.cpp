#include "motor-controller.h"

MotorController::MotorController(int rightMotorsPin1, int rightMotorsPin2, int leftMotorsPin1, int leftMotorsPin2) {
    RIGHT_MOTORS_PIN_1 = rightMotorsPin1;
    RIGHT_MOTORS_PIN_2 = rightMotorsPin2;
    LEFT_MOTORS_PIN_1 = leftMotorsPin1;
    LEFT_MOTORS_PIN_2 = leftMotorsPin2;
}

void MotorController::setup(SoftwareSerial* bt) {
    pinMode(RIGHT_MOTORS_PIN_1, OUTPUT);
    pinMode(RIGHT_MOTORS_PIN_2, OUTPUT);
    pinMode(LEFT_MOTORS_PIN_1, OUTPUT);
    pinMode(LEFT_MOTORS_PIN_2, OUTPUT);

    bluetooth = bt;
}

void MotorController::printStatus(String message) {
    if(needToPrintStatus) {
      	needToPrintStatus = false;
        bluetooth->println("[ScoutBot] " + message);
    }
}

void MotorController::setPrintFlag() {
    needToPrintStatus = true;
}

void MotorController::controlMotor(MotorDirection direction) {
    int rightMotorsPin1 = LOW;
    int rightMotorsPin2 = LOW;
    int leftMotorsPin1 = LOW;
    int leftMotorsPin2 = LOW;
    
    switch(direction) {
        case MotorDirection::Forward:
            rightMotorsPin1 = motorSpeed;
            rightMotorsPin2 = LOW;
            leftMotorsPin1 = motorSpeed;
            leftMotorsPin2 = LOW;

            break;
        case MotorDirection::Backward:
            rightMotorsPin1 = LOW;
            rightMotorsPin2 = motorSpeed;
            leftMotorsPin1 = LOW;
            leftMotorsPin2 = motorSpeed;

            break;
        case MotorDirection::Left:
            rightMotorsPin1 = motorSpeed;
            rightMotorsPin2 = LOW;
            leftMotorsPin1 = LOW;
            leftMotorsPin2 = motorSpeed;

            break;
        case MotorDirection::Right:
            rightMotorsPin1 = LOW;
            rightMotorsPin2 = motorSpeed;
            leftMotorsPin1 = motorSpeed;
            leftMotorsPin2 = LOW;

            break;
        case MotorDirection::Stop:
        default:
            rightMotorsPin1 = LOW;
            rightMotorsPin2 = LOW;
            leftMotorsPin1 = LOW;
            leftMotorsPin2 = LOW;
            break;
    }

    analogWrite(RIGHT_MOTORS_PIN_1, rightMotorsPin1);
    analogWrite(RIGHT_MOTORS_PIN_2, rightMotorsPin2);
    
    analogWrite(LEFT_MOTORS_PIN_1, leftMotorsPin1);
    analogWrite(LEFT_MOTORS_PIN_2, leftMotorsPin2);
}

void MotorController::goForward() {
    controlMotor(MotorDirection::Forward);
  	printStatus("Moving forward");
}

void MotorController::turnRight() {
    controlMotor(MotorDirection::Right);
  	printStatus("Turning right");
}

void MotorController::turnLeft() {
    controlMotor(MotorDirection::Left);
  	printStatus("Turning left");
}

void MotorController::goBakward() {
    controlMotor(MotorDirection::Backward);
  	printStatus("Moving backward");
}

void MotorController::stop() {
    controlMotor(MotorDirection::Stop);
  	printStatus("Stopped");
}
