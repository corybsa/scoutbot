#include "motor-controller.h"

MotorController::MotorController(
        int frontRight1, int frontRight2,
        int rearRight1, int rearRight2,
        int frontLeft1, int frontLeft2,
        int rearLeft1, int rearLeft2
) {
    FRONT_RIGHT_MOTOR_PIN_1 = frontRight1;
    FRONT_RIGHT_MOTOR_PIN_2 = frontRight2;

    REAR_RIGHT_MOTOR_PIN_1 = rearRight1;
    REAR_RIGHT_MOTOR_PIN_2 = rearRight2;

    FRONT_LEFT_MOTOR_PIN_1 = frontLeft1;
    FRONT_LEFT_MOTOR_PIN_2 = frontLeft2;

    REAR_LEFT_MOTOR_PIN_1 = rearLeft1;
    REAR_LEFT_MOTOR_PIN_2 = rearLeft2;
}

void MotorController::setup() {
    pinMode(REAR_RIGHT_MOTOR_PIN_1, OUTPUT);
    pinMode(REAR_RIGHT_MOTOR_PIN_2, OUTPUT);

    pinMode(FRONT_RIGHT_MOTOR_PIN_1, OUTPUT);
    pinMode(FRONT_RIGHT_MOTOR_PIN_2, OUTPUT);

    pinMode(REAR_LEFT_MOTOR_PIN_1, OUTPUT);
    pinMode(REAR_LEFT_MOTOR_PIN_2, OUTPUT);

    pinMode(FRONT_LEFT_MOTOR_PIN_1, OUTPUT);
    pinMode(FRONT_LEFT_MOTOR_PIN_2, OUTPUT);
}

void MotorController::controlMotor(MotorDirection direction) {
    int frontRightPin1 = LOW;
    int frontRightPin2 = LOW;

    int frontLeftPin1 = LOW;
    int frontLeftPin2 = LOW;

    int rearRightPin1 = LOW;
    int rearRightPin2 = LOW;

    int rearLeftPin1 = LOW;
    int rearLeftPin2 = LOW;
    
    switch(direction) {
        case MotorDirection::Forward:
            frontRightPin1 = motorSpeed;
            frontRightPin2 = LOW;

            frontLeftPin1 = motorSpeed;
            frontLeftPin2 = LOW;

            rearRightPin1 = motorSpeed;
            rearRightPin2 = LOW;

            rearLeftPin1 = motorSpeed;
            rearLeftPin2 = LOW;

            break;
        case MotorDirection::Backward:
            frontRightPin1 = LOW;
            frontRightPin2 = motorSpeed;

            frontLeftPin1 = LOW;
            frontLeftPin2 = motorSpeed;

            rearRightPin1 = LOW;
            rearRightPin2 = motorSpeed;

            rearLeftPin1 = LOW;
            rearLeftPin2 = motorSpeed;
            break;
        case MotorDirection::Left:
            frontRightPin1 = motorSpeed;
            frontRightPin2 = LOW;

            frontLeftPin1 = LOW;
            frontLeftPin2 = motorSpeed;

            rearRightPin1 = motorSpeed;
            rearRightPin2 = LOW;

            rearLeftPin1 = LOW;
            rearLeftPin2 = motorSpeed;

            break;
        case MotorDirection::Right:
            frontRightPin1 = LOW;
            frontRightPin2 = motorSpeed;

            frontLeftPin1 = motorSpeed;
            frontLeftPin2 = LOW;

            rearRightPin1 = LOW;
            rearRightPin2 = motorSpeed;

            rearLeftPin1 = motorSpeed;
            rearLeftPin2 = LOW;

            break;
        case MotorDirection::Stop:
        default:
            frontRightPin1 = LOW;
            frontRightPin2 = LOW;

            frontLeftPin1 = LOW;
            frontLeftPin2 = LOW;

            rearRightPin1 = LOW;
            rearRightPin2 = LOW;

            rearLeftPin1 = LOW;
            rearLeftPin2 = LOW;
            break;
    }

    analogWrite(FRONT_RIGHT_MOTOR_PIN_1, frontRightPin1);
    analogWrite(FRONT_RIGHT_MOTOR_PIN_2, frontRightPin2);
    
    analogWrite(FRONT_LEFT_MOTOR_PIN_1, frontLeftPin1);
    analogWrite(FRONT_LEFT_MOTOR_PIN_2, frontLeftPin2);
    
    analogWrite(REAR_RIGHT_MOTOR_PIN_1, rearRightPin1);
    analogWrite(REAR_RIGHT_MOTOR_PIN_2, rearRightPin2);
    
    analogWrite(REAR_LEFT_MOTOR_PIN_1, rearLeftPin1);
    analogWrite(REAR_LEFT_MOTOR_PIN_2, rearLeftPin2);
}

void MotorController::goForward() {
    controlMotor(MotorDirection::Forward);
}

void MotorController::turnRight() {
    controlMotor(MotorDirection::Right);
}

void MotorController::turnLeft() {
    controlMotor(MotorDirection::Left);
}

void MotorController::goBakward() {
    controlMotor(MotorDirection::Backward);
}

void MotorController::stop() {
    controlMotor(MotorDirection::Stop);
}
