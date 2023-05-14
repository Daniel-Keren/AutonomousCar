int in1A=8;
int in2A=7;
int enA=9;
int Speed=190;
int StartSPEED=255;
int in1B=10;
int in2B=11;
int enB=3;
int Trigpin=4;
int Echopin=5;
int TurnSpeed=125;
float x,t;
int Th=30;
bool Driveflag=0;
bool Trunflag=0;


void setup() {
  //Motor A config to pins 7,8,9
  pinMode(in1A,OUTPUT);
  pinMode(in2A,OUTPUT);
  pinMode(enA,OUTPUT);
  //Motor B config to pins 10,11,3
  pinMode(in1B,OUTPUT);
  pinMode(in2B,OUTPUT);
  pinMode(enB,OUTPUT);
  //Sonar config to pins 4,5
  pinMode(Trigpin,OUTPUT);
  pinMode(Echopin,INPUT);
  Serial.begin(9600);

  //Start moving forward
  digitalWrite(in1A,LOW);
  digitalWrite(in2A,HIGH);
  digitalWrite(in1B,LOW);
  digitalWrite(in2B,HIGH);
  analogWrite(enB,Speed);
  analogWrite(enA,Speed);

  x=calcDis();
}

void loop() {
   //Check if the closest object is in the range of collision
   if (x<Th){
    //Reset moving forward state
    Driveflag=0;
    //Check if previous iteration was moving forward
    if (Trunflag==0){
      //stop car motors and wait for 1.2 seconds
      digitalWrite(in1A,LOW);
      digitalWrite(in2A,LOW);
      digitalWrite(in1B,LOW);
      digitalWrite(in2B,LOW);
      delay(1200);
      //Config 2 motors to turn opposite ways so the car turns right for 2.5 seconds
      digitalWrite(in1A,HIGH);
      digitalWrite(in2A,LOW);
      digitalWrite(in1B,LOW);
      digitalWrite(in2B,HIGH);
      analogWrite(enB,TurnSpeed);
      analogWrite(enA,TurnSpeed);
      //Set current state to turnig state so there is no need to stop the car again
      Trunflag=1;
      delay(2500);
      }
     //Calculate the distance to the closest object for next iteration
     x=calcDis();    
     }
// The car is not in the range of collision so keep moving forward
   else{
    //Reset turning state 
    Trunflag=0;
    //Check if previous iteration was turning state
    if (Driveflag==0){
    //Config motors to move the car forward
    digitalWrite(in1A,LOW);
    digitalWrite(in2A,HIGH);
    digitalWrite(in1B,LOW);
    digitalWrite(in2B,HIGH);
    analogWrite(enB,Speed);
    analogWrite(enA,Speed);
    //Set current state to moving forward  
    Driveflag=1;
    }
    //Calculate the distance to the closest object for next iteration
    x=calcDis(); 
  }
}

//Function that return the distance to the closest object 
float calcDis(){
  digitalWrite(Trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(Trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigpin,LOW);

  t=pulseIn(Echopin,HIGH);
  x=0.0344*t/2;
  Serial.print("Distance is: ");
  Serial.print(x);
  Serial.println(" cm");
  return x;
  }
