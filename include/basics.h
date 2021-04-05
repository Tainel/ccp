/// HEADER - BASICS
/** Header file for basic macros and data types. */
#ifndef __BASICS_H__
#define __BASICS_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include <stdbool.h>

//_____________________________________________________________________________

// ------ MACROS ------ //

/** Returns minimun value between determined numbers a and b. */
#ifndef MIN
#define MIN(a,b) \
  (((a)<(b))?(a):(b))
#endif // MIN

/** Returns maximum value between determined numbers a and b. */
#ifndef MAX
#define MAX(a,b) \
  (((a)>(b))?(a):(b))
#endif // MAX

/** Swaps determined numbers a and b. */
#ifndef SWAP
#define SWAP(a,b) \
  ((a)^=(b),(b)^=(a),(a)^=(b))
#endif // SWAP

/** Prints fatal error message and exits execution. */
#ifndef FATAL
#define FATAL(error) \
  (fputs("FATAL ERROR: ",stderr),fputs(error,stderr),exit(EXIT_FAILURE))
#endif // FATAL

/** Allocates memory safely. */
#ifndef MALLOC
#define MALLOC(n) \
  (__extension__({Ptr _p=malloc(n);if(!(_p))FATAL("Can't malloc.\n");_p;}))
#endif // MALLOC

/** Reallocates memory safely. */
#ifndef REALLOC
#define REALLOC(p,n) \
  (__extension__({Ptr _p=realloc(p,n);if(!(_p))FATAL("Can't realloc.\n");_p;}))
#endif // REALLOC

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Data type for general pointers. */
typedef void* Ptr;

/** Visit pointer function type. */
typedef void (*Visit) (Ptr val);

/** Copy pointer function type. */
typedef Ptr (*Copy) (Ptr val);

/** Check condition pointer function type. */
typedef bool (*Condition) (Ptr val);

/** Check equality pointer funciton type. */
typedef bool (*Equals) (Ptr val1, Ptr val2);

/** Compare pointer funciton type. */
typedef int (*Compare) (Ptr val1, Ptr val2);

/** Hash pointer function type. */
typedef unsigned long long (*Hash) (Ptr key);

//_____________________________________________________________________________

#endif // __BASICS_H__
