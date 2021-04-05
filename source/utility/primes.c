/// SOURCE - NUMERIC
/** Source file for prime number functions. */
#ifndef __PRIMES_C__
#define __PRIMES_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/primes.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

bool prime_check(const unsigned long long n) {
  // Check corner cases
  if (n == 2 || n == 3)
    return true;
  if (n%2 == 0 || n%3 == 0 || n < 2)
    return false;
  // Check primality by trial division
  bool prime = true;
  unsigned long long i = 5, ii = 25, last = 0;
  while (ii <= n && ii > last && prime)
    prime = !(n%i == 0 || n%(i+2) == 0), last = ii, ii += 12*i+36, i += 6;
  // Return answer
  return prime;
}

unsigned long long prime_next(const unsigned long long n) {
  // Check corner cases
  unsigned long long m = n;
  if (m < 2)
    return 2;
  if (prime_check(m))
    return m;
  unsigned long long i = m%6;
  if (i == 0 && ++i && prime_check(++m))
    return m;
  // Find next prime by trial division, ignoring multiples of 2 and 3
  if (i < 5)
    m += 5-i;
  bool found = false, overflow = m < n;
  for (i = 2; !found && !overflow; overflow = m < n)
    found = (prime_check(m)) ? true : (m += i, i = (i%4)+2, false);
  // Return closest prime
  return (!overflow) ? m : 0;
}

//_____________________________________________________________________________

#endif // __PRIMES_C__
