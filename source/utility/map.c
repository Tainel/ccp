/// SOURCE - HASH TABLE
/** Source file for hash table implementation using double hashing. */
#ifndef __MAP_C__
#define __MAP_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/map.h"

//_____________________________________________________________________________

// ------ MACROS ------ //

/** Maximum load factor before resizing. */
#ifndef MAX_LOAD
#define MAX_LOAD ((long double)0.7L)
#endif // MAX_LOAD

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Map map_create(Hash hash, Equals equals, const size_t cap) {
  // Allocate memory for hash table
  Map map = MALLOC(sizeof(struct _Map));
  // Initialize table
  map->size = map->fil = 0, map->hash = hash, map->equals = equals;
  map->cells = MALLOC(sizeof(HashCell)*(map->cap=prime_next(cap)));
  for (size_t i = 0; i < map->cap; ++i)
    map->cells[i].key = map->cells[i].data = NULL, map->cells[i].rem = false;
  // Return empty table
  return map;
}

size_t map_size(Map map) {
  // Return the number of elements
  return map->size;
}

bool map_empty(Map map) {
  // Check is map is empty
  return map->size == 0;
}

Map map_insert(Map map, Ptr key, Ptr data, Visit delKey, Visit delData) {
  // Search the index
  size_t idx = map_index(map,key);
  // If the cell is empty, add the new element
  if (!map->cells[idx].key) {
    if (!map->cells[idx].rem)
      ++map->fil;
    else
      map->cells[idx].rem = false;
    ++map->size;
  }
  // Else, remove the previous element
  else
    map_free(map->cells,delKey,delData,idx);
  // Place the new element
  map->cells[idx].key = key, map->cells[idx].data = data;
  // Return updated map
  return ((long double)map->fil/map->cap >= MAX_LOAD) ? map_resize(map) : map;
}

Map map_remove(Map map, Ptr key, Visit delKey, Visit delData) {
  // Find the index of the key
  size_t tag = map->hash(key), idx = HASH(tag,map->cap);
  while (!AVAILABLE(map,key,idx) || map->cells[idx].rem)
    idx = PROBE(tag,idx,map->cap);
  // Remove the element if it exists
  if (map->cells[idx].key) {
    map_free(map->cells,delKey,delData,idx);
    map->cells[idx].rem = true, --map->size;
  }
  // Return updated map
  return map;
}

Ptr map_search(Map map, Ptr key) {
  // Search the index
  size_t idx = map_index(map,key);
  // Return found data
  return (map->cells[idx].key) ? map->cells[idx].data : NULL;
}

Map map_traverse(Map map, Visit visitKey, Visit visitData) {
  // Traverse each cell
  for (size_t i = 0; i < map->cap; ++i)
    if (map->cells[i].key) {
      if (visitKey)
        visitKey(map->cells[i].key);
      if (visitData)
        visitData(map->cells[i].data);
    }
  // Return the map
  return map;
}

Map map_clear(Map map, Visit delKey, Visit delData, const size_t cap) {
  // Remove each element from map
  for (size_t i = 0; i < map->cap; ++i) {
    if (map->cells[i].key)
      map_free(map->cells,delKey,delData,i);
    map->cells[i].rem = false;
  }
  map->size = map->fil = 0;
  // Resize map to its original size
  map->cap = prime_next(cap);
  map->cells = REALLOC(map->cells,sizeof(HashCell)*map->cap);
  // Return empty map
  return map;
}

void map_delete(Map map, Visit delKey, Visit delData) {
  // Empty the table
  for (size_t i = 0; i < map->cap; ++i)
    if (map->cells[i].key)
      map_free(map->cells,delKey,delData,i);
  // Free the cells and the structure
  free(map->cells), free(map);
}

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

Map map_resize(Map map) {
  // Update capacity and create new table
  size_t cap = prime_next(map->cap*2);
  HashCell* cells = MALLOC(sizeof(HashCell)*cap);
  for (size_t i = 0; i < cap; ++i)
    cells[i].key = cells[i].data = NULL, cells[i].rem = false;
  // Return the table after rehasing
  return map_rehash(map,cells,cap);
}

Map map_rehash(Map map, HashCell* cells, const size_t cap) {
  // Place each element of map into the new table
  for (size_t i = 0; i < map->cap; ++i)
    if (map->cells[i].key) {
      // Find the index of current key in cells
      size_t tag = map->hash(map->cells[i].key), idx = HASH(tag,cap);
      while (cells[idx].key)
        idx = PROBE(tag,idx,cap);
      // Update the new cells
      cells[idx] = map->cells[i];
    }
  // Update the table
  free(map->cells), map->cells = cells, map->cap = cap, map->fil = map->size;
  // Return updated hash table
  return map;
}

size_t map_index(Map map, Ptr key) {
  // Find the index for the key
  size_t tag = map->hash(key), idx = HASH(tag,map->cap);
  while (!AVAILABLE(map,key,idx))
    idx = PROBE(tag,idx,map->cap);
  // If a removed cell was found, continue searching for key or empty cell
  if (map->cells[idx].rem) {
    size_t aux = idx;
    while (!AVAILABLE(map,key,aux) || map->cells[aux].rem)
      aux = PROBE(tag,aux,map->cap);
    // If key was found, swap its elements with original index
    if (map->cells[aux].key) {
      HashCell temp = map->cells[idx];
      map->cells[idx] = map->cells[aux], map->cells[aux] = temp;
    }
  }
  // Return found index
  return idx;
}

void map_free(HashCell* cells, Visit delKey, Visit delData, const size_t idx) {
  // Free the elements if necessary
  if (delKey)
    delKey(cells[idx].key);
  if (delData)
    delData(cells[idx].data);
  // Empty the cell
  cells[idx].key = cells[idx].data = NULL;
}

//_____________________________________________________________________________

#endif // __MAP_C__
