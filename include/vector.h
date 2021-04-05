/// HEADER - VECTOR
/** Header file for vector implementation. */
#ifndef __VECTOR_H__
#define __VECTOR_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "basics.h"
#include <stdlib.h>
#include <stdio.h>

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Vector struct. */
typedef struct _Vec {
  Ptr arr; // data array
  size_t len, cap; // size and capacity
} /** Pointer to the vector. */ *Vec;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates an empty vector with initialized capacity. */
Vec vec_create(const size_t maxLen);

/** Returns size of vec. */
size_t vec_len(Vec vec);

/** Checks if vec is empty. */
bool vec_empty(Vec vec);

/** Returns the element in given position pos of vec. */
Ptr vec_fetch(Vec vec, const size_t pos);

/** Modifies the element of vec in given position by a non-null val. */
Vec vec_modify(Vec vec, Ptr val, Visit del, const size_t pos);

/** Appends an element to vec. */
Vec vec_push(Vec vec, Ptr val);

/** Removes last element of vec. */
Vec vec_pop(Vec vec, Visit del);

/** Truncates vec in given position, and returns the remainder. */
Vec vec_div(Vec vec, const size_t pos);

/** Concatenates two vectors into the first one. */
Vec vec_cat(Vec vec, Vec cat, Copy copy);

/** Modifies vec applying mod to everyone of its elements. */
Vec vec_map(Vec vec, Copy mod);

/** Returns a copy of vec with all the elements that satisfy cond. */
Vec vec_filter(Vec vec, Copy copy, Condition cond);

/** Sorts vec. */
Vec vec_sort(Vec vec, Compare comp);

/** Traverses vec. */
Vec vec_traverse(Vec vec, Visit visit);

/** Returns a copy of vec. */
Vec vec_copy(Vec vec, Copy copy);

/** Reverses vec. */
Vec vec_reverse(Vec vec);

/** Sets exact capacity for vec. */
Vec vec_full(Vec vec);

/** Empties vec and sets its capacity. */
Vec vec_clear(Vec vec, Visit del, const size_t maxLen);

/** Destroys vec. */
void vec_delete(Vec vec, Visit del);

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

/** Sorts subvector in range [l,r]. */
Vec vec_subsort(Vec vec, Compare comp, const size_t l, const size_t r);

/** Merges two sorted halves in range [l,r]. */
Vec vec_merge(Vec vec, Compare comp, const size_t l, const size_t r);

//_____________________________________________________________________________

#endif // __VECTOR_H__
