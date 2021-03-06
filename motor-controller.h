#ifndef SCOUTBOT_MOTOR_CONTROLLER_H
#define SCOUTBOT_MOTOR_CONTROLLER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class MotorController {
private:
    enum class MotorDirection {
        Forward,
        Backward,
        Left,
        Right,
        Stop
    };

    int RIGHT_MOTORS_PIN_1;
    int RIGHT_MOTORS_PIN_2;
    int LEFT_MOTORS_PIN_1;
    int LEFT_MOTORS_PIN_2;

    int motorSpeed = 128;
    bool needToPrintStatus = false;
    bool isInAutoMode = false;
    bool isAutoTurning = false;
    SoftwareSerial* bluetooth;

    void controlMotor(MotorDirection direction);
    void printStatus(String message);

public:
    MotorController(int rightMotorsPin1, int rightMotorsPin2, int leftMotorsPin1, int leftMotorsPin2);

    void setup(SoftwareSerial* bt);
    void setPrintFlag();
    void goForward();
    void turnRight();
    void turnLeft();
    void goBakward();
    void stop();
    void autoMode(double distance);
};

#endif
