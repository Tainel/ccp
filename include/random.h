/// HEADER - RANDOM
/** Header file for a 32-bit Mersenne Twister pseudorandom generator. */
#ifndef __RANDOM_H__
#define __RANDOM_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include <stdint.h>
#include <time.h>

//_____________________________________________________________________________

// ------ MACROS ------ //

/** Generates random 32-bit integer on range [a,b). */
#ifndef IRNDI
#define IRNDI(a,b) \
  (random_int()%((b)-(a))+(a))
#endif // IRNDI

/** Generates random real on range [a,b). */
#ifndef IRNDR
#define IRNDR(a,b) \
  (random_real()*((b)-(a))+(a))
#endif // IRNDR

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Initializes the state vector with a seed. */
void random_seed(const uint32_t seed);

/** Generates a random 32-bit natural number, that is, on range [0,2^32). */
uint32_t random_int(void);

/** Generates a random real on range [0,1). */
double random_real(void);

//_____________________________________________________________________________

#endif // __RANDOM_H__
