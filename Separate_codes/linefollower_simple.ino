#define LEFT_SENSOR_PIN   2
#define CENTER_SENSOR_PIN 3
#define RIGHT_SENSOR_PIN  4

#define LEFT_MOTOR_FORWARD  9
#define LEFT_MOTOR_BACKWARD 10
#define RIGHT_MOTOR_FORWARD 11
#define RIGHT_MOTOR_BACKWARD 12

void setup() {
    randomSeed(analogRead(0)); // Initialize random seed
    pinMode(LEFT_SENSOR_PIN, INPUT);
    pinMode(CENTER_SENSOR_PIN, INPUT);
    pinMode(RIGHT_SENSOR_PIN, INPUT);

    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
}

void loop() {
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
    } else {
        // No line detected, stop
        stopMotors();
    }
}

void moveForward() {
    digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void turnLeft() {
    digitalWrite(LEFT_MOTOR_FORWARD, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void turnRight() {
    digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}

void stopMotors() {
    digitalWrite(LEFT_MOTOR_FORWARD, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}