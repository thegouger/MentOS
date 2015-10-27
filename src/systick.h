#pragma once

#include <cstdint>

class Systick
{
public:
  static void tick();
  static uint64_t getTickCount();

private:
  static uint64_t _ticks;
};
