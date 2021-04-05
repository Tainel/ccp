/// HEADER - BINARY SEARCH TREE
/** Header file for binary search tree implementation. */
#ifndef __BST_H__
#define __BST_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "bsnode.h"

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Binary search tree structure. */
typedef struct _Bst {
  Bsn root; // root of the tree
  Compare comp; // order function
  size_t size; // number of elements in the tree
} /** Pointer to the binary search tree. */ *Bst;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates an empty binary search tree. */
Bst bst_create(Compare comp);

/** Returns the number of nodes in bst. */
size_t bst_size(Bst bst);

/** Checks if bst is empty. */
bool bst_empty(Bst bst);

/** Determines if val is present in bst. */
bool bst_search(Bst bst, Ptr val);

/** Returns the minimum element in non-empty bst. */
Ptr bst_min(Bst bst);

/** Returns the maximum element in non-empty bst. */
Ptr bst_max(Bst bst);

/** Returns the element of bst in given position. */
Ptr bst_fetch(Bst bst, const size_t pos);

/** Inserts val into bst. If another element exists where val should be, that
 * element is removed. */
Bst bst_insert(Bst bst, Ptr val, Visit del);

/** Removes val from bst if it exists. */
Bst bst_remove(Bst bst, Ptr val, Visit del);

/** Traverse bst. */
Bst bst_traverse(Bst bst, Visit visit);

/** Creates a copy of bst. */
Bst bst_copy(Bst bst, Copy copy);

/** Reverses bst, replacing comp with the opposite order relation. */
Bst bst_reverse(Bst bst, Compare opposite);

/** Empties bst. */
Bst bst_clear(Bst bst, Visit del);

/** Destroys bst. */
void bst_delete(Bst bst, Visit del);

//_____________________________________________________________________________

#endif // __BST_H__
