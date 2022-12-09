# Pseudorandom Number Generator

This is a pseudorandom number generator implemented using xorshift. Xorshift generators basically bitwise shift the number and xor that number with itself. Different chain of xorshifts can be used, i used 13 left, 17 right, 4 left shift implementation. 

There are different pseudorandom number generator implementations but since xorshift generators can be reverted, i also implemented get_prev() function which basically returns the previous random generated number. For this reason, I do not recommend using it for encryption since it is easily reverted.

This is almost identical to one that i implemented in my internship.

- Works only with unsigned 32 bits integer.
