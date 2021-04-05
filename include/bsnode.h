/// HEADER - BINARY SEARCH NODE
/** Header file for binary search node implementation. */
#ifndef __BSNODE_H__
#define __BSNODE_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "basics.h"
#include <stdlib.h>
#include <stdio.h>

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Binary search node structure. */
typedef struct _Bsn {
  Ptr val; // value stored in the node
  struct _Bsn* left, *right; // pointers to left and right child
  size_t height; // height of the node
} /** Pointer to the binary search node. */ *Bsn;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Determines if val is present in the rooted tree. */
bool bsn_search(Bsn root, Ptr val, Compare comp);

/** Returns the value in the given position of the rooted tree. */
Ptr bsn_index(Bsn root, size_t* counter, const size_t pos);

/** Inserts val into the rooted tree. If another element exists where val
 * should be, that element is removed. */
Bsn bsn_insert(Bsn root, Ptr val, Compare comp, Visit del, bool* updated);

/** Removes val from the rooted tree if it exists. */
Bsn bsn_remove(Bsn root, Ptr val, Compare comp, Visit del, bool* updated);

/** Traverses the rooted tree. */
Bsn bsn_traverse(Bsn root, Visit visit);

/** Creates a copy of the rooted tree. */
Bsn bsn_copy(Bsn root, Copy copy);

/** Reverses the rooted tree. */
Bsn bsn_reverse(Bsn root);

/** Destroys the rooted tree. */
void bsn_delete(Bsn root, Visit del);

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

/** Creates a binary search node of height one with given val. */
Bsn bsn_init(Ptr val);

/** Returns the height of the node */
size_t bsn_height(Bsn node);

/** Updates the height of the node from the height of its childs. */
Bsn bsn_upheight(Bsn node);

/** Rotates the rooted tree to the left. */
Bsn bsn_rotleft(Bsn root);

/** Rotates the rooted tree to the right. */
Bsn bsn_rotright(Bsn root);

/** Returns the balance factor of the rooted tree. */
size_t bsn_balfactor(Bsn root, bool* sgn);

/** Balances the rooted tree. */
Bsn bsn_balance(Bsn root);

/** Removes root from the rooted tree. */
Bsn bsn_remroot(Bsn root, Compare comp, Visit del);

//_____________________________________________________________________________

#endif // __BSNODE_H__

