/*
	PinToggle.h - control pin toggling
	Created by Bob Burton, 25/03/2018
*/

#ifndef PinToggle_h
#define PinToggle_h

#include "Arduino.h"

class PinToggle
{
  private:
    byte _pinNum;
    byte _startState;
    byte _originalStartState;
    unsigned int _toggleCount;
    unsigned int _originalToggleCount;
    boolean _started = false;
    unsigned long _periods[2];
    byte _periodIndex;
    unsigned long _startTime;
    unsigned long _currentTime;
    boolean _toggling = false;
    byte _currentState;
    boolean _counting;
    void _writeState();

  public:
    PinToggle(byte pin);  //constructor - define the pin to be used
    void begin();	//set pinMode
    void startToggling(byte state, unsigned long lowPeriod, unsigned long highPeriod, unsigned int toggleCount = 0);  //set initial state and periods
    void restartToggling();	//restart toggling with original parameters
    void update();  //check whether period has ended and change state if true
    void setOutputState(byte state);	//set the output state for the pin and stop toggling
    byte getOutputState();	//get the current state of the output
    void stopToggling(byte state);	//stop toggling and go into the given state
    void resumeToggling();	//resume toggling
    boolean getTogglingState();	//get toggling state
    unsigned int getToggleCount();	//get the number of toggles remaining
};

#endif
