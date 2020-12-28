#include "Arduino.h"

#ifndef sequencer.h
#define sequencer.h

void initialize(float beat, float delta);
float time_frame(float seconde);
float tempo(float seconde);

#endif