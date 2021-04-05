/// SOURCE - STACK
/** Source file for stack implementation. */
#ifndef __STACK_C__
#define __STACK_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/stack.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Stack stack_create(void) {
  // Create empty stack
  Stack stk = MALLOC(sizeof(struct _Stack));
  stk->top = NULL, stk->len = 0;
  // Returns stack
  return stk;
}

Ptr stack_top(Stack stk) {
  // Return top of stack
  return stk->top->val;
}

size_t stack_len(Stack stk) {
  // Return size of stk
  return stk->len;
}

bool stack_empty(Stack stk) {
  // Return true if the top is null
  return stk->top == NULL;
}

Stack stack_push(Stack stk, Ptr val) {
  // Create the node
  Sln node = sln_create(val,stk->top);
  // Update the top
  stk->top = node, ++stk->len;
  // Return updated stack
  return stk;
}

Stack stack_pop(Stack stk, Visit del) {
  // Update the top
  Sln target = stk->top;
  stk->top = target->next, --stk->len;
  // Free the node
  sln_delete(target,del);
  // Return updated stack
  return stk;
}

Stack stack_traverse(Stack stk, Visit visit) {
  // Traverse the stack from the top
  for (Sln node = stk->top; node; visit(node->val), node = node->next);
  // Return the stack
  return stk;
}

Stack stack_copy(Stack stk, Copy copy) {
  // Create new stack
  Stack newStk = stack_create();
  // If the stack is empty, return the copy as is
  if (!stk->top)
    return newStk;
  // Else, append each element to the new stack
  newStk->top = sln_create(copy(stk->top->val),NULL), newStk->len = stk->len;
  for (Sln node = stk->top->next, curr = newStk->top; node; node = node->next)
    curr->next = sln_create(copy(node->val),NULL), curr = curr->next;
  // Return new stack
  return newStk;
}

Stack stack_reverse(Stack stk) {
  // Connect each node with the previous one
  Sln curr = NULL;
  for (Sln node = stk->top, prev = NULL; node; )
    curr = node, node = node->next, curr->next = prev, prev = curr;
  // Update the top
  stk->top = curr;
  // Return rotated stack
  return stk;
}

Stack stack_clear(Stack stk, Visit del) {
  // Erase each node from the top
  for (Sln node = stk->top, target = node; node; target = node)
    node = node->next, sln_delete(target,del);
  // Remove the top
  stk->top = NULL, stk->len = 0;
  // Return updated stack
  return stk;
}

void stack_delete(Stack stk, Visit del) {
  // Free the stack
  free(stack_clear(stk,del));
}

//_____________________________________________________________________________

#endif // __STACK_C__
