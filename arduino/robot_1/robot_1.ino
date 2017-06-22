// Adafruit motor shield setup
#include <AFMotor.h>

AF_DCMotor leftMotor(3);
AF_DCMotor rightMotor(1);

// time needed to rotate by approximately 90 degrees
#define ROTATION_TIME 1000

// variables to store the distances to the nearest obstacle
// (wall, robot etc)
int frontDistance;
int rearDistance;
int leftDistance;
int rightDistance;

// HC-SR04 Pin Connections
// The trigger from all the HC-SR04 sensors are connected
// to the same trigger pin
int trigPin = A1;
int frontDistancePin = A5;
int leftDistancePin = A4;
int rearDistancePin = A2;
int rightDistancePin = A3;

// called on initialisation and reset
void setup() {
  Serial.begin(9600);
  randomSeed(43);

  pinMode(trigPin, OUTPUT);
  pinMode(frontDistancePin, INPUT);
  pinMode(leftDistancePin, INPUT);
  pinMode(rearDistancePin, INPUT);
  pinMode(rightDistancePin, INPUT);

  leftMotor.setSpeed(200);
  rightMotor.setSpeed(200);

  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}

// main program containing logic
void loop() {

  // NOTE
  // The pulseIn of the HC-SR04 echo pin outputs 0 if no obstacle is detected

  // while there is no obstacle in the front
  while ((frontDistance = getDistance(frontDistancePin)) >= 40) {
    drive();

    // if there's any obstacle on the left, steer right
    leftDistance = getDistance(leftDistancePin);
    if (leftDistance <= 30 && leftDistance != 0) {
      steerRight();
      delay(30);
    }

    // if there's any obstacle on the right, steer left
    rightDistance = getDistance(rightDistancePin);
    if (rightDistance <= 30 && rightDistance != 0) {
      steerLeft();
      delay(30);
    }
  }

  stop();

  // there's an obstacle in the front
  // the robot has to turn left or right
  leftDistance = getDistance(leftDistancePin);
  rightDistance = getDistance(rightDistancePin);

  if (leftDistance > rightDistance) {
    rotateLeft(); // includes delay
  } else {
    rotateRight(); // includes delay
  }

  frontDistance = getDistance(frontDistancePin);

  // if there's still an obstacle in the front
  // and there's place to go reverse
  if (frontDistance < 40 && frontDistance != 0) {
    rearDistance = getDistance(rearDistancePin);

    while (rearDistance >= 50) {
      goReverse();
    }
  }

  delay(20);
}

// moves forward
void drive() {
  leftMotor.setSpeed(200);
  rightMotor.setSpeed(200);
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

// slightly turns right
void steerRight() {
  leftMotor.setSpeed(200);
  rightMotor.setSpeed(120);
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

// slightly turns left
void steerLeft() {
  leftMotor.setSpeed(120);
  rightMotor.setSpeed(200);
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

// turns left
void rotateLeft() {
  leftMotor.setSpeed(120);
  rightMotor.setSpeed(120);
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  delay(ROTATION_TIME);
}

// turns right
void rotateRight() {
  leftMotor.setSpeed(120);
  rightMotor.setSpeed(120);
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  delay(ROTATION_TIME);
}

// goes reverse
void goReverse() {
  leftMotor.setSpeed(200);
  rightMotor.setSpeed(200);
  leftMotor.run(BACKWARD);
  rightMotor.run(BACKWARD);
}

// emergency brake
void stop() {
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}

// get the distance from the HC-SR04
// pin -> echo pin for the particular HC-SR04
int getDistance(int pin) {
  long duration;
  int cms;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(pin, HIGH);

  cms = duration / 29 / 2;

  return cms;
}

