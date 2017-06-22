// L293D Motor Control Pins
// these pins can be given PWM signals to control rotation speed
const int lf = 2;
const int rf = 3;
const int lb = 4;
const int rb = 5;

// time needed to rotate by approximately 90 degrees
#define ROTATION_TIME 50

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
int frontDistancePin = A2;
int leftDistancePin = A4;
int rearDistancePin = A5;
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

  pinMode(lf, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(rf, OUTPUT);
  pinMode(rb, OUTPUT);
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
      delay(10);
    }

    // if there's any obstacle on the right, steer left
    rightDistance = getDistance(rightDistancePin);
    if (rightDistance <= 30 && rightDistance != 0) {
      steerLeft();
      delay(10);
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
  analogWrite(lf, 200);
  analogWrite(lb, 0);
  analogWrite(rf, 200);
  analogWrite(rb, 0);
}

// slightly turns right
void steerRight() {
  analogWrite(lf, 200);
  analogWrite(lb, 0);
  analogWrite(rf, 120);
  analogWrite(rb, 0);
}

// slightly turns left
void steerLeft() {
  analogWrite(lf, 120);
  analogWrite(lb, 0);
  analogWrite(rf, 200);
  analogWrite(rb, 0);
}

// turns left
void rotateLeft() {
  analogWrite(lf, 0);
  analogWrite(lb, 200);
  analogWrite(rf, 200);
  analogWrite(rb, 0);
  delay(ROTATION_TIME);
}

// turns right
void rotateRight() {
  analogWrite(lf, 200);
  analogWrite(lb, 0);
  analogWrite(rf, 0);
  analogWrite(rb, 200);
  delay(ROTATION_TIME);
}

// goes reverse
void goReverse() {
  analogWrite(lf, 0);
  analogWrite(lb, 200);
  analogWrite(rf, 0);
  analogWrite(rb, 200);
}

// emergency brake
void stop() {
  analogWrite(lf, 0);
  analogWrite(lb, 0);
  analogWrite(rf, 0);
  analogWrite(rb, 0);
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

