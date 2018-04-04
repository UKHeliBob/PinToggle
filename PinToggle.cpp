/*
  PinToggle.cpp - control pin toggling
  Created by Bob Burton, 25/03/2018
*/

#include "Arduino.h"
#include "PinToggle.h"

PinToggle::PinToggle(byte pin)  //constructor
{
  _pinNum = pin;
  

 }

void PinToggle::begin()
{
  pinMode(_pinNum, OUTPUT);
}

//overloaded function to handle optional parameters

//base version
void PinToggle::startToggling(byte startState, unsigned long lowPeriod, unsigned long highPeriod)
{
  _periods[0] = lowPeriod;
  _periods[1] = highPeriod;
  if (_startState == LOW)
  {
    _periodIndex = 0;
  }
  else
  {
    _periodIndex = 1;
  }
	_startState = startState;
	_originalStartState = _startState;
	_currentState = _startState;
	_writeState();
	_startTime = millis();
	_toggling = true;
	_started = true;	
}

//with toggle count parameter
void PinToggle::startToggling(byte startState, unsigned long lowPeriod, unsigned long highPeriod, unsigned int toggleCount)
{
	_toggleCount = toggleCount;
	_originalToggleCount = _toggleCount;
	_counting = true;
	startToggling(startState, lowPeriod, highPeriod);	//call base version
}

void PinToggle::waitBeforeToggling(byte startState, unsigned long lowPeriod, unsigned long highPeriod, unsigned long waitPeriod)
{
  _currentState = startState;
  _originalStartState = startState;
  _periods[0] = lowPeriod;
  _periods[1] = highPeriod;
    if (_startState == LOW)
  {
    _periodIndex = 0;
  }
  else
  {
    _periodIndex = 1;
  }
  _waiting = true;
  _waitPeriod = waitPeriod;
  _waitStartTime = millis();	
_writeState();  
}

void PinToggle::restartToggling() //restart toggling with original parameters
{
  if (_started)
  {
    startToggling(_originalStartState, _periods[0], _periods[1], _originalToggleCount);
  }
}

void PinToggle::update(callbackFunc func = nullptr)  //change state if period ended.  callback optional
{
  _currentTime = millis();
  if (_toggling)   //no need to update if not currently toggling
  {
    if (_currentTime - _startTime >= _periods[_periodIndex])
    {
      _currentState = !_currentState;
      _writeState();
      _periodIndex++;
      _periodIndex %= 2;
      _startTime = _currentTime;
      if (_counting)
      {
        _toggleCount--;
		if (func)
			{
				cb1 = func;          //function to execute
				cb1(_toggleCount);  //execute the callback function.  pass back toggle count
			}
        if (_toggleCount == 0)
		{	 
          _toggling = false;
        }
      }
    }
  }
  
  if (_waiting)
  {
	 if (_currentTime - _waitStartTime >= _waitPeriod)
	 {
		 _waiting = false;
		 startToggling(_originalStartState, _periods[0], _periods[1]);
	 }
  }
  
  
}

unsigned int PinToggle::getToggleCount()
{
  return _toggleCount;
}

void PinToggle::stopToggling(byte state)
{
  setOutputState(state);
}

void PinToggle::setOutputState(byte state)
{
  _currentState = state;
  _writeState();
  _toggling = false;
}

byte PinToggle::getOutputState()
{
  return _currentState;
}


void PinToggle::resumeToggling()
{
  if (_started)
  {
    _toggling = true;
  }
}

boolean PinToggle::getTogglingState()
{
  return _toggling;
}

void PinToggle::_writeState()
{
  digitalWrite(_pinNum, _currentState);
}

void PinToggle::updateLowPeriod(unsigned long newPeriod)
{
  if (_toggling)
  {
    _periods[0] = newPeriod;
  }
}

void PinToggle::updateHighPeriod(unsigned long newPeriod)
{
  if (_toggling)
  {
    _periods[1] = newPeriod;
  }
}
