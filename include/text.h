/// HEADER - TEXT
/** Header file for text manipulation. */
#ifndef __TEXT_H__
#define __TEXT_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "strings.h"
#include "list.h"

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Text daya type alias. */
typedef List Txt;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Reads text pointed by fp. */
Txt txt_read(FILE* fp);

/** Writes txt into fp. */
void txt_write(Txt txt, FILE* fp);

//_____________________________________________________________________________

#endif // __TEXT_H__
