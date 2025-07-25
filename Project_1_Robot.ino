/*
 # DemoRobot_V1
 * This is about a demonstrable DIY robot application project
 * All rights reserved under the R&D team Anka Robotics by Anka Technologies
 * Developers: Damithrafdo, Shanuka, Kalaynilavan, Medhavi
 * Under the supervision of Dr. Tharindu
 * 
 * Development Board: Arduino Uno
 * Functions: Obstacle avoiding, line following...
 * Sensors: Ultrasonic sensor array, IR line follower array
 * Motors: 2 DC motors with motor driver
 * 
 * Project Name: DemoRobot_V1
 * Version: 1.0 
 * Date: 2025-06-16
 * Description:
 * This code is for a simple robot that can follow a line using an IR sensor array and avoid obstacles using an ultrasonic sensor array.
 * The robot can move forward, backward, turn left, and turn right based on the readings from the IR sensors.
 * The robot is controlled using an Arduino Uno board, which receives input from the sensors and sends signals to the motors.
 * The robot can be programmed to follow a line, avoid obstacles, and perform other tasks based on the sensor readings.
 * This code is a basic implementation of a line-following robot with obstacle avoidance capabilities.
 * 
 * Diagram        
 *          __________________________
 *         |                          |
 *         | Ultrasonic Sensor Array  |
 *         |__________________________|             _____________
 *                       |                         |             |
 *                       |-------------------------| Servo motor |
 *          __________________________    |        |_____________|
 *         |  (ir0,ir1,ir2,ir3,ir4)   |   |        
 *         |  Line Follower IR Array  |   |
 *         |__________________________|   |
 *                       |                |
 *                       |-----------------
 *                 ______|______
 *                |             |
 *                | Arduino Uno |
 *                |_____________|
 *                       |
 *  __________     ______|______     ___________
 * |   (lm)   |   |             |   |   (rm)    |  
 * |Left Motor|---| MotorDriver |---|Right Motor| 
 * |__________|   |_____________|   |___________|
 *            
 *            
 * This code includes           
 *            
 */

//Add Libries here - #include<libry.h>
#include <NewPing.h> 
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



//Add difines here - #define app A0
// Ultrasonic sensor pins
#define TRIG_PIN A1      // Main ultrasonic sensor
#define ECHO_PIN A2
#define TRIG_DOWN A0     // Downward ultrasonic sensor
#define ECHO_DOWN A3
#define MAX_DISTANCE 200 

// Servo pin
#define SERVO_PIN 13

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Button
#define BUTTON_PIN 7

// IR
#define LEFT_SENSOR_PIN   2
#define CENTER_SENSOR_PIN 3
#define RIGHT_SENSOR_PIN  4

//Put variables here - int Val

const int rmb=12, rmf=11, lmb=10, lmf=9, rme= 5, lme=6; //motor signals, left/right motor back/forward
int THRESHOLD_DISTANCE = 30;// the distance (in cm) for obstacle detection
int modeCount = 0; // Variable to track the mode
bool lastState = HIGH;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing downSonar(TRIG_DOWN, ECHO_DOWN, MAX_DISTANCE);
Servo myservo;
int distance = 100;
int downDistance = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(rmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(rme, OUTPUT);
  pinMode(lme, OUTPUT);
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(CENTER_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  // Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_DOWN, OUTPUT);
  pinMode(ECHO_DOWN, INPUT);
  // Servo setup
  myservo.attach(SERVO_PIN);
  myservo.write(90);  // Center
  delay(1000);

  randomSeed(analogRead(0));
  showOnOLED("Robot Starting...");
  delay(2000);
  display.clearDisplay();
  showOnOLED("Select Mode");
  delay(3000);
  showOnOLED("Default Mode: A");
  delay(2000);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  // pushbutton setup
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  bool currentState = digitalRead(BUTTON_PIN);

  if (lastState == LOW && currentState == HIGH) {
    modeCount = (modeCount + 1) % 4; // Cycle through 0, 1, 2
    Serial.print("Mode changed to: ");
    Serial.println(modeCount);
  }

  lastState = currentState;

  switch (modeCount) {
    case 0:
      ModeA();
      Serial.println("A");
      break;
    case 1:
      ModeB();
      Serial.println("B");
      break;
    case 2:
      ModeC();
      Serial.println("C");
      break;
    case 3:
      ModeD();  
      Serial.println("D");
      break;
    default:
      break;
  }
}


//Add functions here - 
/*func(_){
 *  if(_){
 *  }
 *  else{
 *  }
 *  retern;
 * }
 */
// Display function for OLED 
void showOnOLED(const char* msg) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(msg);
  display.display();
}
// Reads front distance
int readDistance() {
  delay(50);
  int cm = sonar.ping_cm();
  if (cm == 0) cm = 250;
  return cm;
}

// Reads downward distance
int readDownDistance() {
  delay(50);
  int cm = downSonar.ping_cm();
  if (cm == 0) cm = 250;
  return cm;
}

// Analyze path using servo + main ultrasonic
void analyzeFreePath() {
  myservo.write(0);
  int distanceRight = lookRight();
  delay(500);
  int distanceLeft = lookLeft();
  delay(500);

  if (distanceRight >= distanceLeft) {
    turnRight();
  } else {
    turnLeft();
  }
  myservo.write(0);
}

int lookRight() {
  myservo.write(90);        
  delay(200);

  myservo.write(0);        
  delay(200);

  int d = readDistance();   
  delay(100);

  myservo.write(90);        
  delay(200);

  return d;
}


int lookLeft() {
  myservo.write(90);        
  delay(200);

  myservo.write(180);       
  delay(200);

  int d = readDistance();   
  delay(100);

  myservo.write(90);        
  delay(200);

  return d;
}


//-- Mode functions for different behaviors

// Mode A: Sample testing-----------------------------------------------------------------------------------
// This mode is for testing the robot's movements and functionality
void ModeA(){
  //Sample testing
  showOnOLED("Mode A");
  delay(3000);
  // Show initial message
  display.clearDisplay();
  showOnOLED("Testing start");
  delay(1000);
  // Test movements
  moveForward();
  showOnOLED("Forward");
  delay(1000); 
  stopMotors();
  delay(500);
  moveBackward();
  showOnOLED("Backward");
  delay(1500);
  stopMotors();
  delay(1000);
  turnLeft();
  showOnOLED("Left"); 
  delay(1500);
  stopMotors();
  delay(1000);
  turnRight();
  showOnOLED("Right");
  delay(1500);
  stopMotors();
  delay(1000);
  stopMotors();
  showOnOLED("Stopped");
  delay(5000);
}

// Mode B: Obstacle avoidance-------------------------------------------------------------------------------
// This mode is for obstacle avoidance using a single ultrasonic sensor
// The robot will move forward if no obstacles are detected, otherwise it will back up and turn
void ModeB() {
  // Obstacle avoidance
  showOnOLED("Mode B");
  delay(3000);
  // Read distance from the ultrasonic sensor
  float distance = readDistance();
  if (distance < THRESHOLD_DISTANCE) {
    stopMotors();
    delay(500);       
    moveBackward();   
    delay(100);
    bool turn_Right = random(0, 2);  
    if (turn_Right) {
      turnRight();
    } else {
      turnLeft();
    }               
    delay(400);
  } else {
    moveForward(); 
  }
}

 // Mode C: Obstacle avoidance with two sensors---------------------------------------------------------------
// This mode is for obstacle avoidance using two ultrasonic sensors
// The robot will move forward if no obstacles are detected, otherwise it will back up and turn
void ModeC(){
  //Obstacle avoidance with two sensors
  showOnOLED("Mode C");
  delay(3000);
  float distance1 = readDownDistance();
  float distance = readDistance();
  if (distance < THRESHOLD_DISTANCE || distance1 < THRESHOLD_DISTANCE ) {
    stopMotors();
    delay(500);       
    moveBackward();   
    delay(100);
    bool turn_Right = random(0, 2);  
    if (turn_Right) {
      turnRight();
    } else {
      turnLeft();
    }               
    delay(400);
  } else {
    moveForward(); 
  }
}
 
// Mode D: Line following-----------------------------------------------------------------------------------
// This mode is for line following using IR sensors
// The robot will follow a line based on the readings from the IR sensors
void ModeD(){
  //Line following
  showOnOLED("Mode D");
  delay(3000);
  int leftSensor = digitalRead(LEFT_SENSOR_PIN);
  int centerSensor = digitalRead(CENTER_SENSOR_PIN);
  int rightSensor = digitalRead(RIGHT_SENSOR_PIN);

  if (leftSensor == HIGH && centerSensor == LOW && rightSensor == HIGH) {
        // On line, go forward
        moveForward();
  } else if (leftSensor == LOW && centerSensor == LOW && rightSensor == HIGH) {
        // Line detected on left, turn left
        turnLeft();
  } else if (leftSensor == LOW && centerSensor == HIGH && rightSensor == HIGH) {
        // Line detected on left, turn left
        turnLeft();
  } else if (leftSensor == HIGH && centerSensor == LOW && rightSensor == LOW) {
        // Line detected on right, turn right
        turnRight();
  } else if (leftSensor == HIGH && centerSensor == HIGH && rightSensor == LOW) {
        // Line detected on right, turn right
        turnRight();
  } else if (leftSensor == LOW && centerSensor == LOW && rightSensor == LOW) {
        // Line detected on right, turn right
        turnLeft();
        delay(400);
  } else {
        // No line detected, stop
        stopMotors();
  }
}

// Function to move the robot forward, backward, turn left, turn right, and stop motors
// These functions control the motors based on the robot's movement requirements
void moveForward() {
    digitalWrite(lmf, HIGH);
    digitalWrite(lmb, LOW);
    digitalWrite(rmf, HIGH);
    digitalWrite(rmb, LOW);
}

void moveBackward() {
    digitalWrite(lmf, LOW);
    digitalWrite(lmb, HIGH);
    digitalWrite(rmf, LOW);
    digitalWrite(rmb, HIGH);
}

void turnLeft() {
    digitalWrite(lmf, LOW);
    digitalWrite(lmb, HIGH);
    digitalWrite(rmf, HIGH);
    digitalWrite(rmb, LOW);
}

void turnRight() {
    digitalWrite(lmf, HIGH);
    digitalWrite(lmb, LOW);
    digitalWrite(rmf, LOW);
    digitalWrite(rmb, HIGH);
}

void stopMotors() {
    digitalWrite(lmf, LOW);
    digitalWrite(lmb, LOW);
    digitalWrite(rmf, LOW);
    digitalWrite(rmb, LOW);
}

