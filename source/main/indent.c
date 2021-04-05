/// MAIN - INDENT
/** Main file for an indentation program. */
#ifndef __MAIN__
#define __MAIN__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/text.h"
#include "../../include/bst.h"

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Type of end of line. */
typedef enum _NewLine {
  NONE, LF, CRLF
} /** Newline type alias. */ Newline;

/** Flags for the indent program. */
typedef struct _Flags {
  bool n, s; // flags
} /** Indent flags alias. */ Flags;

/** State of the indented file. */
typedef struct _State {
  char* name; // name of the file
  unsigned long tws, tabs, lfs, cuts, old, bytes, nascii; // numeric values
  bool read, updated, write; // boolean flags
} /** File state alias. */ State;

/** Total information of all given files. */
typedef struct _Log {
  int total, read, fails, up; // numeric file values
  unsigned long tws, tabs, lfs, cuts, old, bytes, nascii; // numeric values
} /** Final log alias. */ Log;

//_____________________________________________________________________________

// ------ STATICS ------ //

/** Prints helpful information for the program. */
static void indent_help(void) {
  // Print help
  puts("Indents ASCII LF/CRLF C/C++ source code and header files.");
  puts("Usage: indent [option] [flags] [files]");
  puts("The possible options are:");
  puts(" * -h  provides helpful information and exits.");
  puts("The possible flags are:");
  puts(" * -n  leaves the files unchanged.");
  puts(" * -s  stays quiet after indenting.");
  puts("All files are indented according to the following rules:");
  puts(" * all trailing whitespaces are removed.");
  puts(" * all tabs are replaced with two spaces.");
  puts(" * all lines are terminated with a line feed.");
  puts(" * all lines are cut and continued below after 80 bytes long.");
  puts("Useful runtime information is given after indenting each file.");
}

/** Check if given string sets on a flag. If true, modify the flags. */
static bool indent_isflag(char* arg, Flags* flags) {
  // Check if the argument corresponds with a possible flag
  if (!strcmp(arg,"-n"))
    return flags->n = true;
  if (!strcmp(arg,"-s"))
    return flags->s = true;
  // Return false if no flag was found
  return false;
}

/** Detects the newline character used in the given string. */
static Newline indent_newline(Str line) {
  // Initialize the end of line
  Newline nl = NONE;
  // Detect the end of line in the string
  if (line->len && line->word[line->len-1] == '\n')
    nl = (line->len-1 && line->word[line->len-2] == '\r') ? CRLF : LF;
  // Return found newline
  return nl;
}

/** Indents the current line of the file stored in node. */
static void indent_line(Dln node, State* state, Str tabs, Str spaces) {
  // Detect the newline used
  Newline nl = indent_newline(node->val);
  if (nl != LF)
    ++state->lfs;
  // Trim all trailing spaces
  size_t len = ((Str)node->val)->len;
  state->tws += (unsigned long)(len-str_trailing(node->val)->len-nl);
  len = ((Str)node->val)->len;
  // Replace all tabs with two spaces
  state->tabs += (unsigned long)(str_repall(node->val,tabs,spaces)->len-len);
  // Add a line feed at the end of the line
  str_append(node->val,'\n');
  // Cut the line if it exceeds 80 characters long and continue below
  if (((Str)node->val)->len > 80) {
    Str rest = str_div(node->val,78);
    str_append(node->val,'\\'), str_append(node->val,'\n'), ++state->cuts;
    node->next = dln_create(rest,node,node->next);
  }
  // Count characters
  len = ((Str)node->val)->len, state->bytes += (unsigned long)len;
  for (size_t i = 0; i < len; ++i)
    if ((unsigned char)(((Str)node->val)->word[i]) >= 128)
      ++state->nascii;
  // Adjust the line
  str_full(node->val);
}

/** Prints all gathered information during the indentation of the file. */
static void indent_verbose(State* state) {
  // Print log
  printf("  File name: \"%s\"\n",state->name);
  if (!state->read)
    puts("    The file couldn't be read.");
  else {
    printf("    %lu removed trailing whitespaces.\n",state->tws);
    printf("    %lu replaced tabs.\n",state->tabs);
    printf("    %lu updated newlines.\n",state->lfs);
    printf("    %lu cut lines.\n",state->cuts);
    printf("    %lu non-ASCII bytes.\n",state->nascii);
    printf("    %lu total bytes originally.\n",state->old);
    printf("    %lu total bytes in final version.\n",state->bytes);
    if (!state->write)
      puts("    The file couldn't be written on.");
    else if (state->updated)
      puts("    The file was updated.");
    else
      puts("    The file was not updated.");
  }
}

/** Indents the code inside the file of given name. */
static State indent_file(Str name, Flags* flags) {
  // Initialize the state
  State state = {name->word,0,0,0,0,0,0,0,true,false,true};
  // Open and read file if possible
  FILE* fp = fopen(name->word,"rb");
  if (!fp) {
    state.read = false;
    if (!flags->s)
      indent_verbose(&state);
    return state;
  }
  Txt code = txt_read(fp);
  fclose(fp);
  // Count the number of bytes if necessary
  if (!flags->s)
    for (Dln node = code->first; node; node = node->next)
      state.old += (unsigned long)(((Str)node->val)->len);
  // Indent the code
  Str tab = str_create("\t"), spaces = str_create("  ");
  for (Dln node = code->first; node; node = node->next)
    indent_line(node,&state,tab,spaces);
  str_delete(tab), str_delete(spaces);
  // Rewrite the code into the file if possible
  if (!flags->n && (state.tws || state.tabs || state.lfs || state.cuts)) {
    fp = fopen(name->word,"wb");
    if (!fp)
      state.write = false;
    else
      txt_write(code,fp), fclose(fp), state.updated = true;
  }
  // Print log
  if (!flags->s)
    indent_verbose(&state);
  // Free the memory
  list_delete(code,(Visit)str_delete);
  // Return the state
  return state;
}

/** Merges the second state into the first one. */
static void indent_merge(Log* log, State* st) {
  // Merge the fields
  log->read += (st->read) ? 1: 0;
  log->fails += (!st->write) ? 1: 0;
  log->up += (st->updated) ? 1: 0;
  log->tws += st->tws, log->tabs += st->tabs, log->lfs += st->lfs;
  log->cuts += st->cuts, log->old += st->old, log->bytes += st->bytes;
  log->nascii += st->nascii;
}

/** Traverses all files recursively and indents them. */
static void indent_traverse(Bsn files, Log* log, Flags* flags) {
  // Traverse the files recursively
  if (files) {
    indent_traverse(files->left,log,flags);
    State st = indent_file(files->val,flags);
    indent_merge(log,&st);
    indent_traverse(files->right,log,flags);
  }
}

/** Prints the final log. */
static void indent_log(Log* log) {
  // Print final log
  puts("Final log:");
  puts("  File information:");
  printf("    %d out of %d files were read.\n",log->read,log->total);
  printf("    %d out of %d files were updated:\n",log->up,log->up+log->fails);
  puts("  Found changes:");
  printf("    %lu removed trailing whitespaces.\n",log->tws);
  printf("    %lu replaced tabs.\n",log->tabs);
  printf("    %lu updated newlines.\n",log->lfs);
  printf("    %lu cut lines.\n",log->cuts);
  puts("  Byte information:");
  printf("    %lu non-ASCII bytes in total.\n",log->nascii);
  printf("    %lu bytes in total originally.\n",log->old);
  printf("    %lu bytes in total in final version.\n",log->bytes);
}

//_____________________________________________________________________________

// ------ MAIN ------ //

int main(int argc, char** argv) {
  // If necessary, provide helpful information
  if (argc > 1 && !strcmp(argv[1],"-h"))
    indent_help();
  // Else, continue with the execution
  else {
    // Parse flags
    Flags flags = {false,false};
    int fidx;
    for (fidx = 1; fidx < argc && indent_isflag(argv[fidx],&flags); ++fidx);
    // Indent each file if possible
    if (fidx < argc) {
      // Read each file once
      Bst files = bst_create((Compare)str_cmp);
      while (fidx < argc)
        bst_insert(files,str_create(argv[fidx++]),(Visit)str_delete);
      Log log = {(int)files->size,0,0,0,0,0,0,0,0,0,0};
      if (!flags.s)
        puts("Start indentation:");
      indent_traverse(files->root,&log,&flags);
      // Print the final log
      if (!flags.s)
        indent_log(&log);
      // Free the memory
      bst_delete(files,(Visit)str_delete);
    }
    // Else, print corresponding message
    else if (!flags.s)
      puts("There are no files to indent.");
  }
  // Finish execution
  return EXIT_SUCCESS;
}

//_____________________________________________________________________________

#endif // __MAIN__
