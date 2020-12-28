#include "Arduino.h"
#include "sequencer.h"

float const MILLI = 1000.0;
float beat_tempo = 0;
float delta_tempo = 0;

void initialize(float beat, float delta){
	beat_tempo = beat;
	delta_tempo = delta;
}

float time_frame(float seconde){
	return (((seconde/beat_tempo)*delta_tempo)*MILLI);
}

float tempo(float seconde){
	return (((seconde/beat_tempo)-((seconde/beat_tempo)*delta_tempo))*MILLI);
}