
//we used L298N here 
#define setPoint 2500
#define numOfSensors 4

#define sensor1 2
#define sensor2 3
#define sensor3 4
#define sensor4 5

#define motor1A 7
#define motor1B 8
#define motor2A 9
#define motor2B 10

#define ENA 6
#define ENB 11

int initialMotor1Speed=160;
int initialMotor2Speed=160;
int motorSpeed;
int Motor1Speed;
int Motor2Speed;

int currentPosition=0;
int erorr=0;
int lastErorr=0;

double Kp=0.049;
double Kd=0;
double Ki=0;


int SENSOR[4]={0,0,0,0};
int sensor[4];
void setup() {
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);

  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(motor1A,OUTPUT);
  pinMode(motor1B,OUTPUT);
  pinMode(motor2A,OUTPUT);
  pinMode(motor2B,OUTPUT);

 Serial.begin(9600);
}

void loop() {
     currentPosition=0;
  
   PID_control();

  
  
    analogWrite(ENA,Motor1Speed);
    analogWrite(ENB,Motor2Speed);

    forward();
    
   
  

    Serial.print(sensor[0]);
     Serial.print(" ");
     Serial.print(sensor[1]);
     Serial.print(" ");
     Serial.print(sensor[2]);
     Serial.print(" ");
     Serial.print(sensor[3]);
     Serial.print(" ");
     Serial.print(currentPosition);
     Serial.print(" ");
     Serial.print(Motor1Speed);
     Serial.print(" ");
     Serial.print(Motor2Speed);
     Serial.print(" ");
     Serial.print(motorSpeed);
     Serial.print(" ");
     Serial.println(erorr);
     delay(200);
}

void initializeSensors(){

     SENSOR[0]=!digitalRead(sensor1);
     SENSOR[1]=!digitalRead(sensor2);
     SENSOR[2]=!digitalRead(sensor3);
     SENSOR[3]=!digitalRead(sensor4);

   if(SENSOR[0]==1)sensor[0]=1000;
   else sensor[0]=0;
   
   if(SENSOR[1]==1)sensor[1]=2000;
   else sensor[1]=0;

   if(SENSOR[2]==1)sensor[2]=3000;
   else sensor[2]=0;

   if(SENSOR[3]==1)sensor[3]=4000;
   else sensor[3]=0;
}


void position(){
  initializeSensors();
  int count=0;
  if(sensor[0]==0){ currentPosition+=1000; count++;}
  if(sensor[1]==0){ currentPosition+=2000; count++;}
  if(sensor[2]==0){ currentPosition+=3000; count++;}
  if(sensor[3]==0){ currentPosition+=4000; count++;}

  currentPosition/=count;
}


void PID_control(){
  position();
  erorr=currentPosition-setPoint;

   motorSpeed=(Kp*erorr)+(Kd*(erorr-lastErorr));

  lastErorr=erorr;

  Motor1Speed=initialMotor1Speed+motorSpeed;
  Motor2Speed=initialMotor2Speed-motorSpeed;

  Motor1Speed=constrain(Motor1Speed,0,255);
  Motor2Speed=constrain(Motor2Speed,0,255);


}


void forward(){
    digitalWrite(motor1A,HIGH);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,HIGH);
    digitalWrite(motor2B,LOW);
}
void backward(){
  
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,HIGH);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,HIGH);
}

void left(){
  
    digitalWrite(motor1A,HIGH);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,LOW);
    digitalWrite(motor2B,LOW);
}

void right(){
  
    digitalWrite(motor1A,LOW);
    digitalWrite(motor1B,LOW);
    digitalWrite(motor2A,HIGH);
    digitalWrite(motor2B,LOW);
}

