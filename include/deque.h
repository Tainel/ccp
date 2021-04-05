/// HEADER - DEQUE
/** Header file for deque implementation. */
#ifndef __DEQUE_H__
#define __DEQUE_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "dlnode.h"

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Deque struct. */
typedef struct _Deque {
  Dln front, back; // pointers to the front and back of the deque
  size_t len; // length of the deque
} /** Pointer to the deque. */ *Deque;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates an empty deque. */
Deque deque_create(void);

/** Returns the element at the front of non-empty deq. */
Ptr deque_front(Deque que);

/** Returns the element at the back of non-empty deq. */
Ptr deque_back(Deque que);

/** Returns deq's length. */
size_t deque_len(Deque deq);

/** Checks if deq is empty. */
bool deque_empty(Deque deq);

/** Pushes an element val to the front of deq. */
Deque deque_pushfront(Deque deq, Ptr val);

/** Pushes an element val to the back of deq. */
Deque deque_pushback(Deque deq, Ptr val);

/** Pops the element from the front of non-empty deq. */
Deque deque_popfront(Deque deq, Visit del);

/** Pops the element from the back of non-empty deq. */
Deque deque_popback(Deque deq, Visit del);

/** Traverses deq in the given direction dir. */
Deque deque_traverse(Deque deq, Visit visit, const Direction dir);

/** Returns a copy of deq. */
Deque deque_copy(Deque deq, Copy copy);

/** Reverses deq. */
Deque deque_reverse(Deque deq);

/** Empties deq. */
Deque deque_clear(Deque deq, Visit del);

/** Destroys deq. */
void deque_delete(Deque deq, Visit del);

//_____________________________________________________________________________

#endif // __DEQUE_H__
