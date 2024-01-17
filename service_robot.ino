#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

AF_DCMotor motor1(1);  // Motor 1 is connected to M1 on the motor driver
AF_DCMotor motor2(2);  // Motor 2 is connected to M2 on the motor driver
Servo myservo;         // Servo motor

SoftwareSerial bluetooth(10, 11); // RX, TX pins for Bluetooth module

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  myservo.attach(9); // Attach the servo to pin 9
}

void loop() {
  if (bluetooth.available() > 0) {
    char command = bluetooth.read();

    switch(command) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopMoving();
        break;
      case 'T':
        turnServo();
        break;
      default:
        break;
    }
  }
}

void moveForward() {
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void moveBackward() {
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

void turnLeft() {
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

void turnRight() {
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void stopMoving() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void turnServo() {
  myservo.write(90); // Rotate servo to 90 degrees
  delay(1000);       // Wait for the servo to reach the desired position
  myservo.write(0);  // Reset the servo position
}
