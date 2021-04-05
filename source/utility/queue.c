/// SOURCE - QUEUE
/** Source file for queue implementation. */
#ifndef __QUEUE_C__
#define __QUEUE_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/queue.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Queue queue_create(void) {
  // Create empty queue
  Queue que = MALLOC(sizeof(struct _Queue));
  que->front = que->back = NULL, que->len = 0;
  // Returns queue
  return que;
}

Ptr queue_front(Queue que) {
  // Return front of queue
  return que->front->val;
}

Ptr queue_back(Queue que) {
  // Return back of queue
  return que->back->val;
}

size_t queue_len(Queue que) {
  // Return size of que
  return que->len;
}

bool queue_empty(Queue que) {
  // Return true if the front is null
  return que->front == NULL;
}

Queue queue_push(Queue que, Ptr val) {
  // Create new node
  Sln node = sln_create(val,NULL);
  // Update the back
  if (que->front)
    que->back->next = node;
  else
    que->front = node;
  que->back = node, ++que->len;
  // Return updated queue
  return que;
}

Queue queue_pop(Queue que, Visit del) {
  // Update the front
  Sln target = que->front;
  que->front = target->next, --que->len;
  // Free the node
  sln_delete(target,del);
  // Update the back
  if (!que->back)
    que->back = NULL;
  // Return updated queue
  return que;
}

Queue queue_traverse(Queue que, Visit visit) {
  // Traverse the queue from the front
  for (Sln node = que->front; node; visit(node->val), node = node->next);
  // Return the queue
  return que;
}

Queue queue_copy(Queue que, Copy copy) {
  // Create new queue
  Queue newQue = queue_create();
  // If the queue is empty, return the copy as is
  if (!que->front)
    return newQue;
  // Else, append each element to the new queue
  Sln curr = newQue->front = sln_create(copy(que->front->val),NULL);
  for (Sln node = que->front->next; node; node = node->next)
    curr->next = sln_create(copy(node->val),NULL), curr = curr->next;
  newQue->back = curr, newQue->len = que->len;
  // Return new queue
  return newQue;
}

Queue queue_reverse(Queue que) {
  // Connect each node with the previous one
  for (Sln node = que->front, prev = NULL, curr = NULL; node; )
    curr = node, node = node->next, curr->next = prev, prev = curr;
  // Update the front and back
  Ptr temp = que->front;
  que->front = que->back, que->back = temp;
  // Return reversed queue
  return que;
}

Queue queue_clear(Queue que, Visit del) {
  // Erase each node from the front
  for (Sln node = que->front, target = node; node; target = node)
    node = node->next, sln_delete(target,del);
  // Remove the front
  que->front = que->back = NULL, que->len = 0;
  // Return updated queue
  return que;
}

void queue_delete(Queue que, Visit del) {
  // Free the queue
  free(queue_clear(que,del));
}

//_____________________________________________________________________________

#endif // __QUEUE_C__
