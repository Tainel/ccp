/// HEADER - SINGLY LINKED NODE
/** Header file for singly linked node implementation. */
#ifndef __SLNODE_H__
#define __SLNODE_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "basics.h"
#include <stdlib.h>
#include <stdio.h>

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Singly linked node struct. */
typedef struct _Sln {
  Ptr val; // data stored in node
  struct _Sln* next; // pointer to next node
} /** Pointer to the singly linked node. */ *Sln;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates a singly linked node storing val and pointing to next. */
Sln sln_create(Ptr val, Sln next);

/** Destroys node. */
void sln_delete(Sln node, Visit del);

//_____________________________________________________________________________

#endif // __SLNODE_H__
