#include <AccelStepper.h>


const int HALFSTEP = 8;

const int motorPin5 = 4;     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
const int motorPin6 = 5;     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
const int motorPin7 = 6;    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
const int motorPin8 = 7;    // IN4 on ULN2003 ==> Orange on 28BYJ-48

const int motorPin1 = 8;     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
const int motorPin2 = 9;     // IN2 on ULN2004 ==> Pink   on 28BYJ-48
const int motorPin3 = 12;    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
const int motorPin4 = 13;    // IN4 on ULN2003 ==> Orange on 28BYJ-48

const int trigPin = 10;
const int echoPin = 11;

unsigned long previousMillis = 0;
const long interval = 5000;

bool moveNow = false;
bool buttonPress = false;

long duration;
int distance;

AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(1000);	
  stepper2.setMaxSpeed(1000);
  stepper2.setSpeed(1000);	
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    distanceLoc();
    previousMillis = currentMillis;
  }
  buttonForward();
  buttonBackward();
  if (moveNow == true) {
    stepper.runSpeed();
    stepper2.runSpeed();
  }
}

void buttonForward() {
  int sensorVal = digitalRead(2);
  //Serial.println(sensorVal);
  if (sensorVal == LOW) {
    stepper.setSpeed(1000);
    stepper2.setSpeed(1000);		
    buttonPress = !buttonPress;
    Serial.println(buttonPress);
    if (buttonPress = true) {
      forwardMove();
    }
    else {
      moveNow = false;
    }
  }
}

void buttonBackward() {
  int sensorVal2 = digitalRead(3);
  //Serial.println(sensorVal2);
  if (sensorVal2 == LOW) {
    stepper.setSpeed(-1000);
    stepper2.setSpeed(-1000);
    buttonPress = !buttonPress;
    Serial.println(buttonPress);
    if (buttonPress = true) {
      backwardMove();
    }
    else {
      moveNow = false;
    }
  }
}

void forwardMove() {
  moveNow = true;
}

void backwardMove() {
  moveNow = true;
}

void stopMove() {
  //stepper.stop();
  moveNow = false;
  buttonPress = false;
}

void distanceLoc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.println(distance);
  if (distance < 15) {
    stopMove();
  }
}