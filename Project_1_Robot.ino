/*
 * This is about demonstratable DIY robot application project
 * All right reserved under R&D team Anka Robotics by Anka Technologies
 * Developers: Damithrafdo, Shenuka, Kalaynilavan, Medhawi
 * Under supervision of Dr. Tharindu
 * 
 * Development Board: arduino uno
 * Functions: Obstacle avoiding, line folowing ...
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





//Add difines here - #define app A0





//Put variables here - int Val

const int rme=10,lme=11; //enable pins, Speed
const int rmb=8, rmf=9, lmb=12, lmf=13; //motor signals, left/right motor back/forward
const int ir0=2, ir1=3, ir2=4, ir3=5, ir4=6; //ir signals white=1 and black=0
int val0=0, val1=0, val2=0, val3=0, val4=0; //variables



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
  void ModeB();
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

 void ModeA(){
  //Obstacle avoidance 
 }
 
 void ModeB(){
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
 
 void ModeC(){
  
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
