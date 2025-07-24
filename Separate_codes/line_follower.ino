/*
    * Line Follower Robot using Arduino
    * By: Damithra Fernando
    * Date: 2025-06-16
    * This code is for a simple line follower robot that uses IR sensors to detect the line and control the motors accordingly.
    * The robot can move forward, turn left, turn right, and stop based on the sensor readings.
    * 
*/

//const int rme=10,lme=11; //enable pins
const int lmb=9, lmf=10, rmb=11, rmf=12; //motor signals
const int ir0=2, ir1=3, ir2=4, //ir3=5, ir4=6; //ir signals white=1 and black=0
int val0=0, val1=0, val2=0, val3=0, val4=0; //variables

void moveForward() {
    digitalWrite(lmb, LOW);
    digitalWrite(lmf, HIGH);
    digitalWrite(rmb, LOW);
    digitalWrite(rmf, HIGH);
}
void turnLeft() {
    digitalWrite(lmb, LOW);
    digitalWrite(lmf, LOW);
    digitalWrite(rmb, LOW);
    digitalWrite(rmf, HIGH);
}
void turnRight() {
    digitalWrite(lmb, LOW);
    digitalWrite(lmf, HIGH);
    digitalWrite(rmb, LOW);
    digitalWrite(rmf, LOW);
}
void stop() {
    digitalWrite(lmb, LOW);
    digitalWrite(lmf, LOW);
    digitalWrite(rmb, LOW);
    digitalWrite(rmf, LOW);
}

void setup() {
  // put your setup code here, to run once:
pinMode(rmb, OUTPUT);
pinMode(rmf, OUTPUT);
pinMode(lmb, OUTPUT);
pinMode(lmf, OUTPUT);
//pinMode(rme, OUTPUT);
//pinMode(lme, OUTPUT);
pinMode(ir0, INPUT);
pinMode(ir1, INPUT);
pinMode(ir2, INPUT);
pinMode(ir3, INPUT);
pinMode(ir4, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
val0=digitalRead(ir0);
val1=digitalRead(ir1);
val2=digitalRead(ir2);
// val3=digitalRead(ir3);
// val4=digitalRead(ir4);
}