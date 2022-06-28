#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#include "motor-controller.h"

const int RIGHT_MOTORS_PIN_1 = 3;
const int RIGHT_MOTORS_PIN_2 = 5;

const int LEFT_MOTORS_PIN_1 = 6;
const int LEFT_MOTORS_PIN_2 = 9;

const int TRIGGER_PIN = 7;
const int ECHO_PIN = 8;

const int bluetoothRx = 10;
const int bluetoothTx = 11;

unsigned long time;
double distance;
double objectTemp;
double ambientTemp;

SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);

Adafruit_MLX90614 mlx;

String command;
MotorController motorController = MotorController(
    RIGHT_MOTORS_PIN_1,
    RIGHT_MOTORS_PIN_2,
    LEFT_MOTORS_PIN_1,
    LEFT_MOTORS_PIN_2
);

void getCommand() {
    // check if data is available
    if(bluetooth.available() > 0) {
        command = bluetooth.readString();
        command.trim();
        command.toLowerCase();
        motorController.setPrintFlag();
    }
}

void parseCommand() {
    if(command == "go" || command == "forward") {
        if(distance > 5) {
            motorController.goForward();
        } else {
            bluetooth.println("[ScoutBot] object less than 5 inches in front, stopping...");
            motorController.setPrintFlag();
            motorController.stop();
            command = "";
        }
    } else if(command == "back" || command == "reverse") {
        motorController.goBakward();
    } else if(command == "stop" || command == "halt") {
        motorController.stop();
    } else if(command == "left") {
        motorController.turnLeft();
    } else if(command == "right") {
        motorController.turnRight();
    } else if(command == "scan") {
        scan();
        command = "";
    } else if(command == "auto" || command == "roam") {
        motorController.autoMode(distance);
    } else {
        if(command != "") {
            bluetooth.println("[ScoutBot] unknown command: " + command);
            command = "";
        }
    }
}

double getDistance() {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(15);
    digitalWrite(TRIGGER_PIN, LOW);
    
    time = pulseIn(ECHO_PIN, HIGH);
    // distance in inches
    return time / 148.1;
}

void scan() {
    objectTemp = mlx.readObjectTempF();
    ambientTemp = mlx.readAmbientTempF();

    bluetooth.println("[ScoutBot] ambient temperature is " + (String)ambientTemp + "F");
    bluetooth.println("[ScoutBot] object is " + (String)distance + " inches in front");

    if(objectTemp > 90 && objectTemp < 100) {
        bluetooth.println("[ScoutBot] object is " + (String)objectTemp + "F");
        bluetooth.println("[ScoutBot] object is possibly human");
    }
}

void printCommands() {
    bluetooth.println("\n[ScoutBot] Commands:");
    bluetooth.println("go | forward: move forward");
    bluetooth.println("back | reverse: move backward");
    bluetooth.println("stop | halt: stop all motion");
    bluetooth.println("left: turn left");
    bluetooth.println("right: turn right");
    bluetooth.println("scan: scan for objects in front of ScoutBot");
    bluetooth.println("auto | roam: ScoutBot will enter free roam mode\n");
}

void setup() {
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
  
    motorController.setup(&bluetooth);
    
    Serial.begin(9600);
    bluetooth.begin(9600);
    mlx.begin();

    printCommands();
    bluetooth.println("[ScoutBot] System initialized. Waiting for command...");
}

void loop() {
    getCommand();
    parseCommand();

    distance = getDistance();
}
