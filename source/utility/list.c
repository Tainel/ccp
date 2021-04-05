/// SOURCE - LINKED LIST
/** Source file for linked list implementation. */
#ifndef __LIST_C__
#define __LIST_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/list.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

List list_create(void) {
  // Create empty list
  List list = MALLOC(sizeof(struct _List));
  list->first = list->last = NULL, list->len = 0;
  // Return empty list
  return list;
}

size_t list_len(List list) {
  // Return length of list
  return list->len;
}

bool list_empty(List list) {
  // Return true if list is empty
  return list->first == NULL;
}

Ptr list_fetch(List list, const size_t pos) {
  // Find element in given position
  Dln node = list->first;
  for (size_t i = pos; i; node = node->next, --i);
  // Return element
  return node->val;
}

List list_prepend(List list, Ptr val) {
  // Create new node
  Dln node = dln_create(val,NULL,list->first);
  // Prepend the node
  if (list->first)
    list->first = list->first->prev = node;
  else
    list->first = list->last = node;
  ++list->len;
  // Return updated list
  return list;
}

List list_append(List list, Ptr val) {
  // Create new node
  Dln node = dln_create(val,list->last,NULL);
  // Append the node
  if (list->last)
    list->last = list->last->next = node;
  else
    list->first = list->last = node;
  ++list->len;
  // Return updated list
  return list;
}

List list_insert(List list, Ptr val, const size_t pos) {
  // Check corner cases
  if (pos == 0)
    return list_prepend(list,val);
  if (pos == list->len)
    return list_append(list,val);
  // Search where to place the element
  Dln prev = list->first;
  for (size_t i = pos; --i; prev = prev->next);
  // Create the node and insert it
  Dln node = dln_create(val,prev,prev->next);
  prev->next = node, node->next->prev = node, ++list->len;
  // Return updated list
  return list;
}

List list_pop(List list, Visit del) {
  // Remove first node
  Dln target = list->first;
  list->first = target->next, dln_delete(target,del), --list->len;
  // Chech if now is empty
  if (!list->first)
    list->last = NULL;
  else
    list->first->prev = NULL;
  // Return updated list
  return list;
}

List list_eject(List list, Visit del) {
  // Remove last node
  Dln target = list->last;
  list->last = target->prev, dln_delete(target,del), --list->len;
  // Chech if now is empty
  if (!list->last)
    list->first = NULL;
  else
    list->last->next = NULL;
  // Return updated list
  return list;
}

List list_remove(List list, Visit del, const size_t pos) {
  // Check corner cases
  if (pos == 0)
    return list_pop(list,del);
  if (pos == list->len-1)
    return list_eject(list,del);
  // Search target node
  Dln target = list->first->next;
  for (size_t i = pos; --i; target = target->next);
  // Remove the node
  target->prev->next = target->next, target->next->prev = target->prev;
  dln_delete(target,del), --list->len;
  // Return updated list
  return list;
}

List list_modify(List list, Ptr val, Visit del, const size_t pos) {
  // Find node in given position
  Dln node = list->first;
  for (size_t i = pos; i; node = node->next, --i);
  // Change the content of the node
  if (del)
    del(node->val);
  node->val = val;
  // Return updated list
  return list;
}

List list_div(List list, size_t pos) {
  // Create remainder list
  List rest = list_create();
  // Check corner cases
  if (pos == 0) {
    Ptr temp = list->first;
    list->first = rest->first, rest->first = temp;
    temp = list->last, list->last = rest->last, rest->last = temp;
    list->len ^= rest->len, rest->len ^= list->len, list->len ^= rest->len;
    return rest;
  }
  if (pos == list->len)
    return rest;
  // Get beginning of remainder
  Dln node;
  size_t i = pos;
  for (node = list->first; i; node = node->next, --i);
  // Divide the list
  rest->len = list->len-i, list->len = i;
  rest->last = list->last, list->last = node->prev;
  list->last->next = node->prev = NULL, rest->first = node;
  // Return remainder list
  return rest;
}

List list_cat(List list, List cat, Copy copy) {
  // Append a copy of each element of cat to list
  for (Dln node = cat->first; node; node = node->next) {
    list->last = dln_create(copy(node->val),list->last,NULL), ++list->len;
    if (list->first)
      list->last->prev->next = list->last;
    else
      list->first = list->last;
  }
  // Return concatenated list
  return list;
}

List list_map(List list, Copy mod) {
  // Apply mod to every element
  for (Dln node = list->first; node; node = node->next)
    node->val = mod(node->val);
  // Return updated list
  return list;
}

List list_filter(List list, Copy copy, Condition cond) {
  // Create the new list
  List newList = list_create();
  // Append a copy of each element that satisfies cond
  for (Dln node = list->first; node; node = node->next)
    if (cond(node->val))
      list_append(newList,copy(node->val));
  // Return new list
  return newList;
}

List list_sort(List list, Compare comp) {
  // If the list has more than one element, sort it
  if (list->first != list->last) {
    // Find middle node
    Dln mid = list->first, end = mid->next;
    while (end && end->next)
      mid = mid->next, end = end->next->next;
    // Divide the list into two sublists
    List rem = list_create();
    rem->last = list->last, rem->first = mid->next, rem->first->prev = NULL;
    list->last = mid, list->last->next = NULL;
    // Sort both sublists and merge them
    list_merge(list_sort(list,comp),list_sort(rem,comp),comp);
  }
  // Return sorted list
  return list;
}

List list_traverse(List list, Visit visit, const Direction dir) {
  // Traverse the list in que specified direction
  switch (dir) {
    case L2R:
      for (Dln node = list->first; node; visit(node->val), node = node->next);
      break;
    case R2L:
      for (Dln node = list->last; node; visit(node->val), node = node->prev);
      break;
  }
  // Return the list
  return list;
}

List list_copy(List list, Copy copy) {
  // Create new list
  List newList = list_create();
  // If the list is empty, return the copy as is
  if (!list->first)
    return newList;
  // Else, append each element to the new list
  Dln curr = newList->first = dln_create(copy(list->first->val),NULL,NULL);
  for (Dln node = list->first->next; node; node = node->next)
    curr->next = dln_create(copy(node->val),curr,NULL), curr = curr->next;
  newList->last = curr, newList->len = list->len;
  // Return new list
  return newList;
}

List list_reverse(List list) {
  // For each node, swap the pointers to their neighbours
  Ptr temp;
  for (Dln node = list->first; node; node = node->prev)
    temp = node->prev, node->prev = node->next, node->next = temp;
  // Swap first and last
  temp = list->first, list->first = list->last, list->last = temp;
  // Return reversed list
  return list;
}

List list_clear(List list, Visit del) {
  // Erase each node from the start
  for (Dln node = list->first, target = node; node; target = node)
    node = node->next, dln_delete(target,del);
  // Remove the start and end
  list->first = list->last = NULL, list->len = 0;
  // Return updated list
  return list;
}

void list_delete(List list, Visit del) {
  // Clear the list
  for (Dln node = list->first, target = node; node; target = node)
    node = node->next, dln_delete(target,del);
  // Free the list
  free(list);
}

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

List list_merge(List list, List rem, Compare comp) {
  // Start to merge both lists
  Dln node1 = list->first, node2 = rem->first;
  while (node1 && node2) {
    // If first node is grater than the second one, place in after
    if (comp(node1->val, node2->val) >= 0) {
      // Connect accordingly
      Dln next = node2->next;
      node2->next = node1, node2->prev = node1->prev, node1->prev = node2;
      if (node2->prev)
        node2->prev->next = node2;
      else
        list->first = node2;
      // Move to the next node in rem
      node2 = next;
    }
    // Else, move to the next node in list
    else
      node1 = node1->next;
  }
  // If nodes remain in rem, append them at the end of list
  if (node2)
    list->last->next = node2, node2->prev = list->last, list->last = rem->last;
  // Free the second list once it's not needed anymore
  list->len += rem->len, free(rem);
  // Return merged list
  return list;
}

//_____________________________________________________________________________

#endif // __LIST_C__
