# PinToggle
Arduino library to control pin toggling

The PinToggle library, what does it do and why ?

The PinToggle library, as its name suggests, lets you toggle Arduino pins on and
 off (HIGH/LOW) at a rate set within the sketch without needing to do deal with
timing within the sketch itself.  The number of milliseconds in each of the two
states is defined when starting the toggling as is the initial state of the pins
and the number of times that the pin should change state before toggling stops.  
The default is to toggle forever until stopped or paused by the main sketch.

Several miscellaneous functions are available in the library to pause and resume
 toggling, stop toggling, restart toggling and to read and write the state of
 the output pin whilst stopping the toggling, which digitalWrite() would not do.
 
 Other functions allow the sketch to determine whether the output pin is 
 currently being toggled and the number of toggles still to be done if toggle
 counting is happening.
 
 I hope that it goes without saying that none of the functions block the free
 running of the loop() function.  No timers are used by the library so it
 may be used with other code that uses the timers, such as the Servo 
 library and there will be no interaction between the two.  It is, however, 
 important that the PinToggle update() function is called frequently so that
 toggling is maintained at the defined rate.
 
So what is the library for ?

The library was written to provide a means to turn one or more outputs on and 
off (HIGH and LOW) at a user defined rate without the need for the main sketch 
to keep track of time in order to change the output state(s).  Typically the 
output would be to an LED in order to make it flash either alone or in 
conjunction with other LEDs.  

However, the library is not limited to doing this as the outputs may be 
connected to any device, such as relays, that need to be turned on and off at a 
fixed rate, perhaps for a defined number of times.  This may be used to attract
attention, perhaps in the case of an error, and the output pin could be used to
drive a small speaker or turn a tone generator on and off.

Note that the library is not intended to provide a high resolution high 
frequency output such as would be used to generate musical tones.  Rather it is
designed to provide a more general purpose output for use as required.  The 
maximum output frequency that can be generated is about 35kHz but this depends
on what else the main sketch is doing.

Functions available in the PinToggle library


PinToggle(byte pin);
Call this to name and create the PinToggle object.  
Parameters	:	pin		the pin number associated with the object

init();
Set up pinMode() for the pin

startToggling(byte state, unsigned long lowPeriod, unsigned long highPeriod, unsigned int toggleCount);
Start toggling the pin state
Parameters :	state 		the initial state of the pin (HIGH or LOW)
				lowPeriod 	the period in milliseconds that the pin should be LOW
				highPeriod 	the period in milliseconds that the pin should be HIGH
				toggleCount	the number of times the pin should toggle before stopping.  
							Set to 0 (the default) to disable the count and toggle continuously

restartToggling();
Restart toggling the pin state with the original parameters

update(funcName);
Update the state of the pin if the current period has ended.  Must be called frequently
Parameters	:	funcName	name of the function to be called when the update occurs
					the callback function returns the toggle count if it changes during the update

setOutputState(byte state);
Set the output state for the pin and stop toggling
Parameters	:	state		the state (HIGH or LOW) into which the pin should be put

getOutputState();	
Get the current state of the output

stopToggling(byte state);
Stop toggling and go into the specified state
Parameters:		state		the state into which the pin should be put (HIGH or LOW)

resumeToggling();
Resume toggling from where it was stopped

getTogglingState();
Get toggling state (true or false)

getToggleCount();
Get the number of toggles remaining

updateLowPeriod(unsigned long newPeriod);
Changes the LOW period of a toggling object
Parameters		newPeriod	the new value for the LOW period (milliseconds)

updateHighPeriod(unsigned long newPeriod);
Changes the HIGH period of a toggling object
Parameters		newPeriod	the new value for the HIGH period (milliseconds)






