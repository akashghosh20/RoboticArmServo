#include <Servo.h>

Servo servo1, servo2, servo3, servo4, servo5, servo6, gripperServo, finger1, finger2, finger3, finger4, finger5, finger6;

int potPin1 = A0, potPin2 = A1, potPin3 = A2, potPin4 = A3, potPin5 = A4, potPin6 = A5;
int gripperPin = 8;
int sonarTrigPin = 16;  // Adjust pin numbers based on your setup
int sonarEchoPin = 17;

void setup() {
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);

  finger1.attach(10);
  finger2.attach(11);
  finger3.attach(12);
  finger4.attach(13);
  finger5.attach(14);
  finger6.attach(15);

  gripperServo.attach(9);
  pinMode(gripperPin, OUTPUT);

  pinMode(sonarTrigPin, OUTPUT);
  pinMode(sonarEchoPin, INPUT);
}

void loop() {
  int angle1 = map(analogRead(potPin1), 0, 1023, 0, 180);
  int angle2 = map(analogRead(potPin2), 0, 1023, 0, 180);
  int angle3 = map(analogRead(potPin3), 0, 1023, 0, 180);
  int angle4 = map(analogRead(potPin4), 0, 1023, 0, 180);
  int angle5 = map(analogRead(potPin5), 0, 1023, 0, 180);
  int angle6 = map(analogRead(potPin6), 0, 1023, 0, 180);

  // Read object detection sensor
  if (isObjectDetected()) {
    // Close fingers and gripper to pick up the object
    closeFingers();
    delay(500);
    closeGripper();

    // Move the arm to another position
    moveToAnotherPosition();

    // Open fingers and gripper after moving
    openFingers();
    openGripper();
  }

  // Set servo angles based on sensor readings
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);
  servo5.write(angle5);
  servo6.write(angle6);

  // Add a delay to control the update rate (adjust as needed)
  delay(15);  // Adjust the delay based on the response time of your system
}

bool isObjectDetected() {
  // Trigger the sonar sensor
  digitalWrite(sonarTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonarTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonarTrigPin, LOW);

  // Read the echo duration
  long duration = pulseIn(sonarEchoPin, HIGH);

  // Calculate distance based on the speed of sound (343 meters/second)
  // and the fact that the sound travels back and forth
  float distance = duration * 0.0343 / 2;

  // Adjust the threshold based on your requirements
  return (distance < 20);  // Object detected within 20 cm
}

void moveToAnotherPosition() {
  // Simple example: Move the arm to a predefined position
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
  servo6.write(90);

  delay(1000);  // Adjust the delay based on your system's response time
}

void openGripper() {
  gripperServo.write(180);
}

void closeGripper() {
  gripperServo.write(0);
}

void openFingers() {
  finger1.write(90);
  finger2.write(90);
  finger3.write(90);
  finger4.write(90);
  finger5.write(90);
  finger6.write(90);
}

void closeFingers() {
  finger1.write(0);
  finger2.write(0);
  finger3.write(0);
  finger4.write(0);
  finger5.write(0);
  finger6.write(0);
}
