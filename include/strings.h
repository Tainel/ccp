/// HEADER - STRINGS
/** Header file for string manipulation. */
#ifndef __STRINGS_H__
#define __STRINGS_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "basics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//_____________________________________________________________________________

// ------ MACROS ------ //

/** Prints str in given stream. */
#ifndef PRINT
#define PRINT(str,stream) \
  (fputs((str)->word,stream))
#endif // PRINT

//_____________________________________________________________________________

// ------ TYPES ------ //

/** String struct. */
typedef struct _Str {
  char* word; // char array
  size_t len, cap; // size and capacity
} /** Pointer to the string. */ *Str;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Creates a string from word. */
Str str_create(char* word);

/** Returns word stored in str. */
char* str_word(Str str);

/** Returns length of str. */
size_t str_len(Str str);

/** Checks if str is empty. */
bool str_empty(Str str);

/** Checks if two strings are equal. */
bool str_equal(Str str1, Str str2);

/** Compares two strings. */
int str_cmp(Str str1, Str str2);

/** Returns char in given valid position pos of str. */
char str_fetch(Str str, const size_t pos);

/** Modifies char in valid pos of str by a non-null char c. */
Str str_modify(Str str, const size_t pos, const char c);

/** Appends a non-null char c to str. */
Str str_append(Str str, const char c);

/** Removes last char from non-empty string str. */
Str str_truncate(Str str);

/** Removes all spaces at the start and end of str. */
Str str_trim(Str str);

/** Removes all trailing spaces from str. */
Str str_trailing(Str str);

/** Removes all leading spaces from str. */
Str str_leading(Str str);

/** Modifies str with a new word. */
Str str_change(Str str, char* s);

/** Truncates str in given position, and returns the remainder. */
Str str_div(Str str, const size_t pos);

/** Concatenates two strings into the first one. */
Str str_cat(Str str, Str cat);

/** Inserts non-empty string in inside str in given position. */
Str str_insert(Str str, Str in, const size_t pos);

/** Replaces the substring of str of given non-zero length len in pos by in. */
Str str_replace(Str str, Str in, const size_t len, const size_t pos);

/** Replaces each instance of non-empty string pat in str by string in. */
Str str_repall(Str str, Str pat, Str in);

/** Returns a long long represented by str in the specified base. If move is
 * true, str then becomes the substring that comes immediately after the
 * number. If no number is found at the beginning of str, 0 is returned, and
 * str remains unchanged. If sig is true, the number is signed. */
long long str_int(Str str, const int base, const bool move, const bool sig);

/** Returns a long double represented by str. If move is true, str then becomes
 * the substring that comes immediately after the number. If no number is found
 * at the beginning of str, 0 is returned, and str remains unchanged. */
long double str_real(Str str, const bool move);

/** Modifies each char of str according to a given function strMod. */
Str str_map(Str str, char (*strMod) (char));

/** Hashes str. */
unsigned long long str_hash(Str str);

/** Reads a string from given stream fp. */
Str str_get(FILE* fp, const bool eol);

/** Reads lines from fp until a line that fulfills the given condition is read.
 * An optional function is passed to print a message every time a line is read
 * that doesn't fulfill the requirements. */
Str str_getcond(FILE* fp, const bool eol, Condition cond, Visit message);

/** Determines if the string has a non-space character. */
bool str_nonspace(Str str);

/** Returns a copy of str. */
Str str_copy(Str str);

/** Reverses str. */
Str str_reverse(Str str);

/** Sets exact capacity for str. */
Str str_full(Str str);

/** Empties str ans initializes its capacity. */
Str str_clear(Str str, const size_t maxLen);

/** Destroys str. */
void str_delete(Str str);

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

/** Returns an array of numbers with information necessary for str_kmp. */
size_t* str_lpps(Str str);

/** Returns an array of numbers with the ocurrences of non-empty string pat
 * inside str, according to Knuth-Morris-Pratt's algorithm. */
size_t* str_kmp(Str str, Str pat);

//_____________________________________________________________________________

#endif // __STRINGS_H__
