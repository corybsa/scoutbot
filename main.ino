#include "motor-controller.h"

const int FRONT_RIGHT_MOTOR_PIN_1 = A2;
const int FRONT_RIGHT_MOTOR_PIN_2 = A3;

const int REAR_RIGHT_MOTOR_PIN_1 = A0;
const int REAR_RIGHT_MOTOR_PIN_2 = A1;

const int FRONT_LEFT_MOTOR_PIN_1 = 6;
const int FRONT_LEFT_MOTOR_PIN_2 = 9;

const int REAR_LEFT_MOTOR_PIN_1 = 3;
const int REAR_LEFT_MOTOR_PIN_2 = 5;

const int IR_PIN = A4;
const int TRIGGER_PIN = 11;
const int ECHO_PIN = 10;

String command;
MotorController motorController = MotorController(
	FRONT_RIGHT_MOTOR_PIN_1,
  	FRONT_RIGHT_MOTOR_PIN_2,
    REAR_RIGHT_MOTOR_PIN_1,
  	REAR_RIGHT_MOTOR_PIN_2,
    FRONT_LEFT_MOTOR_PIN_1,
    FRONT_LEFT_MOTOR_PIN_2,
    REAR_LEFT_MOTOR_PIN_1,
    REAR_LEFT_MOTOR_PIN_2
);

void getCommand() {
    // check if data is available
    if(Serial.available() > 0) {
        command = Serial.readString();
    }
}

void parseCommand() {
    if(command == "go" || command == "forward") {
        motorController.goForward();
    } else if(command == "right") {
        motorController.turnRight();
    } else if(command == "left") {
        motorController.turnLeft();
    } else if(command == "back" || command == "reverse") {
        motorController.goBakward();
    } else if(command == "stop" || command == "halt") {
        motorController.stop();
    } else {
        if(command != "") {
            Serial.println("unknown command");
            command = "";
        }
    }
}

void setup() {
  	pinMode(TRIGGER_PIN, OUTPUT);
  	pinMode(ECHO_PIN, INPUT);
  
    motorController.setup();
    
    Serial.begin(9600);
}

void loop() {
    getCommand();
    parseCommand();
}
