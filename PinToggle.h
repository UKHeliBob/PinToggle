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
    unsigned long _togglePeriods[2];
    unsigned long _burstPeriods[2];	
    byte _togglePeriodIndex;
    byte _burstPeriodIndex;
    unsigned long _toggleStartTime;
	unsigned long _burstStartTime;	
	byte _interBurstState;
    unsigned long _currentTime;
    byte _currentState;
	boolean _counting;
	unsigned long _waitStartTime;
	unsigned long _waitPeriod;
	boolean _toggling = false;
	boolean _waiting = false;
	boolean _bursting = false;
	byte _ID;
	void _writeState();
	
  public:
    using callbackFunc = void (*)(int);   //create function pointer type
    callbackFunc cb1;                       //an instance of the function pointer type
    PinToggle(byte pin);  //constructor - define the pin to be used
	byte begin();	//set pinMode and return ID
	void startToggling(byte startState, unsigned long lowPeriod, unsigned long highPeriod);  //base version
    void startToggling(byte state, unsigned long lowPeriod, unsigned long highPeriod, unsigned int toggleCount);  //set initial state and periods
	void waitBeforeToggling(byte startState, unsigned long lowPeriod, unsigned long highPeriod, unsigned long waitPeriod);
    void restartToggling();	//restart toggling with original parameters
	void update(callbackFunc func = nullptr);  //check whether period has ended and change state if true
    void setOutputState(byte state);	//set the output state for the pin and stop toggling
	byte getOutputState();	//get the current state of the output
	void stopToggling(byte state);	//stop toggling and go into the given state
    void resumeToggling();	//resume toggling
    boolean getTogglingState();	//get toggling state
	unsigned int getToggleCount();	//get the number of toggles remaining
	void updateLowPeriod(unsigned long newPeriod);
	void updateHighPeriod(unsigned long newPeriod);	
	void startBurstMode(unsigned long lowPeriod, unsigned long highPeriod, unsigned long burstOnPeriod, unsigned long burstOffPeriod, byte interBurstState);
	void stopBurstMode(byte stoppedBurstState);
	};

#endif