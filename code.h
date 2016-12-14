
const int trigPin = D5;
const int echoPin = D6;
const int magneticSensor = A0;
const int ledRedPin = D0;
const int ledYellowPin = D1;
const int ledGreenPin = D2;
 
 
 
long duration;
int distance;
char publishString[40];
int lastDistance=0;
String top=" ";
String lastTop=" ";
int  sensorReading=0;

const int numRows = 2;
const int numCols = 16;

 int previousDis = 0;
 int newTarget = 0;
 
 int  currentLevel=0;
 
 int myArray[100];
 int counter=0;
 int progress=0;

 int lastTime=0;
 boolean checkLastTime=false;
 boolean targetReached=true;
 
void setup() {
    

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(magneticSensor, INPUT);
pinMode(ledRedPin, OUTPUT); 
pinMode(ledYellowPin, OUTPUT); 
pinMode(ledGreenPin, OUTPUT); 

Time.zone(-6);
}


void loop() {
    

    sensorReading = analogRead(magneticSensor);
    delay(1000);
    
   /* sprintf(publishString1,"%u",sensorReading);
    Particle.publish("sensorReading", publishString1);*/
   
   topStauts();
   
   if(!(top.equals(lastTop))){
         Particle.publish("Top", top);
         lastTop=top;
         
   }

    
  if(top.equals("Opened")){
        
        digitalWrite(trigPin,LOW);
        delayMicroseconds(2);

        digitalWrite(trigPin,HIGH);
        delayMicroseconds(10);

        digitalWrite(trigPin,LOW);


        duration=pulseIn(echoPin,HIGH);
        distance=duration *0.034/2;

        delay(1000);


        waterTracker();


        delay(1000);    
    
}

 dayLog();
 EndOfDayClear();
 reminder();
 reachingTarget();
}


/* this function reads Magnetic Door Switch sensor. If the "magnet" is closed to the "read switch" will change the top value to "Closed" */

void  topStauts(){
    
    if(sensorReading>=500) {
        top="Opened";
    }else {
        top="Closed";
    }
}


/* this function stores the last value of progress and the current value then runs target() */
void dayLog(){
    
    
    int lastValueInArray=0;
    
    if(counter ==0){
    
    }
    else
    {
     lastValueInArray=myArray[counter -1];
    }
    
    
    if(top.equals("Closed") & (lastValueInArray != currentLevel))
    {
        
        myArray[counter]=currentLevel;
        counter++;
    
        
        if(counter>=2){
         Target();
        
        }
    }
    
    delay(1000);

    
}


// this function caluclates the progress useing the pervious value and current
void Target(){

if((myArray[counter-1]< myArray[counter-2])){
    
    progress= progress + (myArray[counter-2]-myArray[counter-1]);
    sprintf(publishString,"%u",progress);
     Particle.publish("progress", publishString);
      light();
      lastTime=Time.hour();
      checkLastTime=true;
}
    
}

// this function displays the level of water on ML.
void waterTracker(){
     
        if(distance<=18 && distance>=0) {
      
     if(distance!=lastDistance) {
         int x=0;
         for(int i=18;i>distance;i--){
             x++;
         }
         
                 currentLevel= x * 40;
                 sprintf(publishString,"%u",currentLevel);
                 Particle.publish("currentLevel", publishString);
                 lastDistance=distance;
                 delay(1000);
              
  }
  
        }
         
     }
     
     // this function changes the light based on prorgess 
     void light(){
         
         if(progress==0){
        
         digitalWrite(ledRedPin,LOW);  
         digitalWrite(ledYellowPin,LOW);   
         digitalWrite(ledGreenPin,LOW);
         }
         
         else if(progress<400){
         digitalWrite(ledRedPin,HIGH);  
         digitalWrite(ledYellowPin,LOW);   
         digitalWrite(ledGreenPin,LOW);    
             
         }else if(progress>=400 && progress<1000){
             
         digitalWrite(ledRedPin,LOW);  
         digitalWrite(ledYellowPin,HIGH);   
         digitalWrite(ledGreenPin,LOW);   
             
         }else if(progress>1000){
             
         digitalWrite(ledRedPin,LOW);  
         digitalWrite(ledYellowPin,LOW);   
         digitalWrite(ledGreenPin,HIGH); 
             
         }
     }
     
     /* this function runs every day at 11:59 to update the progress and light. in other word it's start new day by setting every thing to default*/
void EndOfDayClear(){
         
    if(Time.hour()==23 && Time.minute()==59)
    {
                  
            progress=0;
            counter=0;
            light();
            targetReached=true;
                     
            delay(60000);
    }
    

} 

/* this function runs when the progress doesn't cheange in more than 6 hours */
void reminder(){
    
    int period=Time.hour()-lastTime;
    
    
    if (period>=6 && checkLastTime==true)
    {
           Particle.publish("Reminder", "More than 6 houres");
           checkLastTime=false;
           delay(1000);
    }
}

/* this function runs once and only once in a day to publish event if the progress more than 1000 */
void reachingTarget(){
    
    if(progress>=1000 && targetReached==true){
        Particle.publish("Target", "Congratulation !! You reached your target");
        targetReached=false;
        delay(1000);
    }
}



 