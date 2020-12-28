extern "C"{
#include "sequencer.h"
};

//pin used can be change to anay digital pin
int pin = 5;

//second is the time frame for the temop
float seconde = 1.0;
float time_f,tempo_f = 0.0;

unsigned long currentTime=0;
unsigned long previousTime=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  //2.0 is the time division it means a tempo of 2 beats per second 1/2 = 0.5s
  //0.8 (80%) is the percentage of OFF time, 0.5*0.8 = 0.4s -> LOW 0.4s - HIGH 0.1s
  //initialize the counters to calculate the tempo
  initialize(2.0, 0.8);
  //getting values that have been calculated
  time_f = time_frame(seconde);
  tempo_f = tempo(seconde);
  
  Serial.begin(9600);
}

void loop() {

  currentTime=millis();
  if((currentTime-previousTime)>= tempo_f){
        digitalWrite(pin, LOW);
        if((currentTime-previousTime)>= time_f){
          digitalWrite(pin, HIGH);
          previousTime=currentTime;
        }
       
  }
  
  
}
