extern "C"{
#include "sequencer.h"
};

int pin = 5;


float seconde = 1.0;
float time_f,tempo_f = 0.0;

unsigned long currentTime=0;
unsigned long previousTime=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  initialize(2.0, 0.8);
  Serial.begin(9600);
  time_f = time_frame(seconde);
  tempo_f = tempo(seconde);
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
