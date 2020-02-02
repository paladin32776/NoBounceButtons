#include "TimeRingBuffer.h"

TimeRingBuffer::TimeRingBuffer(unsigned char _n)
{
  if (N<=MAX_TIMERING)
    N = _n;
  else
    N = MAX_TIMERING;
  for (n=0;n<N;n++)
    TRB[0] = 0;
  n=0;
}

void TimeRingBuffer::push(unsigned long _time)
{
  if (++n==N)
    n=0;
  TRB[n] = _time;
}

unsigned long TimeRingBuffer::get(unsigned char _n)
{
  if (_n>=N)
    return 0;
  if (n<_n)
    return TRB[N-(_n-n)];
  else
    return TRB[n-_n];
}

unsigned long TimeRingBuffer::delta(unsigned char _n)
{
  if (_n+1>=N)
    return 0;
  return get(_n)-get(_n+1);
}

bool TimeRingBuffer::delta_in(unsigned char _n, unsigned long dmin, unsigned long dmax)
{
  return delta_in(_n, dmin, dmax, false);
}

bool TimeRingBuffer::delta_in(unsigned char _n, unsigned long dmin, unsigned long dmax, bool include_boundaries)
{
  unsigned long d = delta(_n);
  return (d>dmin && d<dmax) || (include_boundaries && d>=dmin && d<=dmax);
}
