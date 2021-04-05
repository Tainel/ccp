/// SOURCE - DOUBLY LINKED NODE
/** Source file for doubly linked node implementation. */
#ifndef __DLNODE_C__
#define __DLNODE_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/dlnode.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Dln dln_create(Ptr val, Dln prev, Dln next) {
  // Create new node
  Dln node = MALLOC(sizeof(struct _Dln));
  node->val = val, node->prev = prev, node->next = next;
  // Return new node
  return node;
}

void dln_delete(Dln node, Visit del) {
  // Free element if possible
  if (del)
    del(node->val);
  // Free the node
  free(node);
}

//_____________________________________________________________________________

#endif // __DLNODE_C__
