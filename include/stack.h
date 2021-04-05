/// HEADER - STACK
/** Header file for stack implementation. */
#ifndef __STACK_H__
#define __STACK_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "slnode.h"

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Stack struct. */
typedef struct _Stack {
  Sln top; // pointer to the top of the stack
  size_t len; // length of the stack
} /** Pointer to the stack. */ *Stack;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates an empty stack. */
Stack stack_create(void);

/** Returns the element at the top of non-empty stk. */
Ptr stack_top(Stack stk);

/** Returns stk's length. */
size_t stack_len(Stack stk);

/** Checks if stk is empty. */
bool stack_empty(Stack stk);

/** Pushes an element val to stk. */
Stack stack_push(Stack stk, Ptr val);

/** Pops an element from non-empty stk. */
Stack stack_pop(Stack stk, Visit del);

/** Traverses stk */
Stack stack_traverse(Stack stk, Visit visit);

/** Creates a copy of stk. */
Stack stack_copy(Stack stk, Copy copy);

/** Reverses stk */
Stack stack_reverse(Stack stk);

/** Empties stk */
Stack stack_clear(Stack stk, Visit del);

/** Destroys stk */
void stack_delete(Stack stk, Visit del);

//_____________________________________________________________________________

#endif // __STACK_H__
