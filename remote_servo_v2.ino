#include <IRremote.h>
#include <Servo.h> 

int receiverPin = 11; //IR RECEIVER PIN
int servoPin = 10;    //SERVO PIN
int degreesOn = 30;    //DEGREES FOR LIGHTS ON
int degreesOff = 150;  //DEGREES FOR LIGHTS OFF
int degreesIdle = 90;  //REST POSITION - DEGREES TO LET LIGHT SWITCH BE MANUALLY USED IF NEEDED

#define code1  59415  //CODE FOR "ON"
#define code2  26775  //CODE FOR "OFF"
 
Servo Servo1; 
IRrecv ir_rec(receiverPin);
decode_results result;
 
void setup()
{
  Serial.begin(9600);   
  ir_rec.enableIRIn();  
  Servo1.attach(servoPin);
  delay(100);
}

void loop() {
  if (ir_rec.decode(&result)) {
    unsigned int val = result.value;
    switch(val) {
       case code1:
          Servo1.attach(servoPin);   //ATTACH SERVO
          Servo1.write(degreesOn);   //LIGHTS ON
          delay(500);
          Servo1.write(degreesIdle); //BACK TO REST POSITION
          delay(500);                //DELAY NEEDED TO MAKE SERVO WORK CORRECTLY (IF THIS IS NOT ASSIGNED THE SERVO WOULD DETACH BEFORE MOVING TO POSITION)
          Serial.println("- On -");  //DEBUGGING PURPOSES
          Servo1.detach();           //DETACH SERVO TO SAVER POWER
          break;
       case code2:
          Servo1.attach(servoPin);   //ATTACH SERVO
          Servo1.write(degreesOff);  //LIGHTS OFF
          delay(500);               
          Servo1.write(degreesIdle); //BACK TO REST POSITION
          delay(500);                //DELAY NEEDED TO MAKE SERVO WORK CORRECTLY (IF THIS IS NOT ASSIGNED THE SERVO WOULD DETACH BEFORE MOVING TO POSITION)
          Serial.println("- Off -"); //DEBUGGING PURPOSES
          Servo1.detach();           //DETACH SERVO TO SAVER POWER
          break;   
   
    }   
    Serial.println(val); //DEBUGGING PURPOSES
    ir_rec.resume();
  }
}

