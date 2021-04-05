/// HEADER - NUMERIC
/** Header file for prime number functions. */
#ifndef __PRIMES_H__
#define __PRIMES_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include <stdbool.h>

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Checks if n is prime. */
bool prime_check(const unsigned long long n);

/** Returns smallest prime greater than or equal to n, or 0 if overflow. */
unsigned long long prime_next(const unsigned long long n);

//_____________________________________________________________________________

#endif // __PRIMES_H__
