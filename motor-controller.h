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

    int REAR_RIGHT_MOTOR_PIN_1;
    int REAR_RIGHT_MOTOR_PIN_2;

    int FRONT_RIGHT_MOTOR_PIN_1;
    int FRONT_RIGHT_MOTOR_PIN_2;

    int REAR_LEFT_MOTOR_PIN_1;
    int REAR_LEFT_MOTOR_PIN_2;

    int FRONT_LEFT_MOTOR_PIN_1;
    int FRONT_LEFT_MOTOR_PIN_2;

    int motorSpeed = 128;

    void controlMotor(MotorDirection direction);

public:
    MotorController(
        int frontRight1, int frontRight2,
        int rearRight1, int rearRight2,
        int frontLeft1, int frontLeft2,
        int rearLeft1, int rearLeft2
    );

    void setup();
    void goForward();
    void turnRight();
    void turnLeft();
    void goBakward();
    void stop();
};

#endif