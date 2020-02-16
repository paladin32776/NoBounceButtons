#include "Arduino.h"
#include "TimeRingBuffer.h"

#ifndef NOBOUNCEBUTTONS_H
#define NOBOUNCEBUTTONS_H

#define MAX_BUTTONS 16
#define DEBOUNCE_DELAY 50
#define MIN_HOLD_TIME 2000
#define MIN_HOLD_TIME_2 8000
#define DOUBLE_CLICK_TIME 300

#define TIMERINGBUFFER_CNT 6

#define NBB_CLICK 1
#define NBB_LONG_CLICK 2
#define NBB_EXTRA_LONG_CLICK 3
#define NBB_DOUBLE_CLICK 4

class NoBounceButtons
{
	private:
		unsigned char N = 0;
		unsigned char Pin[MAX_BUTTONS];
		bool ActiveLow[MAX_BUTTONS];
		unsigned char State[MAX_BUTTONS];          // current "official" state of the button
		bool StateChange[MAX_BUTTONS];
		// unsigned long LastStateTime[MAX_BUTTONS];  // last time the state changed
		TimeRingBuffer* LastStateTime[MAX_BUTTONS];  // last time the state changed
		unsigned char LastValue[MAX_BUTTONS];      // previous reading from the input pin
		unsigned long LastValueTime[MAX_BUTTONS] ;   	// last time the input pin reading changed
		unsigned char Action[MAX_BUTTONS];
  public:
    NoBounceButtons(); 											// default constructor
    char create(unsigned char pin); 				// create a new button and return id
		char create(unsigned char pin, bool activelow); 				// create a new button and return id
  	unsigned char action(unsigned char id);	// check if button has been pressed
  	void reset(unsigned char id);						// reset button action
    void check();														// call in main loop; contains all the important code
};

#endif // NOBOUNCEBUTTONS_H
