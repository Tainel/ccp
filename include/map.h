/// HEADER - HASH TABLE
/** Header file for hash table implementation using double hashing. */
#ifndef __MAP_H__
#define __MAP_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "primes.h"
#include "basics.h"
#include <stdlib.h>
#include <stdio.h>

//_____________________________________________________________________________

// ------ MACROS ------ //

/** Returns number in range [0,c-1] obtained from k. */
#ifndef HASH
#define HASH(k,c) \
  ((k)%(c))
#endif // HASH

/** Returns number in range [0,c-1] obtained from k, different from i. */
#ifndef PROBE
#define PROBE(k,i,c) \
  (((i)+(1+(k)%((c)-1)))%(c))
#endif // PROBE

/** Determines if a position in hash table m is free to place k. */
#ifndef AVAILABLE
#define AVAILABLE(m,k,i) \
  (!(m)->cells[i].key||(m)->equals((m)->cells[i].key,k))
#endif // AVAILABLE

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Structure of a cell of a hash table. */
typedef struct _HashCell{
  Ptr key, data; // key and data stored in the cell
  bool rem; // flag that indicates if the cell was recently removed
} /** Hash cell type alias. */ HashCell;

/** Structure of a hash table. */
typedef struct _Map {
  HashCell* cells; // array of hash cells
  Hash hash; // hash function
  Equals equals; // equality function for keys
  size_t size, fil, cap; // number of elements, non-empty cells and total cells
} /** Pointer to the hash table. */ *Map;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates an empty hash table. */
Map map_create(Hash hash, Equals equals, const size_t cap);

/** Returns the number of elements in map. */
size_t map_size(Map map);

/** Checks if map is empty. */
bool map_empty(Map map);

/** Inserts data inside map with given key. If the key was already used, the
 * old element is removed. */
Map map_insert(Map map, Ptr key, Ptr data, Visit delKey, Visit delData);

/** Removes an element and key from map. */
Map map_remove(Map map, Ptr key, Visit delKey, Visit delData);

/** Searches element in map associated with given key. If no element is
 * associated with it, a null pointer is returned. */
Ptr map_search(Map map, Ptr key);

/** Traverse map, both the keys and the data. */
Map map_traverse(Map map, Visit visitKey, Visit visitData);

/** Empties map. */
Map map_clear(Map map, Visit delKey, Visit delData, const size_t cap);

/** Destroys map. */
void map_delete(Map map, Visit delKey, Visit delData);

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

/** Resizes map to a prime no smaller than the previos capacity. */
Map map_resize(Map map);

/** Rehashes each element to a new array of hash cells. */
Map map_rehash(Map map, HashCell* cells, const size_t cap);

/** Searches in map a free index for the given key. */
size_t map_index(Map map, Ptr key);

/** Destroys the element of map in position idx. */
void map_free(HashCell* cells, Visit delKey, Visit delData, const size_t idx);

//_____________________________________________________________________________

#endif // __MAP_H__
