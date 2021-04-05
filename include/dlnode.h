/// HEADER - DOUBLY LINKED NODE
/** Header file for doubly linked node implementation. */
#ifndef __DLNODE_H__
#define __DLNODE_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "basics.h"
#include <stdlib.h>
#include <stdio.h>

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Type of linear traversal. */
typedef enum _Direction {
  L2R, R2L
} /** Linear traversal alias. */ Direction;

/** Doubly linked node struct. */
typedef struct _Dln {
  Ptr val; // data stored in node
  struct _Dln* prev, *next; // pointers to previous and next nodes
} /** Pointer to the doubly linked node. */ *Dln;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates a doubly linked node storing val and pointing to prev and next. */
Dln dln_create(Ptr val, Dln prev, Dln next);

/** Destroys node. */
void dln_delete(Dln node, Visit del);

//_____________________________________________________________________________

#endif // __DLNODE_H__
