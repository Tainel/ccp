/// HEADER - LINKED LIST
/** Header file for linked list implementation. */
#ifndef __LIST_H__
#define __LIST_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "dlnode.h"

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Linked list struct. */
typedef struct _List {
  Dln first, last; // pointers to first and last nodes of the list
  size_t len; // length of the list
} /** Pointer to the list. */ *List;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates an empty linked list. */
List list_create(void);

/** Returns length of list. */
size_t list_len(List list);

/** Checks if list is empty. */
bool list_empty(List list);

/** Returns the element in position pos of list. */
Ptr list_fetch(List list, const size_t pos);

/** Prepends an element to list. */
List list_prepend(List list, Ptr val);

/** Appends an element to list. */
List list_append(List list, Ptr val);

/** Inserts an element to list in given position. */
List list_insert(List list, Ptr val, const size_t pos);

/** Removes the first element of non-empty list. */
List list_pop(List list, Visit del);

/** Removes the last element of non-empty list. */
List list_eject(List list, Visit del);

/** Removes an element from non-empty list on position. */
List list_remove(List list, Visit del, const size_t pos);

/** Modifies the element of list in given position. */
List list_modify(List list, Ptr val, Visit del, const size_t pos);

/** Truncates list in given position, and returns the remainder. */
List list_div(List list, const size_t pos);

/** Concatenates two lists into the first one. */
List list_cat(List list, List cat, Copy copy);

/** Modifies list applying mod to everyone of its elements. */
List list_map(List list, Copy mod);

/** Returns a copy of list with all the elements that satisfy cond. */
List list_filter(List list, Copy copy, Condition cond);

/** Sorts list. */
List list_sort(List list, Compare comp);

/** Traverses list in the given direction. */
List list_traverse(List list, Visit visit, const Direction dir);

/** Creates a copy of list. */
List list_copy(List list, Copy copy);

/** Reverses list. */
List list_reverse(List list);

/** Empties list. */
List list_clear(List list, Visit del);

/** Destroys list. */
void list_delete(List list, Visit del);

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

/** Merges two sorted lists into the first one, while still being sorted. The
 * second list is erased. */
List list_merge(List list, List rem, Compare comp);

//_____________________________________________________________________________

#endif // __LIST_H__
