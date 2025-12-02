#include "solution.hpp"
#define SOLUTION 1

#if SOLUTION
uint16_t checksum(const Blob &blob) {
  uint32_t acc = 0;
  for (auto value : blob) {
    acc += value;
  }

  uint32_t high = acc >> 16;
  uint32_t low = acc & 0xffff;
  acc = high + low;
  
  high = acc >> 16;
  low = acc & 0xffff;
  acc = high + low;
  return static_cast<uint16_t>(acc);
}

#else

uint16_t checksum(const Blob& blob) {
  uint16_t acc = 0;
  for (auto value : blob) {
    acc += value;
    acc += acc < value; // add carry
  }

  return acc;
}
#endif
