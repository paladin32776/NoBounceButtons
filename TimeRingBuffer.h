#include "Arduino.h"

#ifndef TIMERINGBUFFER_H
#define TIMERINGBUFFER_H

#define MAX_TIMERING 6

class TimeRingBuffer
{
  private:
    unsigned char n;
    unsigned char N;
		unsigned long TRB[MAX_TIMERING];
	public:
		TimeRingBuffer(unsigned char _n);
		void push(unsigned long _time);
		unsigned long get(unsigned char _n);
    unsigned long delta(unsigned char _n);
    bool delta_in(unsigned char _n, unsigned long dmin, unsigned long dmax);
    bool delta_in(unsigned char _n, unsigned long dmin, unsigned long dmax, bool include_boundaries);
};

#endif // TIMERINGBUFFER_H
