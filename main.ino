//Standard library for servo motors
#include <Servo.h>

//High level library to interact with ultrasonic server
#include <NewPing.h>

//L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

//sensor pins
#define trig_pin_main A0 
#define echo_pin_main A1 

#define trig_pin_right A2
#define echo_pin_right A3 

#define trig_pin_right A4
#define echo_pin_right A5

#define maximum_distance 200
boolean goesForward = false;
int distance_main = 100;
int distance_right;
int distance_left;

NewPing sonar(trig_pin_main, echo_pin_main, maximum_distance);
NewPing rightSonar(trig_pin_right,echo_pin_right,maximum_distance);
NewPing leftSonar(trig_pin_right,echo_pin_right,maximum_distance);


const int servo_pin = 10;
Servo servo_main;


void setup(){
  //Baud rate 9600
  Serial.begin(9600);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_main.attach(servo_pin);

  servo_main.write(115);
  delay(2000);
  distance_main = readPing();
  delay(100);
  distance_main = readPing();
  delay(100);
  distance_main = readPing();
  delay(100);
  distance_left=readleft();
  distance_right=readright();
  delay(100);
}

void loop(){
  Serial.println(distance_left);
  Serial.println(distance_right);

  if(distance_right<=15){//right Ultrasonic
   stopMoving();
    delay(200);
     turnSmallLeft();
  }

  if(distance_left<=15){//Left Ultrasonic
    stopMoving();
    delay(200);
    turnSmallRight();
  }
  
  if (distance_main <= 20){
   
    stopMoving();
    delay(300);
    moveBackward();
    delay(400);
    stopMoving();
    delay(300);
    distanceRight = lookRight(); //using main ultrasonic
    delay(300);
    distanceLeft = lookLeft(); //using main ultrasonic
    delay(300);

    if (distanceRight >= distanceLeft){
      turnRight();
      stopMoving();
    }
    else{
      turnLeft();
      stopMoving();
    }
  }
  else{
    moveForward(); 
  }
    distance_main = readPing();
    distance_left=readleft(); //using dedicated ultrasonic
    distance_right=readright(); //using dedicated ultrasonic
}

//main sensor
int lookRight(){  
  servo_main.write(50);
  delay(500);
  int distance_main = readPing();
  delay(100);
  servo_main.write(115);
  return distance_main;
}

//main sensor
int lookLeft(){
  servo_main.write(170);
  delay(500);
  int distance_main = readPing();
  delay(100);
  servo_main.write(115);
  return distance_main;
}

//Forward distance
int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

//Dedicated left sensor
int readleft(){
  delay(70);
  int cm = leftSonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

//Dedicated right sensor
int readright(){
  delay(70);
  int cm = rightSonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}


void stopMoving(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(250);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
 
}

void turnSmallRight(){
 digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(125);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
}


void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(250);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void turnSmallLeft(){
 digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(125);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
}