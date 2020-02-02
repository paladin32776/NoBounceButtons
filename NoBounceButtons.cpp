#include "NoBounceButtons.h"
#include "limits.h"

NoBounceButtons::NoBounceButtons() // default constructor
{
}

char NoBounceButtons::create(unsigned char pin)  // create a new button
{
  create(pin, true);
}

char NoBounceButtons::create(unsigned char pin, bool activelow)  // create a new button
{
  if (N<MAX_BUTTONS)
  {
    pinMode(pin,INPUT_PULLUP);
    Pin[N] = pin;    // pin to which button is connected
    ActiveLow[N] = activelow;
    LastValue[N] = HIGH;       // last value of the pin before it was toggled
    LastValueTime[N] = 0;      // last time the pin was toggled
    // LastStateTime[N] = 0;      // last time the "official" state was changed
    LastStateTime[N] = new TimeRingBuffer(TIMERINGBUFFER_CNT);
    State[N] = LOW;           // current "official" state of the button
    StateChange[N] = false;
    Action[N] = 0;         // button action state variable

    return N++;  // Return N, and then only increase it by one
                 // (so the value before the increase gets returned)
  }
  else
    return -1;
}

unsigned char NoBounceButtons::action(unsigned char id)  // check if button has been pressed
{
  return Action[id];
}


void NoBounceButtons::reset(unsigned char id)  // reset button action
{
  Action[id] = 0;
}


void NoBounceButtons::check()
{
  int Value;
  unsigned long Time;
  for (unsigned int id=0; id<N; id++)
  {
    // togglebutton read and debounce code
    Value = (digitalRead(Pin[id]) != ActiveLow[id]);
    Time = millis();
    // Detect a change at the pin:
    if (Value != LastValue[id])
      LastValueTime[id] = Time;
    LastValue[id] = Value;
    // If last change/slope is further in the past than a pre-defined time span,
    // and the current value differs from the "official" state:
    if ((Time - LastValueTime[id]) > DEBOUNCE_DELAY && Value != State[id])
    {
      State[id] = Value;  // make the value the "official" state
      LastStateTime[id]->push(Time); // push time to last state change time
      StateChange[id] = true;
    }

    if ((State[id] == LOW) && (Time-LastStateTime[id]->get(0)>DOUBLE_CLICK_TIME) && StateChange[id])
    {
      if (LastStateTime[id]->delta_in(0, 0, MIN_HOLD_TIME) && LastStateTime[id]->delta_in(1, DOUBLE_CLICK_TIME, ULONG_MAX))
            Action[id] = 1; // Regular click
      else if (LastStateTime[id]->delta_in(0, 0, MIN_HOLD_TIME) && LastStateTime[id]->delta_in(1, 0, DOUBLE_CLICK_TIME) && LastStateTime[id]->delta_in(2, 0, MIN_HOLD_TIME))
            Action[id] = 4; // Double-click
      else if (LastStateTime[id]->delta_in(0, MIN_HOLD_TIME, MIN_HOLD_TIME_2) && LastStateTime[id]->delta_in(1, DOUBLE_CLICK_TIME, ULONG_MAX))
            Action[id] = 2; // Long click
      else if (LastStateTime[id]->delta_in(0, MIN_HOLD_TIME_2, ULONG_MAX) && LastStateTime[id]->delta_in(1, DOUBLE_CLICK_TIME, ULONG_MAX))
            Action[id] = 3; // Extra long click

      StateChange[id] = false;
    }
  }
}
