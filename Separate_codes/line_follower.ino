/*
    * Line Follower Robot using Arduino
    * By: Damithra Fernando
    * Date: 2025-06-16
    * This code is for a simple line follower robot that uses IR sensors to detect the line and control the motors accordingly.
    * The robot can move forward, turn left, turn right, and stop based on the sensor readings.
    * 
*/

const int rme=10,lme=11; //enable pins
const int rmb=8, rmf=9, lmb=12, lmf=13; //motor signals
const int ir0=2, ir1=3, ir2=4, ir3=5, ir4=6; //ir signals white=1 and black=0
int val0=0, val1=0, val2=0, val3=0, val4=0; //variables

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
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
val0=digitalRead(ir0);
val1=digitalRead(ir1);
val2=digitalRead(ir2);
val3=digitalRead(ir3);
val4=digitalRead(ir4);
if(val0 && val1 && !val2 && val3 && val4) //forward
{
  bool x=true;
  InALine(x); 
}
else if(val0 && val1 && val2 && !val3 && !val4) //turn right
{
  bool y=true;
  Turn(y);
}
else if(!val0 && !val1 && val2 && val3 && val4) //turn left
{
  bool y=false;
  Turn(y);
}
else if(!val0 && !val1 && !val2 && !val3 && !val4) //stop
{
  stop();
}
else if(val0 && val1 && val2 && val3 && val4) //circle
{
  bool y=false;
  Turn(y);  
}
else if(!val0 && !val1 && val2 && !val3 && !val4) //in a t-shape condition turn left
{
  bool y=false;
  Turn(y);  
}
else if(val0 && val1 && !val2 && !val3 && !val4) //in a forward and left condition turn left
{
  bool y=false;
  Turn(y);  
}
else if(!val0 && !val1 && !val2 && val3 && val4) //in a forward and right condition go straight
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
