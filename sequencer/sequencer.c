#include "Arduino.h"
#include "sequencer.h"

float const MILLI = 1000.0;
float beat_tempo = 0;
float delta_tempo = 0;

//initalizing the beat and the delta of ON/OFF
void initialize(float beat, float delta){
  beat_tempo = beat;
  delta_tempo = delta;
}

//time frame gives the value in millisecond of OFF time depending on the beat and tempo
float time_frame(float seconde){
  return (((seconde/beat_tempo)*delta_tempo)*MILLI);
}

//time frame gives the value in millisecond of ON time depending on the beat and tempo
float tempo(float seconde){
  return (((seconde/beat_tempo)-((seconde/beat_tempo)*delta_tempo))*MILLI);
}
