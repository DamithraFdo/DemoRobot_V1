This is about a demonstrable DIY robot application project
 * All rights reserved under the R&D team Anka Robotics by Anka Technologies
 * Developers: Damithrafdo, Shenuka, Kalaynilavan, Medhawi
 * Under the supervision of Dr. Tharindu
   
 * Development Board: Arduino Uno
 * Functions: Obstacle avoiding, line following...
 * Sensors: Ultrasonic sensor array, IR line follower array
 * Motors: 2 DC motors with motor driver
  
 * Project Name: DemoRobot_V1
 * Version: 1.0 
 * Date: 2025-06-16
 * Description:
   This code is for a simple robot that can follow a line using an IR sensor array and avoid obstacles using an ultrasonic sensor array.
   The robot can move forward, backward, turn left, and turn right based on the readings from the IR sensors.
   The robot is controlled using an Arduino Uno board, which receives input from the sensors and sends signals to the motors.
   The robot can be programmed to follow a line, avoid obstacles, and perform other tasks based on the sensor readings.
   This code is a basic implementation of a line-following robot with obstacle avoidance capabilities.
   
 * Diagram        
           __________________________
          |                          |
          | Ultrasonic Sensor Array  |
          |__________________________| 
                         |
                         |-----------------
            __________________________    |
           |  (ir0,ir1,ir2,ir3,ir4)   |   |
           |  Line Follower IR Array  |   |
           |__________________________|   |
                         |                |
                         |-----------------
                   ______|______
                  |             |
                  | Arduino Uno |
                  |_____________|
                         |
    __________     ______|______     ___________
   |   (lm)   |   |             |   |   (rm)    |  
   |Left Motor|---| MotorDriver |---|Right Motor| 
   |__________|   |_____________|   |___________|
              
   
