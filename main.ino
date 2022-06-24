#include "motor-controller.h"

const int RIGHT_MOTORS_PIN_1 = 3;
const int RIGHT_MOTORS_PIN_2 = 5;

const int LEFT_MOTORS_PIN_1 = 6;
const int LEFT_MOTORS_PIN_2 = 9;

const int IR_PIN = A4;
const int TRIGGER_PIN = 11;
const int ECHO_PIN = 10;

String command;
MotorController motorController = MotorController(
	RIGHT_MOTORS_PIN_1,
  	RIGHT_MOTORS_PIN_2,
  	LEFT_MOTORS_PIN_1,
  	LEFT_MOTORS_PIN_2
);

void getCommand() {
    // check if data is available
    if(Serial.available() > 0) {
        command = Serial.readString();
      	motorController.setPrintFlag();
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
