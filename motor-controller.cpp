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
            rightMotorsPin1 = LOW;
            rightMotorsPin2 = motorSpeed;
            leftMotorsPin1 = motorSpeed;
            leftMotorsPin2 = LOW;

            break;
        case MotorDirection::Right:
            rightMotorsPin1 = motorSpeed;
            rightMotorsPin2 = LOW;
            leftMotorsPin1 = LOW;
            leftMotorsPin2 = motorSpeed;

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
    isInAutoMode = false;
    controlMotor(MotorDirection::Forward);
    printStatus("Moving forward");
}

void MotorController::turnRight() {
    isInAutoMode = false;
    controlMotor(MotorDirection::Right);
    printStatus("Turning right");
}

void MotorController::turnLeft() {
    isInAutoMode = false;
    controlMotor(MotorDirection::Left);
    printStatus("Turning left");
}

void MotorController::goBakward() {
    isInAutoMode = false;
    controlMotor(MotorDirection::Backward);
    printStatus("Moving backward");
}

void MotorController::stop() {
    isInAutoMode = false;
    controlMotor(MotorDirection::Stop);
    printStatus("Stopped");
}

void MotorController::autoMode(double distance) {
    // turn right until there are no obstacles detected within 5 inches
    if(distance < 5) {
        controlMotor(MotorDirection::Right);

        // only print this message if the state is changing
        // from going forward to turning
        if(!isAutoTurning) {
            setPrintFlag();
            printStatus("obstacle detected, turning right...");
        }

        isAutoTurning = true;
        delay(250);
    } else {
        controlMotor(MotorDirection::Forward);

        // only print this message if the state is changing
        // from turning to going forward
        if(isAutoTurning) {
            setPrintFlag();
            printStatus("path is clear, moving forward");
        }
        
        isAutoTurning = false;
    }

    // only print this when auto mode is activated
    if(!isInAutoMode) {
        setPrintFlag();
        printStatus("Entered auto mode");
        isInAutoMode = true;
    }
    
}
