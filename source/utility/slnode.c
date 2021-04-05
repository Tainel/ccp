/// SOURCE - SINGLY LINKED NODE
/** Source file for singly linked node implementation. */
#ifndef __SLNODE_C__
#define __SLNODE_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/slnode.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Sln sln_create(Ptr val, Sln next) {
  // Create new node
  Sln node = MALLOC(sizeof(struct _Sln));
  node->val = val, node->next = next;
  // Return new node
  return node;
}

void sln_delete(Sln node, Visit del) {
  // Free element if possible
  if (del)
    del(node->val);
  // Free the node
  free(node);
}

//_____________________________________________________________________________

#endif // __SLNODE_C__
