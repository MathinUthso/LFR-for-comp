//we used the library for motordriverShield in this version of code
#include<AFMotor.h>
#define left A0
#define right A5
#define threshold 300
AF_DCMotor motor1(1,MOTOR12_1KHZ);
AF_DCMotor motor2(4,MOTOR34_1KHZ);
int left_s;
int right_s;
void setup() {
  Serial.begin(9600);
  pinMode(left,INPUT);
  pinMode(right,INPUT);

  motor1.setSpeed(90);

  motor2.setSpeed(90);
  

}

void loop()
 {
   
   right_s= analogRead(right);
   left_s=analogRead(left);
   
   Serial.print(left_s);
   Serial.print(" ");

   Serial.println(right_s);
   delay(100);
   

 if(left_s>threshold && right_s>threshold)
 stopmotor();
  else if(left_s>threshold && right_s<threshold)
 turnright();
 else if(left_s<threshold && right_s>threshold)
 turnleft();
 else if(left_s<threshold && right_s<threshold)
 forwardmotor();
  
  

}

void turnright()
{
  motor1.run(FORWARD);
  motor2.run(BACKWARD); 
}

void turnleft()
{
  motor1.run(BACKWARD);
  motor2.run(FORWARD); 
}

void forwardmotor()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD); 
}

void backward()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD); 
}
void stopmotor()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}