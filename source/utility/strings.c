/// SOURCE - STRINGS
/** Source file for string manipulation. */
#ifndef __STRINGS_C__
#define __STRINGS_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/strings.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Str str_create(char* word) {
  // Allocate memory for string
  Str str = MALLOC(sizeof(struct _Str));
  // Initialize the string
  str->len = strlen(word), str->cap = str->len+1;
  str->word = MALLOC(sizeof(char)*str->cap);
  str->word = strcpy(str->word,word);
  // Return new string
  return str;
}

char* str_word(Str str) {
  // Return string's content
  return str->word;
}

size_t str_len(Str str) {
  // Return string's length
  return str->len;
}

bool str_empty(Str str) {
  // Return true if string is empty
  return str->len == 0;
}

bool str_equal(Str str1, Str str2) {
  // Compare both strings
  bool equals = true;
  char* s1 = str1->word, *s2 = str2->word;
  while (equals && *s1 && *s2)
    equals = !(*(s1++)-*(s2++));
  if (equals && (*s1 || *s2))
    equals = false;
  // Return compare value
  return equals;
}

int str_cmp(Str str1, Str str2) {
  // Return the compare value of the strings
  return strcmp(str1->word,str2->word);
}

char str_fetch(Str str, const size_t pos) {
  // Return char in given position
  return str->word[pos];
}

Str str_modify(Str str, const size_t pos, const char c) {
  // Modify char in given position
  str->word[pos] = c;
  // Return updated string
  return str;
}

Str str_append(Str str, const char c) {
  // Expand capacity if necessary
  if (str->len+1 == str->cap)
    str->word = REALLOC(str->word,sizeof(char)*(str->cap<<=1));
  // Append c at the end
  str->word[str->len] = c, str->word[++str->len] = '\0';
  // Return updated string
  return str;
}

Str str_truncate(Str str) {
  // Remove last char
  str->word[--str->len] = '\0';
  // Return updated string
  return (str->len<<1 < str->cap) ? str_full(str) : str;
}

Str str_trim(Str str) {
  // Return trimed string
  return str_leading(str_trailing(str));
}

Str str_trailing(Str str) {
  // Find last non-space char
  size_t last;
  bool finish = false;
  for (last = str->len; last && !finish; )
    finish = (!isspace(str->word[last-1])) ? true : (--last, false);
  // Adjust string if necessary
  if (str->len != last)
    str->word[str->len=last] = '\0';
  // Return updated string
  return (str->len<<1 < str->cap) ? str_full(str) : str;
}

Str str_leading(Str str) {
  // Find first non-space char
  size_t first;
  bool finish = false;
  for (first = 0; first < str->len && !finish; )
    finish = (!isspace(str->word[first])) ? true : (++first, false);
  // Adjust string if necessary
  if (first) {
    for (size_t i = first; i < str->len; ++i)
      str->word[i-first] = str->word[i];
    str->word[str->len-=first] = '\0';
  }
  // Return updated string
  return (str->len<<1 < str->cap) ? str_full(str) : str;
}

Str str_change(Str str, char* s) {
  // Adjust string's dimensions
  str->len = strlen(s); str_full(str);
  // Copy new word into the string
  str->word = strcpy(str->word,s);
  // Return updated string
  return str;
}

Str str_div(Str str, const size_t pos) {
  // Divide the string into two
  Str rest = str_create(str->word+pos);
  str->word[str->len=pos] = '\0';
  if (str->len<<1 < str->cap)
    str_full(str);
  // Return reminder string
  return rest;
}

Str str_cat(Str str, Str cat) {
  // Concatenate second string to the first one
  str->word = REALLOC(str->word,sizeof(char)*(str->cap=str->len+cat->len+1));
  for (size_t i = 0; i < cat->len; ++i)
    str->word[str->len++] = cat->word[i];
  str->word[str->len] = '\0';
  // Return concatenated string
  return str;
}

Str str_insert(Str str, Str in, const size_t pos) {
  // Return updated string
  return str_replace(str,in,0,pos);
}

Str str_replace(Str str, Str in, const size_t len, const size_t pos) {
  // Get preffix and suffix of str
  Str rest = str_div(str,pos+len);
  str->word[str->len=pos] = '\0';
  // Do the replacement
  str_cat(str_cat(str,in),rest);
  str_delete(rest);
  // Return updated string
  return str;
}

Str str_repall(Str str, Str pat, Str in) {
  // Find occurrences of pat in str
  size_t* kmp = str_kmp(str,pat);
  // Update array for correct replacement
  if (kmp[0] != 0) {
    size_t len = 1;
    for (size_t i = 2; i <= (size_t)kmp[0]; ++i)
      if (kmp[i]-kmp[len] >= pat->len)
        kmp[++len] = kmp[i];
    if (len != kmp[0])
      kmp[0] = len, kmp = REALLOC(kmp,sizeof(size_t)*(len+1));
    // Replace every ocurrence from right to left
    for (size_t i = len; i; --i)
      str_replace(str,in,pat->len,kmp[i]);
  }
  // Free auxiliary array
  free(kmp);
  // Return updated string
  return str;
}

long long str_int(Str str, const int base, const bool move, const bool sig) {
  // Set the parse function
  typedef long long (*Conv) (const char* word, char** endptr, int base);
  Conv conv = (sig) ? strtoll : (Conv)strtoull;
  // Parse the string
  if (!move)
    return conv(str->word,NULL,base);
  char* rest;
  long long n = conv(str->word,&rest,base);
  // Update the string
  str->len = strlen(rest);
  for (size_t i = 0; i <= str->len; ++i)
    str->word[i] = rest[i];
  if (str->len<<1 < str->cap)
    str_full(str);
  // Return found number
  return n;
}

long double str_real(Str str, const bool move) {
  // Parse the string
  if (!move)
    return strtold(str->word,NULL);
  char* rest;
  long double ld = strtold(str->word,&rest);
  // Update the string
  str->len = strlen(rest);
  for (size_t i = 0; i <= str->len; ++i)
    str->word[i] = rest[i];
  if (str->len<<1 < str->cap)
    str_full(str);
  // Return found number
  return ld;
}

Str str_map(Str str, char (*strMod) (char)) {
  // Apply the function to every char of str
  for (size_t i = 0; i < str->len; ++i)
    str->word[i] = strMod(str->word[i]);
  // Return updated string
  return str;
}

unsigned long long str_hash(Str str) {
  // Hash the string
  unsigned long long h = 5381;
  for (char* c = str->word; *c; ++c)
    h += (h<<5)^(unsigned char)*c;
  // Return the hash of the string
  return h;
}

Str str_get(FILE* fp, const bool eol) {
  // Create main string
  Str str = str_create("");
  // Read from stdin
  int c = fgetc(fp);
  for (bool finish = false; !finish; )
    // Analize the read character
    switch (c) {
      case EOF:
        finish = true;
        break;
      case '\n':
        if (eol)
          str_append(str,(char)c);
        finish = true;
        break;
      default:
        str_append(str,(char)c), c = fgetc(fp);
    }
  // Return read string
  return str_full(str);
}

Str str_getcond(FILE* fp, const bool eol, Condition cond, Visit message) {
  // Read until the condition is met
  Str str = str_get(fp,eol);
  while (!cond(str)) {
    // Print error message if necessary
    if (message)
      message(str);
    // Read next line
    str_delete(str), str = str_get(fp,eol);
  }
  // Return read string
  return str;
}

bool str_nonspace(Str str) {
  // Check if any character is not a space
  bool space = true;
  for (size_t i = 0; space && i < str->len; ++i)
    space = isspace(str->word[i]);
  // Return bool value
  return !space;
}

Str str_copy(Str str) {
  // Return copy of given string
  return str_create(str->word);
}

Str str_reverse(Str str) {
  // Reverse the string
  for (size_t i = 0, j = str->len-1-i; i < str->len>>1; ++i, --j) {
    str->word[i] ^= str->word[j], str->word[j] ^= str->word[i];
    str->word[i] ^= str->word[j];
  }
  // Return reversed string
  return str;
}

Str str_full(Str str) {
  // Adjust string to exact capacity if necessary
  if (str->len+1 != str->cap)
    str->word = REALLOC(str->word,sizeof(char)*(str->cap=str->len+1));
  // Return updated string
  return str;
}

Str str_clear(Str str, const size_t maxLen) {
  // Empty the string
  str->word[str->len=0] = '\0';
  str->word = REALLOC(str->word,sizeof(char)*(str->cap=maxLen+1));
  // Return empty string
  return str;
}

void str_delete(Str str) {
  // Free string's content
  free(str->word);
  // Free string
  free(str);
}

// ____________________________________________________________________________

// ------ AUXILIARIES ------ //

size_t* str_lpps(Str str) {
  // Create the auxiliary array of ints
  size_t* lpps = MALLOC(sizeof(size_t)*str->len);
  lpps[0] = 0;
  for (size_t i = 1, m = 0; i < str->len;)
    if (str->word[i] == str->word[m])
      lpps[i++] = ++m;
    else
      m = (m) ? lpps[m-1] : (lpps[i++] = 0);
  // Return auxiliary array
  return lpps;
}

size_t* str_kmp(Str str, Str pat) {
  // Create necessary arrays
  size_t* kmp = MALLOC(sizeof(size_t)*(str->len+1)), *lpps = str_lpps(pat);
  kmp[0] = 0;
  // Search ocurrences
  for (size_t i = 0, j = 0; i < str->len; ) {
    if (pat->word[j] == str->word[i])
      ++j, ++i;
    if (j == pat->len)
      kmp[++kmp[0]] = i-j, j = lpps[j-1];
    else if (i < str->len && pat->word[j] != str->word[i])
      j = (j) ? lpps[j-1] : (++i, (size_t)0);
  }
  // Free auxiliary memory
  free(lpps);
  kmp = REALLOC(kmp,sizeof(size_t)*(kmp[0]+1));
  // Return final array
  return kmp;
}

//_____________________________________________________________________________

#endif // __STRINGS_C__
