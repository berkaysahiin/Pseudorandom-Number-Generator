#include <stdint.h>

/* Macro definitions for bit manipulation */
#define SET_BIT(target, index) (target |= (1U << (index)))
#define CLEAR_BIT(target, index) (target &= ~(1U << (index)))

/* Random number generator structure */
typedef struct {
    uint32_t state;
} random_number_generator;

/* --------------PUBLIC-------------------*/
uint32_t get_next(random_number_generator* rng);
uint32_t get_next_range(random_number_generator* rng, int upper_bound);
uint32_t get_prev(random_number_generator* rng);
uint32_t get_prev_range(random_number_generator* rng, int upper_bound);
uint32_t xor_shift(uint32_t value);
uint32_t revert(uint32_t value);

/* --------------PRIVATE-------------------*/
uint32_t revert_bits_shift(uint32_t xorshiftedValue, int shift, int is_left);
void set_bit(uint32_t* target, int val, int index);
int get_bit(const uint32_t target, int index);
int xor(const int b1, const int b2);

/* --------------------------------------------------------------------------------- */

random_number_generator init(uint32_t seed) {
    random_number_generator rng = {
        .state = seed
    };
    return rng;
}

uint32_t get_next(random_number_generator* rng) {
    rng->state = xor_shift(rng->state);
    return rng->state;
}

uint32_t get_next_range(random_number_generator* rng, int upper_bound) {
    if (upper_bound <= 0) {
        return 0; 
    }
    return get_next(rng) % upper_bound;
}

uint32_t get_prev(random_number_generator* rng) {
    rng->state = revert(rng->state);
    return rng->state;
}

uint32_t get_prev_range(random_number_generator* rng, int upper_bound) {
    if (upper_bound <= 0) {
        return 0; 
    }
    return get_prev(rng) % upper_bound;
}

uint32_t xor_shift(uint32_t value) {
    value ^= value << 13;
    value ^= value >> 17;
    value ^= value << 4;
    return value;
}

uint32_t revert(uint32_t value) {
    value = revert_bits_shift(value, 4, 1);   // 4-bit left shift revert
    value = revert_bits_shift(value, 17, 0);  // 17-bit right shift revert
    value = revert_bits_shift(value, 13, 1);  // 13-bit left shift revert
    return value;
}

/**
 * @brief Reverts an arbitrary shift (left or right) by a specified number of bits.
 *
 * @param xorshiftedValue The value to revert.
 * @param shift The number of bits that were shifted.
 * @param is_left Boolean flag indicating if it was a left shift (1) or right shift (0).
 * @return The reverted value.
 */
uint32_t revert_bits_shift(uint32_t xorshiftedValue, int shift, int is_left) {
    uint32_t revertedValue = 0;

    if (is_left) {
      
        for (int i = 0; i < shift; i++) {
            set_bit(&revertedValue, get_bit(xorshiftedValue, i), i);
        }
      
        for (int i = shift; i < 32; i++) {
            set_bit(&revertedValue, xor(get_bit(revertedValue, i - shift), get_bit(xorshiftedValue, i)), i);
        }
    } else {
      
        for (int i = 32 - shift; i < 32; i++) {
            set_bit(&revertedValue, get_bit(xorshiftedValue, i), i);
        }

        for (int i = 0; i < 32 - shift; i++) {
            set_bit(&revertedValue, xor(get_bit(revertedValue, i + shift), get_bit(xorshiftedValue, i)), i);
        }
    }

    return revertedValue;
}

/* ------------------------- Bitwise Operations ---------------------------- */

inline void set_bit(uint32_t* target, int val, int index) {
    if (val == 1) {
        SET_BIT(*target, index);
    } else {
        CLEAR_BIT(*target, index);
    }
}

inline int get_bit(const uint32_t target, int index) {
    return (target & (1 << index)) != 0;
}

inline int xor(const int b1, const int b2) {
    return !(b1 == b2);
}
