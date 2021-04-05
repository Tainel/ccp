/// SOURCE - BINARY SEARCH NODE
/** Source file for binary search node implementation. */
#ifndef __BSNODE_C__
#define __BSNODE_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/bsnode.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

bool bsn_search(Bsn root, Ptr val, Compare comp) {
  // Search val if root exists
  bool found = false;
  if (root) {
    int c = comp(val,root->val);
    // If val is lesser than root, move left
    if (c < 0)
      found = bsn_search(root->left,val,comp);
    // If val is greater than root, move right
    else if (c > 0)
      found = bsn_search(root->right,val,comp);
    // If val is root, it was found
    else
      found = true;
  }
  // Return found value
  return found;
}

Ptr bsn_index(Bsn root, size_t* counter, const size_t pos) {
  // Initialize default value
  Ptr val = NULL;
  // Check corner cases
  if (!root)
    return val;
  // If the counter is smaller than the index, recur
  if (*counter <= pos) {
    // Recur to left subtree
    val = bsn_index(root->left,counter,pos);
    // Check if current position is the searched one
    if (++(*counter) == pos+1)
      val = root->val;
    // Recur right
    else if (*counter <= pos)
      val = bsn_index(root->right,counter,pos);
  }
  // Return found value
  return val;
}

Bsn bsn_insert(Bsn root, Ptr val, Compare comp, Visit del, bool* updated) {
  // If the tree is empty, initialize root
  if (!root) {
    *updated = true;
    // Return new root
    return bsn_init(val);
  }
  // Else, search where to place it
  int c = comp(val,root->val);
  // If val is lesser than root, move left
  if (c < 0)
    root->left = bsn_insert(root->left,val,comp,del,updated);
  // If val is greater than root, move right
  else if (c > 0)
    root->right = bsn_insert(root->right,val,comp,del,updated);
  // If val is the root value, replace it with the original
  else {
    root->val = ((del) ? (del(root->val), val) : val), *updated = false;
    // Return the balanced tree
    return root;
  }
  // Return the tree after updating the height and balancing it
  return (*updated) ? bsn_balance(bsn_upheight(root)) : root;
}

Bsn bsn_remove(Bsn root, Ptr val, Compare comp, Visit del, bool* updated) {
  // If the tree is empty, val cannot be removed
  if (!root) {
    *updated = false;
    // Return to previous calls withou updating the tree
    return root;
  }
  // Else, search where it could be
  int c = comp(val,root->val);
  // If val is lesser than root, move left
  if (c < 0)
    root->left = bsn_remove(root->left,val,comp,del,updated);
  // If val is greater than root, move right
  else if (c > 0)
    root->right = bsn_remove(root->right,val,comp,del,updated);
  // If val is the current value, remove the root
  else
    root = bsn_remroot(root,comp,del), *updated = true;
  // Return the tree after updating the height and balancing if necessary
  return (*updated) ? bsn_balance(bsn_upheight(root)) : root;
}

Bsn bsn_traverse(Bsn root, Visit visit) {
  // If root exists, traverse the tree as in inorder DFS
  if (root) {
    // Recur left
    bsn_traverse(root->left,visit);
    // Visit root
    visit(root->val);
    // Recur right
    bsn_traverse(root->right,visit);
  }
  // Return the tree
  return root;
}

Bsn bsn_copy(Bsn root, Copy copy) {
  // Create the new root
  Bsn newNode = NULL;
  // If root exists, copy the root and child subtrees recursively
  if (root) {
    // Copy the root and subtrees recursively
    newNode = bsn_init(copy(root->val)), newNode->height = root->height;
    newNode->left = bsn_copy(root->left,copy);
    newNode->right = bsn_copy(root->right,copy);
  }
  // Return the copy
  return newNode;
}

Bsn bsn_reverse(Bsn root) {
  // If root exists, reverse and swap the child subtrees
  if (root) {
    bsn_reverse(root->left), bsn_reverse(root->right);
    Ptr temp = root->left;
    root->left = root->right, root->right = temp;
  }
  // Return reversed tree
  return root;
}

void bsn_delete(Bsn root, Visit del) {
  // If root exists, free the child subtrees and the value in root
  if (root) {
    bsn_delete(root->left,del), bsn_delete(root->right,del);
    if (del)
      del(root->val);
    // Free the root itself
    free(root);
  }
}

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

Bsn bsn_init(Ptr val) {
  // Allocate memory for the node
  Bsn node = MALLOC(sizeof(struct _Bsn));
  // Initialize the fields
  node->val = val, node->left = node->right = NULL, node->height = 1;
  // Return the new node
  return node;
}

size_t bsn_height(Bsn node) {
  // Return the height of the node
  return (node) ? node->height : 0;
}

Bsn bsn_upheight(Bsn node) {
  // If root doesn't exist, it has no height
  if (!node)
    return node;
  // Else, height is one plus maximun height of childs
  size_t hl = bsn_height(node->left), hr = bsn_height(node->right);
  // Update the height
  node->height = (1+((hl<hr)?hr:hl));
  // Return updated node
  return node;
}

Bsn bsn_rotleft(Bsn root) {
  // Create roots
  Bsn newRoot = root->right, midGrand = newRoot->left;
  // Rotate left
  newRoot->left = root, root->right = midGrand;
  // Update the heights
  bsn_upheight(root), bsn_upheight(newRoot);
  // Return the new root
  return newRoot;
}

Bsn bsn_rotright(Bsn root) {
  // Create roots
  Bsn newRoot = root->left, midGrand = newRoot->right;
  // Rotate right
  newRoot->right = root, root->left = midGrand;
  // Update the heights
  bsn_upheight(root), bsn_upheight(newRoot);
  // Return the new root
  return newRoot;
}

size_t bsn_balfactor(Bsn root, bool* sgn) {
  // If the root doesn't exist, the balance factor is zero
  if (!root) {
    *sgn = false;
    return 0;
  }
  // Else, calculate and return the balance factor of the tree
  size_t hl = bsn_height(root->left), hr = bsn_height(root->right);
  return (hl > hr) ? (*sgn = true, hl-hr) : (*sgn = false, hr-hl);
}

Bsn bsn_balance(Bsn root) {
  // If root doesn't exist, nothing is done
  if (!root)
    return root;
  // Calculate the balance factor
  bool sgn;
  size_t bal = bsn_balfactor(root,&sgn);
  // If the tree is not balanced, there are 4 cases
  if (sgn && bal > 1) {
    bal = bsn_balfactor(root->left,&sgn);
    // Case LL, do R rotation
    if (sgn || !bal)
      root = bsn_rotright(root);
    // Case LR, do double rotation LR
    else
      root->left = bsn_rotleft(root->left), root = bsn_rotright(root);
  }
  else if (!sgn && bal > 1) {
    bal = bsn_balfactor(root->right,&sgn);
    // Case RR, do L rotation
    if (!sgn)
      root = bsn_rotleft(root);
    // Case RL, do double rotation RL
    else
      root->right = bsn_rotright(root->right), root = bsn_rotleft(root);
  }
  // Return updated tree
  return root;
}

Bsn bsn_remroot(Bsn root, Compare comp, Visit del) {
  // Free the value stored in root
  if (del)
    del(root->val);
  // If root has no child, simply remove it
  if (!root->left && !root->right)
    free(root), root = NULL;
  // Else, if root has at most one child, replace root with said child
  else if (!root->left || !root->right) {
    Bsn temp = (root->left) ? root->left : root->right;
    *root = *temp;
    // Free the structure
    free(temp);
  }
  // Else, place the next element as the new root
  else {
    // Move to the next element
    Bsn newRoot;
    for (newRoot = root->right; newRoot->left; newRoot = newRoot->left);
    // Place the new value inside root
    root->val = newRoot->val;
    // Search and remove the new root, and rebalance the tree if needed
    bool updated;
    root->right = bsn_remove(root->right,root->val,comp,NULL,&updated);
  }
  // Return updated tree
  return root;
}

//_____________________________________________________________________________

#endif // __BSNODE_C__
