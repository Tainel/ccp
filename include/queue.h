/// HEADER - QUEUE
/** Header file for queue implementation. */
#ifndef __QUEUE_H__
#define __QUEUE_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "slnode.h"

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Queue struct. */
typedef struct _Queue {
  Sln front, back; // pointers to the front and back of the queue
  size_t len; // length of the queue
} /** Pointer to the queue. */ *Queue;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates an empty queue. */
Queue queue_create(void);

/** Returns the element at the front of non-empty que. */
Ptr queue_front(Queue que);

/** Returns the element at the back of non-empty que. */
Ptr queue_back(Queue que);

/** Returns que's length. */
size_t queue_len(Queue que);

/** Checks if que is empty. */
bool queue_empty(Queue que);

/** Pushes an element val to que. */
Queue queue_push(Queue que, Ptr val);

/** Pops an element from non-empty que. */
Queue queue_pop(Queue que, Visit del);

/** Traverses que */
Queue queue_traverse(Queue que, Visit visit);

/** Creates a copy of que. */
Queue queue_copy(Queue que, Copy copy);

/** Reverses que */
Queue queue_reverse(Queue que);

/** Empties que */
Queue queue_clear(Queue que, Visit del);

/** Destroys que */
void queue_delete(Queue que, Visit del);

//_____________________________________________________________________________

#endif // __QUEUE_H__
