/// SOURCE - RANDOM
/** Source file for a 32-bit Mersenne Twister pseudorandom generator. */
#ifndef __RANDOM_C__
#define __RANDOM_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/random.h"
#include <time.h>

//_____________________________________________________________________________

// ------ MACROS ------ //

/* Degree of recurrence. */
#ifndef N
#define N ((size_t)624)
#endif // N

/** Offset used in the recurrence. */
#ifndef M
#define M ((size_t)397)
#endif // M

/** Most significants bits. */
#ifndef UM
#define UM ((uint32_t)0x80000000)
#endif // UM

/** Least significant bits. */
#ifndef LM
#define LM ((uint32_t)0x7fffffff)
#endif // LM

//_____________________________________________________________________________

// ------ VARIABLES ------ //

/** Array of state vector. */
static uint32_t mt[N];

/** Index of state vector. */
static size_t mti = N+1;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

void random_seed(const uint32_t seed) {
  // Initialize the state vector
  mt[0] = seed;
  for (mti = 1; mti < N; ++mti)
    mt[mti] = 1812433253*(mt[mti-1]^(mt[mti-1]>>30))+(uint32_t)mti;
}

uint32_t random_int(void) {
  // Initialize values
  uint32_t y;
  static uint32_t mat[2] = {0, 0x9908b0df};
  // Generate N words
  if (mti >= N) {
    // Initialize state vector with good enough seed if necessary
    if (mti == N+1)
      random_seed((uint32_t)time(NULL));
    // Modify the state vector accordingly
    for (size_t i = 0; i < N-M; ++i)
      y = (mt[i]&UM)|(mt[i+1]&LM), mt[i] = mt[i+M]^(y>>1)^mat[y&(uint32_t)1];
    for (size_t i = N-M; i < N-1; ++i) {
      y = (mt[i]&UM)|(mt[i+1]&LM);
      mt[i] = mt[i+(M-N)]^(y>>1)^mat[y&(uint32_t)1];
    }
    y = (mt[N-1]&UM)|(mt[0]&LM), mt[N-1] = mt[M-1]^(y>>1)^mat[y&(uint32_t)1];
    mti = 0;
  }
  y = mt[mti++];
  // Temper value
  y ^= (y>>11), y ^= (y<<7)&0x9d2c5680, y ^= (y<<15)&0xefc60000, y ^= (y>>18);
  // Return random value
  return y;
}

double random_real(void) {
  // Generate random integer in order to generate a real number
  uint32_t a = random_int()>>5, b = random_int()>>6;
  // Return random real
  return (a*67108864.+b)*(1./9007199254740992.);
}

//_____________________________________________________________________________

#endif // __RANDOM_C__
