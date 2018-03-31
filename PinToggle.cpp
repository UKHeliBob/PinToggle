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

void PinToggle::startToggling(byte startState, unsigned long lowPeriod, unsigned long highPeriod, unsigned int toggleCount = 0)  //set initial state, periods and count
{
	_originalStartState = startState;
	_originalToggleCount = toggleCount;
  if (toggleCount == 0)
  {
	  _counting = false;
  }
  else
  {
	_counting = true;
  }
  _toggleCount = toggleCount;
  _startState = startState;
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
  _currentState = _startState;
  _writeState();
  _startTime = millis();
  _toggling = true;
  _started = true;
}

void PinToggle::restartToggling()	//restart toggling with original parameters
{
	if (_started)
	{
	startToggling(_originalStartState, _periods[0], _periods[1], _originalToggleCount);
	}
}
	
void PinToggle::update()  //check whether period has ended and change state if true
{
  if (!_toggling)   //no need to update if not currently toggling
  {
    return;
  }
  _currentTime = millis();
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
	  if (_toggleCount == 0)
	  {
		  _toggling = false;
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
		_periods[0] = newPeriod;
		Serial.print("\nNew LOW period : ");
		Serial.println(_periods[0]);

	}
}

void PinToggle::updateHighPeriod(unsigned long newPeriod)
{
	if (_toggling)
	{
		_periods[1] = newPeriod;
		Serial.print("\nNew HIGH period : ");
		Serial.println(_periods[1]);

		}
}
