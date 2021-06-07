
#include <Servo.h> 
Servo myservoS1;
Servo myservoS2;
Servo myservoS3;

const int limitbut = 7;   // limit switch  
const int limitscrew = 6;   // limit switch 
const int RC1 = 2;   // RC1 switch  
const int RC2 = 8;   // RC2 switch  
const int RC3 = 11;   // RC3 switch  
const int RC4 = 12;   // RC4 switch  
const int buzzer = 4; //buzzer to arduino pin 7  
int RF1 = 0;         // variable for reading the pushbutton status
int RF2 = 0;         // variable for reading the pushbutton status
int RF3 = 0;         // variable for reading the pushbutton status
int RF4 = 0;         // variable for reading the pushbutton status
int limitbuton = 0;         // variable for reading the pushbutton status
int limitScrew = 0;         // variable for reading the pushbutton status
int toggle = 1;
 
int cop = 0;
int LinAcop = 0; // 1st run only
int count = 0;
int turnpoint = 33;
int limit = 75;

void setup() {
myservoS1.attach(9, 1000, 2000); // LM
myservoS2.attach(10, 1000, 2000); // wheels 
myservoS3.attach(3, 1000, 2000); // mini
pinMode(limitbut, INPUT);
pinMode(limitscrew, INPUT);
pinMode(RC1, INPUT);
pinMode(RC2, INPUT);   
pinMode(RC3, INPUT);
pinMode(RC4, INPUT); 
pinMode(buzzer, OUTPUT); // Set Piezo Buzzer - pin 10 as an output   
  
}
void loop() {

  
limitbuton = digitalRead(limitbut); //head button
limitScrew = digitalRead(limitscrew); //Lin Ac button
RF1 = digitalRead(RC1); //A button
RF2 = digitalRead(RC2); //C button
RF3 = digitalRead(RC3); //B button
RF4 = digitalRead(RC4); //D button


if (LinAcop == 0) // resets to top first time only
{
      tone(buzzer, 2000); // Send 1KHz sound signal... 
      delay(375);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(155);        // ...for 1sec
      tone(buzzer, 2100); // Send 1KHz sound signal... 
      delay(375);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(155);        // ...for 1sec
do
    { 
      myservoS1.writeMicroseconds(1300); // restart to top
      limitbuton = digitalRead(limitbut); //head button
      delay (100); // just to slow this down
}  while (limitbuton  == LOW ); 
      myservoS1.writeMicroseconds(1500); // stop  motor  
      delay (10000); // pause at start
      LinAcop = 1; // RUNS first time only
}

if (RF1  == HIGH) // A button UP
 {               
     tone(buzzer, 2000); // Send 1KHz sound signal... 
      delay(375);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
    myservoS3.writeMicroseconds(2000);
    delay (3000); 
      noTone(buzzer);     // Stop sound...
     
    myservoS3.writeMicroseconds(1500);               
  }

if (RF3  == HIGH) // A button UP
 {               
     tone(buzzer, 2000); // Send 1KHz sound signal... 
      delay(375);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
    if (toggle == 1)
        {toggle = 0;
        goto bytog; 
        }     
if (toggle == 0)
        {toggle = 1;
        goto bytog; 
        }        
           
  }
bytog:
  
if (RF2  == HIGH && limitScrew == LOW ) // C button DOWN if limit not made
 {               
    tone(buzzer, 2000); // Send 1KHz sound signal... 
    myservoS3.writeMicroseconds(1000);
    delay (3000);  
     noTone(buzzer);     // Stop sound...
    myservoS3.writeMicroseconds(1500);                   
 }

 

if (count <= turnpoint && toggle == 1)    //  reads button and moves UP unless tilt
      {
      myservoS2.writeMicroseconds(1200);  // 
      delay (6000);
       
      myservoS1.writeMicroseconds(1800); // move LM down
      delay (1500); // away from head
      myservoS1.writeMicroseconds(1500); // stop  motor  
      delay (100); // stop LM away from head
      count = count +1;
     }
  
  if (count > turnpoint && toggle == 1)     // only first time 
     {
  if (cop == 0)
{
  myservoS2.writeMicroseconds(1500); // stop  motor 
// lower screw
   if (limitScrew ==  LOW) //  DOWN if limit not made
 {               
    myservoS3.writeMicroseconds(1000);
    delay (3000);  
    myservoS3.writeMicroseconds(1500);                   
 }
  cop = 1; // keep from stopping each time
  delay (2000); 
}
      myservoS2.writeMicroseconds(1800); // take longer at lumbar
      delay (8000); // 
      myservoS1.writeMicroseconds(1800); // move LM screw down
      delay (1500); // 
      myservoS1.writeMicroseconds(1500); // stop  motor  
      delay (100); // 
      count = count +1;
      } 

if ( limit == 71) // lmk when it about to end
{ tone(buzzer, 2000); // Send 1KHz sound signal... 
      delay (785);  
     noTone(buzzer);     // Stop sound...
tone(buzzer, 2000); // Send 1KHz sound signal... 
      delay (785);  
     noTone(buzzer);     // Stop sound...
tone(buzzer, 2000); // Send 1KHz sound signal... 
      delay (785);  
     noTone(buzzer);     // Stop sound...
tone(buzzer, 2000); // Send 1KHz sound signal... 
      delay (785);  
     noTone(buzzer);     // Stop sound...
     
}
 
if (count > limit)     //  reads button and moves UP unless tilt     
{
do
    { 
      myservoS1.writeMicroseconds(1300); // move LM back up to start
      limitbuton = digitalRead(limitbut); //head button
      delay (100); // just to slow this down
}     while (limitbuton  == LOW ); 

myservoS1.writeMicroseconds(1500); // stop LM  motor 
delay (1000);
myservoS2.writeMicroseconds(1500); // stop  wheel motor   
      delay (9000); // 
      count = 0;
      cop = 0;
}  
if (RF4  == HIGH) // D button UP               //  reads button and moves UP unless tilt     
{
do
    { 
      myservoS1.writeMicroseconds(1300); // move LM back up to start
      limitbuton = digitalRead(limitbut); //head button
      delay (100); // just to slow this down
}  while (limitbuton  == LOW ); 

myservoS1.writeMicroseconds(1500); // stop  motor  
      delay (1000); // 
      count = 0;
      cop = 0;

} 

               
  }
  
