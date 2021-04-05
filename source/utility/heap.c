/// SOURCE - HEAP
/** Source file for heap implementation. */
#ifndef __HEAP_C__
#define __HEAP_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/heap.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Heap heap_create(Compare comp, const size_t maxSize) {
  // Allocate memory for the structure
  Heap heap = MALLOC(sizeof(struct _Heap));
  // Initialize the heap
  heap->data = MALLOC(sizeof(Ptr)*(heap->cap=maxSize+1));
  ((Ptr*)heap->data)[0] = NULL, heap->comp = comp, heap->size = 0;
  // Return empty heap
  return heap;
}

size_t heap_size(Heap heap) {
  // Return size of heap
  return heap->size;
}

bool heap_empty(Heap heap) {
  // Return true if heap is empty
  return heap->size == 0;
}

Ptr heap_top(Heap heap) {
  // Return the element at the top of the heap
  return ((Ptr*)heap->data)[0];
}

Heap heap_insert(Heap heap, Ptr val) {
  // Expand capacity if necessary
  if (heap->size+1 == heap->cap)
    heap->data = REALLOC(heap->data,sizeof(Ptr)*(heap->cap*=2));
  // Place val at the end of array
  ((Ptr*)heap->data)[heap->size++] = val;
  ((Ptr*)heap->data)[heap->size] = NULL;
  // Swap with parent until the parent has higher priority or root is reached
  size_t i = heap->size-1, j = (i-1)>>1;
  while (i && heap->comp(((Ptr*)heap->data)[i],((Ptr*)heap->data)[j]) > 0) {
    Ptr temp = ((Ptr*)heap->data)[i];
    ((Ptr*)heap->data)[i] = ((Ptr*)heap->data)[j];
    ((Ptr*)heap->data)[j] = temp;
    i = j, j = (i-1)>>1;
  }
  // Return updated heap
  return heap;
}

Heap heap_pop(Heap heap, Visit del) {
  // Free the root
  if (del)
    del(((Ptr*)heap->data)[0]);
  // Move the last element to the root
  ((Ptr*)heap->data)[0] = ((Ptr*)heap->data)[--heap->size];
  ((Ptr*)heap->data)[heap->size] = NULL;
  // Place the root down the tree where it belongs
  bool placed = false;
  for (size_t i = 0, k; (i<<1)+1 < heap->size && !placed; ) {
    // Move to the child with higher priority
    k = (i<<1)+1;
    if (k+1 < heap->size)
      if (heap->comp(((Ptr*)heap->data)[k+1],((Ptr*)heap->data)[k]) > 0)
        ++k;
    // Determine if the node is well placed
    if (heap->comp(((Ptr*)heap->data)[i],((Ptr*)heap->data)[k]) >= 0)
      placed = true;
    else {
      Ptr temp = ((Ptr*)heap->data)[i];
      ((Ptr*)heap->data)[i] = ((Ptr*)heap->data)[k];
      ((Ptr*)heap->data)[k] = temp, i = k;
    }
  }
  // Return updated heap
  return (heap->size*2 < heap->cap) ? heap_full(heap) : heap;
}

Heap heap_heapify(Ptr arr, Compare comp, const size_t size) {
  // From the last no-leaf node climb the tree up to where it belongs
  for (size_t i = 0, idx = (size>>1)-1; i <= idx; ++i)
    heap_prioritize(arr,comp,size,idx-i);
  // Create the new heap
  Heap heap = MALLOC(sizeof(struct _Heap));
  arr = REALLOC(arr,sizeof(Ptr)*(heap->cap=size+1)), ((Ptr*)arr)[size] = NULL;
  heap->data = arr, heap->comp = comp, heap->size = size;
  // Return new heap
  return heap;
}

Heap heap_reorder(Heap heap, Compare comp) {
  // Apply heapify recursively with given comp
  for (size_t i = 0, idx = (heap->size>>1)-1; i <= idx; ++i)
    heap_prioritize(heap->data,comp,heap->size,idx-i);
  heap->comp = comp;
  // Return updated heap
  return heap;
}

Heap heap_traverse(Heap heap, Visit visit) {
  // Traverse the heap as in BFS
  for (size_t i = 0; i < heap->size; ++i)
    visit(((Ptr*)heap->data)[i]);
  // Return the heap
  return heap;
}

Heap heap_copy(Heap heap, Copy copy) {
  // Create new heap
  Heap newHeap = heap_create(heap->comp,heap->size);
  // Copy all elements to new heap
  for (size_t i = 0; i < heap->size; ++i)
    ((Ptr*)newHeap->data)[newHeap->size++] = copy(((Ptr*)heap->data)[i]);
  ((Ptr*)newHeap->data)[newHeap->size] = NULL;
  // Return new heap
  return newHeap;
}

Heap heap_full(Heap heap) {
  // Resize the heap
  if (heap->size+1 != heap->cap)
    heap->data = REALLOC(heap->data,sizeof(Ptr)*(heap->cap=heap->size+1));
  // Return updated heap
  return heap;
}

Heap heap_clear(Heap heap, Visit del, const size_t maxSize) {
  // Free each element of the heap
  if (del)
    while (heap->size)
      del(((Ptr*)heap->data)[--heap->size]);
  ((Ptr*)heap->data)[0] = NULL;
  // Update the capacity
  heap->data = REALLOC(heap->data,sizeof(Ptr)*(heap->cap=maxSize+1));
  // Return empty heap
  return heap;
}

void heap_delete(Heap heap, Visit del) {
  // Free the data array
  if (del)
    while (heap->size)
      del(((Ptr*)heap->data)[--heap->size]);
  free(heap->data);
  // Free the structure
  free(heap);
}

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

void heap_prioritize(Ptr arr, Compare comp, const size_t s, const size_t r) {
  // Initialize the max index and the two childs of root
  size_t m = r, l = 2*r+1, d = 2*r+2;
  // Find the index of the maximum root child
  if (l < s && comp(((Ptr*)arr)[l],((Ptr*)arr)[m]) > 0)
    m = l;
  if (r < s && comp(((Ptr*)arr)[r],((Ptr*)arr)[m]) > 0)
    m = d;
  // If root is smaller than his biggest child, swap them
  if (m != r) {
    Ptr temp = ((Ptr*)arr)[r];
    ((Ptr*)arr)[r] = ((Ptr*)arr)[m], ((Ptr*)arr)[m] = temp;
    heap_prioritize(arr,comp,s,m);
  }
}

//_____________________________________________________________________________

#endif // __HEAP_C__
