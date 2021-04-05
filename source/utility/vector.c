/// SOURCE - VECTOR
/** Source file for vector implementation. */
#ifndef __VECTOR_C__
#define __VECTOR_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/vector.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Vec vec_create(const size_t maxLen) {
  // Allocate memory for vector
  Vec vec = MALLOC(sizeof(struct _Vec));
  // Initialize vector
  vec->len = 0, vec->cap = maxLen+1;
  vec->arr = MALLOC(sizeof(Ptr)*(vec->cap=maxLen+1));
  ((Ptr*)vec->arr)[0] = NULL;
  // Return vector
  return vec;
}

size_t vec_len(Vec vec) {
  // Return size of vector
  return vec->len;
}

bool vec_empty(Vec vec) {
  // Return true if vector is empty
  return vec->len == 0;
}

Ptr vec_fetch(Vec vec, const size_t pos) {
  // Return element in given position
  return ((Ptr*)vec->arr)[pos];
}

Vec vec_modify(Vec vec, Ptr val, Visit del, const size_t pos) {
  // Modify the element in given position
  if (del)
    del(((Ptr*)vec->arr)[pos]);
  ((Ptr*)vec->arr)[pos] = val;
  // Return updated vector
  return vec;
}

Vec vec_push(Vec vec, Ptr val) {
  // Expand capacity if necessary
  if (vec->len+1 == vec->cap)
    vec->arr = REALLOC(vec->arr,sizeof(Ptr)*(vec->cap*=2));
  // Append val at the end
  ((Ptr*)vec->arr)[vec->len] = val, ((Ptr*)vec->arr)[++vec->len] = NULL;
  // Return updated vector
  return vec;
}

Vec vec_pop(Vec vec, Visit del) {
  // Remove last element
  if (del)
    del(((Ptr*)vec->arr)[vec->len-1]);
  ((Ptr*)vec->arr)[--vec->len] = NULL;
  // Return updated vector
  return (vec->len<<1 < vec->cap) ? vec_full(vec) : vec;
}

Vec vec_div(Vec vec, const size_t pos) {
  // Divide the vector into two
  Vec rest = vec_create(vec->len-pos);
  for (size_t i = pos; i <= vec->len; ++i)
    ((Ptr*)rest->arr)[i-pos] = ((Ptr*)vec->arr)[i];
  rest->len = vec->len-pos;
  ((Ptr*)vec->arr)[vec->len=pos] = NULL;
  if (vec->len<<1 < vec->cap)
    vec_full(vec);
  // Return reminder vector
  return rest;
}

Vec vec_cat(Vec vec, Vec cat, Copy copy) {
  // Concatenate second vector to the first one
  vec->arr = REALLOC(vec->arr,sizeof(Ptr)*(vec->cap=vec->len+cat->len+1));
  for (size_t i = 0; i < cat->len; ++i)
    ((Ptr*)vec->arr)[vec->len++] = copy(((Ptr*)cat->arr)[i]);
  ((Ptr*)vec->arr)[vec->len] = NULL;
  // Return concatenated vector
  return vec;
}

Vec vec_map(Vec vec, Copy mod) {
  // Modify all elements in the vector
  for (size_t i = 0; i < vec->len; ++i)
    ((Ptr*)vec->arr)[i] = mod(((Ptr*)vec->arr)[i]);
  // Return updated vector
  return vec;
}

Vec vec_filter(Vec vec, Copy copy, Condition cond) {
  // Create new vector
  Vec newVec = vec_create(vec->len);
  // Append all elements that satisfy cond
  for (size_t i = 0; i < vec->len; ++i)
    if (cond(((Ptr*)vec->arr)[i]))
      ((Ptr*)newVec->arr)[newVec->len++] = copy(((Ptr*)vec->arr)[i]);
  ((Ptr*)newVec->arr)[newVec->len] = NULL;
  // Return new vector
  return vec_full(newVec);
}

Vec vec_sort(Vec vec, Compare comp) {
  // Return sorted vector
  return vec_subsort(vec,comp,0,vec->len-1);
}

Vec vec_traverse(Vec vec, Visit visit) {
  // Visit all elements in the vector
  for (size_t i = 0; i < vec->len; ++i)
    visit(((Ptr*)vec->arr)[i]);
  // Return vector
  return vec;
}

Vec vec_copy(Vec vec, Copy copy) {
  // Create new vector
  Vec newVec = vec_create(vec->len);
  // Append all elements to new vector
  for (size_t i = 0; i < vec->len; ++i)
    ((Ptr*)newVec->arr)[newVec->len++] = copy(((Ptr*)vec->arr)[i]);
  ((Ptr*)newVec->arr)[newVec->len] = NULL;
  // Return new vector
  return newVec;
}

Vec vec_reverse(Vec vec) {
  // Swap each element with their reflex
  for (size_t i = 0; i < vec->len>>1; ++i) {
    Ptr temp = ((Ptr*)vec->arr)[i];
    ((Ptr*)vec->arr)[i] = ((Ptr*)vec->arr)[vec->len-i-1];
    ((Ptr*)vec->arr)[vec->len-i-1] = temp;
  }
  // Return updated vector
  return vec;
}

Vec vec_full(Vec vec) {
  // Adjust vector to exact capacity if necessary
  if (vec->len+1 != vec->cap)
    vec->arr = REALLOC(vec->arr,sizeof(Ptr)*(vec->cap=vec->len+1));
  // Return updated vector
  return vec;
}

Vec vec_clear(Vec vec, Visit del, const size_t maxLen) {
  // Free all elements
  if (del)
    while (vec->len)
      del(((Ptr*)vec->arr)[--vec->len]);
  ((Ptr*)vec->arr)[0] = NULL;
  // Set the minimum capacity for the vector
  vec->arr = REALLOC(vec->arr,sizeof(Ptr)*(vec->cap=maxLen+1));
  // Return empty vector
  return vec;
}

void vec_delete(Vec vec, Visit del) {
  // Free the data array
  if (del)
    while (vec->len)
      del(((Ptr*)vec->arr)[--vec->len]);
  free(vec->arr);
  // Free the structure
  free(vec);
}

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

Vec vec_subsort(Vec vec, Compare comp, const size_t l, const size_t r) {
  // Sort subvector recursively
  if (l < r) {
    size_t m = (l+r-1)>>1;
    vec_subsort(vec,comp,l,m), vec_subsort(vec,comp,m+1,r);
    vec_merge(vec,comp,l,r);
  }
  // Return sorted subvector
  return vec;
}

Vec vec_merge(Vec vec, Compare comp, const size_t l, const size_t r) {
  // Create auxiliary arrays
  const size_t m = (l+r-1)>>1, len1 = m-l+1, len2 = r-m;
  Ptr* a = MALLOC(sizeof(Ptr)*len1), *b = MALLOC(sizeof(Ptr)*len2);
  for (size_t i = 0; i < len1; ++i)
    a[i] = ((Ptr*)vec->arr)[l+i];
  for (size_t j = 0; j < len2; ++j)
    b[j] = ((Ptr*)vec->arr)[m+j+1];
  // Merge the auxiliary arrays back to vec
  size_t i = 0, j = 0, k = l;
  while (i < len1 && j < len2)
    ((Ptr*)vec->arr)[k++] = (comp(a[i],b[j]) <= 0) ? a[i++] : b[j++];
  // Copy the remaining elements from the auxiliary arrays to vec
  while (i < len1)
    ((Ptr*)vec->arr)[k++] = a[i++];
  while (j < len2)
    ((Ptr*)vec->arr)[k++] = b[j++];
  // Free auxiliary arrays
  free(a), free(b);
  // Return merged subvector
  return vec;
}

//_____________________________________________________________________________

#endif // __VECTOR_C__
