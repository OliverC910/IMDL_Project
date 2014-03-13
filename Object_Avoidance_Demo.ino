int dirPin_L = 6;
int stepperPin_L = 7;
int dirPin_R = 8;
int stepperPin_R = 9;
int pingPin_L = 2;
int pingPin_M = 3;
int pingPin_R = 4;
long duration, inches, inches_L, inches_M, inches_R;
int forward = 0;
int left = 1;
int right = 2;
int backward = 3;

void setup() {
 pinMode(dirPin_L, OUTPUT);
 pinMode(stepperPin_L, OUTPUT);
  pinMode(dirPin_R, OUTPUT);
  pinMode(stepperPin_R, OUTPUT);
    Serial.begin(9600);
}

 void step(int dir,int steps){
   if (dir == 1){
 digitalWrite(dirPin_L,false);
 digitalWrite(dirPin_R,true);
 delay(50);
   }
   else if (dir == 2){
 digitalWrite(dirPin_L,true);
 digitalWrite(dirPin_R,false);
 delay(50);
   }
   else if (dir == 3){
 digitalWrite(dirPin_L,false);
 digitalWrite(dirPin_R,false);
 delay(50);
   }
   else {
 digitalWrite(dirPin_L,true);
 digitalWrite(dirPin_R,true);
 delay(50);
   }
   
 for(int i=0;i<steps;i++){
   digitalWrite(stepperPin_L, HIGH);
   digitalWrite(stepperPin_R, HIGH);
   delayMicroseconds(800);
   digitalWrite(stepperPin_L, LOW);
   digitalWrite(stepperPin_R, LOW);
   delayMicroseconds(800);
 }
 }
 
long ping(int pingPin){
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  return inches = microsecondsToInches(duration);
}

void loop(){

 inches_L =  ping(pingPin_L);
 inches_M =  ping(pingPin_M);
 inches_R =  ping(pingPin_R);  
  
 Serial.print(inches_L);
 Serial.print("in_L, "); 
 Serial.println();
 Serial.print(inches_R);
 Serial.print("in_R, "); 
 Serial.println();
 Serial.print(inches_M);
 Serial.print("in_M, "); 
 Serial.println();
  
 if(inches_L < 5){ 
 Serial.print("Left Turn"); 
 Serial.println();
 step(left,100);
 delay(20);
 }
 else if (inches_R < 5){
 Serial.print("Right Turn"); 
 Serial.println();
 step(right,100);
 delay(20);
 } 
 else if (inches_M < 5){
 Serial.print("Backward"); 
 Serial.println();
 step(backward,100);
 delay(20);
 }
 else{
    step(forward,500);
 delay(20);
  Serial.print("Forward");
   Serial.println(); 
 }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
