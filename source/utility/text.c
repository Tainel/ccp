/// SOURCE - TEXT
/** Source file for text manipulation. */
#ifndef __TEXT_C__
#define __TEXT_C__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/text.h"

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

Txt txt_read(FILE* fp) {
  // Initialize the text
  Txt txt = list_create();
  // Read each line from stream
  for (bool finish = false; !finish; ) {
    Str str = str_get(fp,true);
    // If read line is not empty, append it to txt
    if (str->len) {
      list_append(txt,str);
      // If the current line is the last one, stop reading
      finish = (str->word[str->len-1] != '\n') ? true : false;
    }
    // Else, stop reading
    else
      str_delete(str), finish = true;
  }
  // Return read text
  return txt;
}

void txt_write(Txt txt, FILE* fp) {
  // Print each element of txt in given stream
  for (Dln line = txt->first; line; line = line->next)
    PRINT((Str)line->val,fp);
}

//_____________________________________________________________________________

#endif // __TEXT_C__
