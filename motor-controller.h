#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

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

    int motorSpeed = 16;
  	bool needToPrintStatus = false;

    void controlMotor(MotorDirection direction);
  	void printStatus(String message);

public:
    MotorController(int rightMotorsPin1, int rightMotorsPin2, int leftMotorsPin1, int leftMotorsPin2);

    void setup();
    void goForward();
    void turnRight();
    void turnLeft();
    void goBakward();
    void stop();
  	void setPrintFlag();
};

#endif