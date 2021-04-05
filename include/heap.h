/// HEADER - HEAP
/** Header file for heap implementation. */
#ifndef __HEAP_H__
#define __HEAP_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "basics.h"
#include <stdlib.h>
#include <stdio.h>

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Heap struct. */
typedef struct _Heap {
  Ptr data; // data array
  Compare comp; // priority function
  size_t size, cap; // size and capacity of the heap
} /** Pointer to the heap. */ *Heap;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates an empty heap with initialized capacity. */
Heap heap_create(Compare comp, const size_t maxSize);

/** Returns size of heap. */
size_t heap_size(Heap heap);

/** Checks if heap is empty. */
bool heap_empty(Heap heap);

/** Returns the element at the top of non-empty heap. */
Ptr heap_top(Heap heap);

/** Inserts val into heap. */
Heap heap_insert(Heap heap, Ptr val);

/** Removes the top of non-empty heap. */
Heap heap_pop(Heap heap, Visit del);

/** Creates a heap from given array of pointers. */
Heap heap_heapify(Ptr arr, Compare comp, const size_t size);

/** Replaces the priority function of heap for comp. */
Heap heap_reorder(Heap heap, Compare comp);

/** Traverses heap. */
Heap heap_traverse(Heap heap, Visit visit);

/** Creates a copy of heap. */
Heap heap_copy(Heap heap, Copy copy);

/** Sets exact capacity for heap. */
Heap heap_full(Heap heap);

/** Empties heap and sets its capacity. */
Heap heap_clear(Heap heap, Visit del, const size_t maxSize);

/** Destroys heap. */
void heap_delete(Heap heap, Visit del);

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

/** Sorts a pointer array into a heap data array. */
void heap_prioritize(Ptr arr, Compare comp, const size_t s, const size_t r);

//_____________________________________________________________________________

#endif // __HEAP_H__
