#include "NoBounceButtons.h"

NoBounceButtons nbb;
unsigned char button;

void setup()
{
  Serial.begin(9600);
  button = nbb.create(0);
}

void loop()
{
    nbb.check();
    if (nbb.action(button)>0)
    {
      Serial.printf("Action=%d\n",nbb.action(button));
      nbb.reset(button);
    }
}
