/// SOURCE - DEQUE
/** Source file for deque implementation. */
#ifndef __DEQUE_C__
#define __DEQUE_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/deque.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Deque deque_create(void) {
  // Create empty deque
  Deque deq = MALLOC(sizeof(struct _Deque));
  deq->front = deq->back = NULL, deq->len = 0;
  // Returns deque
  return deq;
}

Ptr deque_front(Deque deq) {
  // Return front of deque
  return deq->front->val;
}

Ptr deque_back(Deque deq) {
  // Return back of deque
  return deq->back->val;
}

size_t deque_len(Deque deq) {
  // Return size of deq
  return deq->len;
}

bool deque_empty(Deque deq) {
  // Return true if the front is null
  return deq->front == NULL;
}

Deque deque_pushback(Deque deq, Ptr val) {
  // Create new node
  Dln node = dln_create(val,deq->back,NULL);
  // If deq is not empty, append to the back
  if (deq->back)
    deq->back->next = node;
  // Else, update front
  else
    deq->front = node;
  // Update back
  deq->back = node, ++deq->len;
  // Return updated deque
  return deq;
}

Deque deque_pushfront(Deque deq, Ptr val) {
  // Create new node
  Dln node = dln_create(val,NULL,deq->front);
  // If deq is not empty, prepend to the front
  if (deq->front)
    deq->front->prev = node;
  // Else, update back
  else
    deq->back = node;
  // Update front
  deq->front = node, ++deq->len;
  // Return updated deque
  return deq;
}

Deque deque_popback(Deque deq, Visit del) {
  // Update back
  Dln target = deq->back;
  deq->back = target->prev;
  // Free the node
  dln_delete(target,del), --deq->len, deq->back->next = NULL;
  // Check is deq is now empty
  if (!deq->back)
    deq->front = NULL;
  // Return updated deque
  return deq;
}

Deque deque_popfront(Deque deq, Visit del) {
  // Update front
  Dln target = deq->front;
  deq->front = target->next;
  // Free the node
  dln_delete(target,del), --deq->len, deq->front->prev = NULL;
  // Check is deq is now empty
  if (!deq->front)
    deq->back = NULL;
  // Return updated deque
  return deq;
}

Deque deque_traverse(Deque deq, Visit visit, const Direction dir) {
  // Traverse the deque in que specified direction
  switch (dir) {
    case L2R:
      for (Dln node = deq->front; node; visit(node->val), node = node->next);
      break;
    case R2L:
      for (Dln node = deq->back; node; visit(node->val), node = node->prev);
      break;
  }
  // Return the deque
  return deq;
}

Deque deque_copy(Deque deq, Copy copy) {
  // Create new deque
  Deque newDeq = deque_create();
  // If the deque is empty, return the copy as is
  if (!deq->front)
    return newDeq;
  // Else, append each element to the new deque
  Dln curr = newDeq->front = dln_create(copy(deq->front->val),NULL,NULL);
  for (Dln node = deq->front->next; node; node = node->next)
    curr->next = dln_create(copy(node->val),curr,NULL), curr = curr->next;
  newDeq->back = curr, newDeq->len = deq->len;
  // Return new deque
  return newDeq;
}

Deque deque_reverse(Deque deq) {
  // For each node, swap the pointers to their neighbours
  Ptr temp;
  for (Dln node = deq->front; node; node = node->prev)
    temp = node->prev, node->prev = node->next, node->next = temp;
  // Swap front and back
  temp = deq->front, deq->front = deq->back, deq->back = temp;
  // Return reversed deque
  return deq;
}

Deque deque_clear(Deque deq, Visit del) {
  // Erase each node from the front
  for (Dln node = deq->front, target = node; node; target = node)
    node = node->next, dln_delete(target,del);
  // Remove the front and back
  deq->front = deq->back = NULL, deq->len = 0;
  // Return updated deque
  return deq;
}

void deque_delete(Deque deq, Visit del) {
  // Free the deque
  free(deque_clear(deq,del));
}

//_____________________________________________________________________________

#endif // __DEQUE_C__
