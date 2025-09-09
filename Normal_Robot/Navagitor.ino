// YOU HAVE TO INSTALL THE AFMOTOR LIBRARY BEFORE UPLOAD THE CODE//
// GO TO SKETCH >> INCLUDE LIBRARY >> ADD .ZIP LIBRARY >> SELECT AF MOTOR ZIP FILE //


//including the libraries
#include <AFMotor.h>

//defining pins and variables
#define lefts A0
#define rights A1

const int trigpin = A4;
const int echopin = A5;
long duration;
int distance;

//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);



void setup() {
  //Setting the motor speed
  motor1.setSpeed(225);
  motor2.setSpeed(225);
  motor3.setSpeed(225);
  motor4.setSpeed(225);
  //Declaring PIN input types
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  
  pinMode(trigpin , OUTPUT);
  pinMode(echopin , INPUT);
  //Begin serial communication
  Serial.begin(9600);
  
}

void loop(){
  //Printing values of the sensors to the serial monitor
  digitalWrite(trigpin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println("Distance: ");
  Serial.println(distance);

  Serial.println(analogRead(lefts));
  Serial.println(analogRead(rights));
  int left = analogRead(lefts);
  int right = analogRead(rights);
  //line detected by both
  if(distance < 10) 
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);

  } 
  else
  {
    if((left)<=40 && (right)<=40){
      //Forward
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    }
    //line detected by left sensor
    else if((left)<=40 && !(right)<=40){
      //turn left
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
      
    }
    //line detected by right sensor
    else if(!(left)<=40 && (right)<=40){
      //turn right
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    
    }
    //line detected by none
    else if(!(left)<=40 && !(right)<=40){
      //stop
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
    
    }
  }
}
