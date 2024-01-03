## Pseudorandom Number Generator (Xorshift)

This pseudorandom number generator (PRNG) is implemented using the xorshift algorithm. Xorshift generators operate by bitwise shifting a number and then performing an exclusive OR (XOR) operation on that number with itself. In this specific implementation, a chain of xorshifts is applied: 13 left shifts, 17 right shifts, and 4 left shifts.

## Usage
The generator is designed to work with unsigned 32-bit integers. To generate a new pseudorandom number, simply call the next() function. Additionally, a get_prev() function is provided, allowing retrieval of the previously generated random number.

```C
#include "random_number_generator.h"

uint32_t seed = 1239131;
uint32_t next = xor_shift(seed) 
uint32_t prev_to_next = revert(next) // 1239131


```
  
## Recommendation
While this xorshift-based PRNG is suitable for various non-cryptographic applications, such as simulations or game development, it is crucial to understand its limitations. Avoid using this generator for cryptographic purposes where the reversibility of the sequence may pose a security risk.

Feel free to adapt and use this PRNG according to your needs, keeping in mind its intended use cases and limitations.
