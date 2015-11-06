#include "systick.h"
#include "framebuffer.h"

uint64_t Systick::_ticks = 0;

void Systick::tick()
{
  _ticks++;
}

uint64_t Systick::getTickCount()
{
  uint64_t ret = _ticks;
  return ret;
}
