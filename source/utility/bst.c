/// SOURCE - BINARY SEARCH TREE
/** Source file for binary search tree implementation. */
#ifndef __BST_C__
#define __BST_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/bst.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Bst bst_create(Compare comp) {
  // Allocate memory for the structure
  Bst bst = MALLOC(sizeof(struct _Bst));
  // Initialize the tree
  bst->root = NULL, bst->comp = comp, bst->size = 0;
  // Return the empty tree
  return bst;
}

size_t bst_size(Bst bst) {
  // Return the size of bst
  return bst->size;
}

bool bst_empty(Bst bst) {
  // Return true if the root doesn't exist
  return bst->root == NULL;
}

bool bst_search(Bst bst, Ptr val) {
  // Return true if val is found recursively
  return bsn_search(bst->root,val,bst->comp);
}

Ptr bst_min(Bst bst) {
  // Search the minimum element in the tree
  Bsn node;
  for (node = bst->root; node->left; node = node->left);
  // Return the minimum value
  return node->val;
}

Ptr bst_max(Bst bst) {
  // Search the maximum element in the tree
  Bsn node;
  for (node = bst->root; node->right; node = node->right);
  // Return the maximum value
  return node->val;
}

Ptr bst_fetch(Bst bst, const size_t pos) {
  // Initialize the counter
  size_t counter = 0;
  // Search the element in given position recursively and return it
  return bsn_index(bst->root,&counter,pos);
}

Bst bst_insert(Bst bst, Ptr val, Visit del) {
  // Insert val going down the tree recursively
  bool updated;
  bst->root = bsn_insert(bst->root,val,bst->comp,del,&updated);
  if (updated)
    ++bst->size;
  // Return updated tree
  return bst;
}

Bst bst_remove(Bst bst, Ptr val, Visit del) {
  // Remove val going down the tree recursively
  bool updated;
  bst->root = bsn_remove(bst->root,val,bst->comp,del,&updated);
  if (updated)
    --bst->size;
  // Return updated tree
  return bst;
}

Bst bst_traverse(Bst bst, Visit visit) {
  // Traverse the tree recursively as in inorder DFS
  bsn_traverse(bst->root,visit);
  // Return the tree
  return bst;
}

Bst bst_copy(Bst bst, Copy copy) {
  // Create the new tree
  Bst newBst = bst_create(bst->comp);
  // Copy each node recursively
  newBst->root = bsn_copy(bst->root,copy), newBst->size = bst->size;
  // Return the new tree
  return newBst;
}

Bst bst_reverse(Bst bst, Compare opposite) {
  // Reverse from root recursively
  bst->root = bsn_reverse(bst->root);
  // Replace the order function
  bst->comp = opposite;
  // Return reversed tree
  return bst;
}

Bst bst_clear(Bst bst, Visit del) {
  // Delete each node recursively
  bsn_delete(bst->root,del);
  // Initialize the fields
  bst->root = NULL, bst->size = 0;
  // Return empty tree
  return bst;
}

void bst_delete(Bst bst, Visit del) {
  // Delete each node recursively
  bsn_delete(bst->root,del);
  // Destroy the structure
  free(bst);
}

//_____________________________________________________________________________

#endif // __BST_C__
