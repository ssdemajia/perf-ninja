#include "solution.hpp"
#include <intrin.h>
static int getSumOfDigits(int n) {
  int sum = 0;
  while (n != 0) {
    sum = sum + n % 10;
    n = n / 10;
  }
  return sum;
}

#define USE_OLD 0

#if USE_OLD
int solution(const hash_map_t *hash_map, const std::vector<int> &lookups) {
  int result = 0;

  for (int val : lookups) {
    if (hash_map->find(val))
    {
      result += getSumOfDigits(val);
    }
  }

  return result;
}
#else
int solution(const hash_map_t* hash_map, const std::vector<int>& lookups) {
  int result = 0;
  const int* hashPtr = hash_map->m_vector.data();
  int NumBuckets = hash_map->N_Buckets;
  for (int i = 0; i < lookups.size(); i++)
  {
    int val = lookups[i];
    //_mm_prefetch((char*) & lookups[i + 1], _MM_HINT_T0);
    //if (i + 1 < lookups.size())
    {
      _mm_prefetch((char*)(hashPtr + lookups[i + 1] % NumBuckets), _MM_HINT_T0);
    }
    if (hash_map->find(val))
    {
      result += getSumOfDigits(val);
    }
  }

  return result;
}
#endif
