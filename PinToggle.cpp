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

byte PinToggle::begin()
{
  static byte _ID = 0;
  pinMode(_pinNum, OUTPUT);
 return _ID++;
}

//overloaded function to handle optional parameters

//base version
void PinToggle::startToggling(byte startState, unsigned long lowPeriod, unsigned long highPeriod)
{
  _togglePeriods[0] = lowPeriod;
  _togglePeriods[1] = highPeriod;
  if (_startState == LOW)
  {
    _togglePeriodIndex = 0;
  }
  else
  {
    _togglePeriodIndex = 1;
  }
	_startState = startState;
	_originalStartState = _startState;
	_currentState = _startState;
	_writeState();
	_toggleStartTime = millis();
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
  _togglePeriods[0] = lowPeriod;
  _togglePeriods[1] = highPeriod;
    if (_startState == LOW)
  {
    _togglePeriodIndex = 0;
  }
  else
  {
    _togglePeriodIndex = 1;
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
    startToggling(_originalStartState, _togglePeriods[0], _togglePeriods[1], _originalToggleCount);
  }
}

void PinToggle::update(callbackFunc func = nullptr)  //change state if period ended.  callback optional
{
  _currentTime = millis();
  if (_toggling)
  {
    if (_currentTime - _toggleStartTime >= _togglePeriods[_togglePeriodIndex])
    {
      _currentState = !_currentState;
      _writeState();
      _togglePeriodIndex++;
      _togglePeriodIndex %= 2;
      _toggleStartTime = _currentTime;
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
		 startToggling(_originalStartState, _togglePeriods[0], _togglePeriods[1]);
	 }
  }
  
    if (_bursting)
  {
    if (_currentTime - _burstStartTime >= _burstPeriods[_burstPeriodIndex])
	{
		_burstPeriodIndex++;
		_burstPeriodIndex %= 2;
		_burstStartTime = _currentTime;
		_toggling = !_toggling;
		
		if (_toggling)
		{
			_toggleStartTime = _currentTime;
		}
		else
		{
			_currentState = _interBurstState;
			_writeState();
		}		
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
    _togglePeriods[0] = newPeriod;
  }
}

void PinToggle::updateHighPeriod(unsigned long newPeriod)
{
  if (_toggling)
  {
    _togglePeriods[1] = newPeriod;
  }
}

void PinToggle::startBurstMode(unsigned long lowPeriod, unsigned long highPeriod, unsigned long burstOnPeriod, unsigned long burstOffPeriod, byte interBurstState)
{
	_togglePeriods[0] = lowPeriod;
	_togglePeriods[1] = highPeriod;
	_burstPeriods[0] = burstOffPeriod;
	_burstPeriods[1] = burstOnPeriod;
	_interBurstState = interBurstState;
	_bursting = true;
	_toggling = true;
	_currentState = LOW;
	_burstPeriodIndex = 0;
	_currentState = _interBurstState;
	_writeState();
	_toggleStartTime = millis();
}

	void PinToggle::stopBurstMode(byte stoppedBurstState)
	{
		_bursting = false;
		_toggling = false;
		_currentState = stoppedBurstState;
		_writeState();		
	}


