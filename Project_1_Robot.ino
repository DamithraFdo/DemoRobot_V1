/*
 # DemoRobot_V1
 * This is about a demonstrable DIY robot application project
 * All rights reserved under the R&D team Anka Robotics by Anka Technologies
 * Developers: Damithrafdo, Shenuka, Kalaynilavan, Medhawi
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
 *         |__________________________| 
 *                       |
 *                       |-----------------
 *          __________________________    |
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
#define TRIG_PIN A1
#define ECHO_PIN A2
#define MAX_DISTANCE 200 

// Servo pin
#define SERVO_PIN 1

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


//Put variables here - int Val

const int rme=10,lme=11; //enable pins, Speed
const int rmb=8, rmf=9, lmb=12, lmf=13; //motor signals, left/right motor back/forward
const int ir0=2, ir1=3, ir2=4, ir3=5, ir4=6; //ir signals white=1 and black=0
int val0=0, val1=0, val2=0, val3=0, val4=0; //variables
int THRESHOLD_DISTANCE = 20;// the distance (in cm) for obstacle detection

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;
int distance = 100;
// void stop();
// void InALine(bool x);
// void Turn(bool y);
// float getDistance();
// void ModeA();
// void ModeB();
// void ModeC();



void setup() {
  // put your setup code here, to run once:
  pinMode(rmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(rme, OUTPUT);
  pinMode(lme, OUTPUT);
  pinMode(ir0, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  // Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // Servo setup
  myservo.attach(SERVO_PIN);
  myservo.write(90);  // Center
  delay(1000);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  void ModeA();
  void ModeB();
  void ModeC();
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
float measureDistance() {
  delay(50);
  int cm = sonar.ping_cm();
  if (cm == 0) cm = 250;  // No object
  return cm;
}

 void ModeA(){
  //Obstacle avoidance 
  float distance = measureDistance();
  if (distance < THRESHOLD_DISTANCE) {
   stop();
   delay(500);       // Pause for a moment
   InALine(false); // Reverse a bit
   delay(1000); 
   Turn(true); //  Turn away from obstacle
   delay(700);   
  } else {
    InALine(true); 
  }
 }
 
 void ModeB(){
  //Obstacle avoidance with servo
  distance = measureDistance();
  Serial.println(distance);

  if (distance <= THRESHOLD_DISTANCE) {
    stop();
    delay(300);
    InALine(false);
    delay(400);
    stop();
    delay(300);

    int distanceRight = lookRight();
    delay(300);
    int distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft) {
      Turn(true);
    } else {
      Turn(false);
    }
  } else {
    InALine(true);
  }
 }
 
 void ModeC(){
  //Line following
  val0=digitalRead(ir0); 
  val1=digitalRead(ir1);
  val2=digitalRead(ir2);
  val3=digitalRead(ir3);
  val4=digitalRead(ir4);
  if(val0 && val1 && !val2 && val3 && val4) //forward (1&1&0&1&1)
  {
    bool x=true;
    InALine(x); 
  }
  else if(val0 && val1 && val2 && !val3 && !val4) //turn right (1&1&1&0&0)
  {
    bool y=true;
    Turn(y);
  }
  else if(!val0 && !val1 && val2 && val3 && val4) //turn left (0&0&1&1&1)
  {
    bool y=false;
    Turn(y);
  }
  else if(!val0 && !val1 && !val2 && !val3 && !val4) //stop (0&0&0&0&0)
  {
    stop();
  }
  else if(val0 && val1 && val2 && val3 && val4) //circle (1&1&1&1&1)
  {
   bool y=false;
    Turn(y);  
  }
  else if(!val0 && !val1 && val2 && !val3 && !val4) //in a t-shape condition turn left (0&0&1&0&0)
  {
   bool y=false;
   Turn(y);  
  }
  else if(val0 && val1 && !val2 && !val3 && !val4) //in a forward and left condition turn left (1&1&0&0&0)
  {
   bool y=false;
   Turn(y);  
  }
  else if(!val0 && !val1 && !val2 && val3 && val4) //in a forward and right condition go straight (0&0&0&1&1)
  {
   bool x=true;
   InALine(x);  
  }
  else
  {
   bool x=false;
   InALine(x);
  }
  delay(1000);
 }

 // Look right
int lookRight() {
  myservo.write(45);
  delay(500);
  int d = measureDistance();
  delay(100);
  myservo.write(90);
  return d;
}

// Look left
int lookLeft() {
  myservo.write(135);
  delay(500);
  int d = measureDistance();
  delay(100);
  myservo.write(90);
  return d;
}

// these are along with the kine following
 void InALine(bool x) //to move in a line
{
  if(x==true)
  {
    analogWrite(rme,60);
    analogWrite(lme,60);
    digitalWrite(rmb,LOW);
    digitalWrite(rmf,HIGH);
    digitalWrite(lmb,LOW);
    digitalWrite(lmf,HIGH);
    Serial.println("forward");
  }
  else //move backward
  {
    analogWrite(rme,50);
    analogWrite(lme,50);
    digitalWrite(rmb,HIGH);
    digitalWrite(rmf,LOW);
    digitalWrite(lmb,HIGH);
    digitalWrite(lmf,LOW);
    Serial.println("backward");    
  }
}

void Turn(bool y) //to turn
{
    analogWrite(rme,50);
    analogWrite(lme,50); 
    if (y==true) //move right
    {
    digitalWrite(rmb,LOW);
    digitalWrite(rmf,LOW);
    digitalWrite(lmb,LOW);
    digitalWrite(lmf,HIGH);
    Serial.println("right");      
    }
    else //move left
    {
    digitalWrite(rmb,LOW);
    digitalWrite(rmf,HIGH);
    digitalWrite(lmb,LOW);
    digitalWrite(lmf,LOW);
    Serial.println("left");      
    }
}
void stop()
{
    analogWrite(rme,0);
    analogWrite(lme,0);
    Serial.println("stop");    
}
