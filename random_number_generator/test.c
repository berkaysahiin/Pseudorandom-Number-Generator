#include <stdio.h>
#include "random_number_generator.h"

int main()
{
  uint32_t seed = 1239131;

  for(int i = 0; i < 100000; ++i) {
    uint32_t next = xor_shift(seed) % 100;
    uint32_t next_next = xor_shift(next);
    uint32_t prev_to_next = revert(next_next) % 100;

    if(next != prev_to_next) {
      printf("failed test. next:%u, prev_to_next:%u\n", next, prev_to_next);
      return -1;
    }

    seed = next;
  }

  random_number_generator rng = init(861762);
  for(int i = 0; i < 100000; i++) {
    uint32_t next = get_next_range(&rng, 1000);
    get_next(&rng);
    uint32_t prev = get_prev_range(&rng, 1000);
    if(prev != next) {
      fprintf(stderr, "Failed to revert");
      return -1;
    }
  }
} 

