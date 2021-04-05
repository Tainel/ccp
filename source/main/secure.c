/// MAIN - SECURE
/** Main file for an encryption program. */
#ifndef __MAIN__
#define __MAIN__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include "../../include/strings.h"
#include "../../include/aesctr.h"

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Cryptographic transformation type. */
typedef enum _CrypOp {
  MANY = -2, INVALID, NONE, HELP, ENCRYPT, DECRYPT
} /** Cryptographic transformation type alias. */ CrypOp;

//_____________________________________________________________________________

// ------ STATICS ------ //

/** Prints helpful information for the program. */
static void sec_help(void) {
  // Print help
  puts("Encrypts and decrypts files.");
  puts("Usage: secure [option]");
  puts("The possible options are:");
  puts(" * -h  provides helpful information and exits.");
  puts(" * -e  encrypts a file.");
  puts(" * -d  attemps to decrypt a file.");
  puts("If encryption is chosen, the following are required:");
  puts(" * a 256-bit encryption key.");
  puts(" * a 64-bit nonce, optional, 0 by default.");
  puts(" * an input file with the plaintext.");
  puts(" * an output file where to print the ciphertext.");
  puts("If decryption is chosen, the following are required:");
  puts(" * the 256-bit key used in the encryption.");
  puts(" * an input file with the nonce and ciphertext.");
  puts(" * an output file where to print the plaintext.");
  puts("In both cases, the default output file is the given input file.");
}

/** Gets key from stdin. */
static unsigned char* sec_getkey(void) {
  // Wait for a key
  fputs("Key: ",stdout);
  // Read key from stdin
  Str key;
  for (bool valid = false; !valid; ) {
    key = str_get(stdin,false);
    // Check if key es valid
    if (!(valid = key->len <= 32)) {
      fputs("Key cannot exceed 32 bytes long, try again.\nKey: ",stdout);
      str_delete(key);
    }
  }
  // Fix the size of the key
  unsigned char* fixed = (unsigned char*)key->word;
  if (key->len != 32)
    fixed = REALLOC(fixed,sizeof(char)*32);
  for (size_t i = key->len+1; i < 32; ++i)
    fixed[i] = '\0';
  // Free extra memory
  free(key);
  // Return the fixed key
  return fixed;
}

/** Gets nonce from stdin. */
static unsigned long long sec_getnonce(void) {
  // Wait for a nonce
  fputs("Nonce: ",stdout);
  // Read nonce from stdin
  unsigned long long nonce = 0;
  for (bool valid = false; !valid; ) {
    Str num = str_trim(str_get(stdin,false));
    // Check if nonce is set to default
    if (num->len)
      nonce = (unsigned long long)str_int(num,10,true,false);
    // Check if nonce is valid
    if (!(valid = num->len == 0))
      fputs("Nonce must be a number, try again.\nNonce: ",stdout);
    // Free extra memory
    str_delete(num);
  }
  // Return the nonce
  return nonce;
}

/** Gets input file from stdin. */
static FILE* sec_getinput(Str* name) {
  // Wait for a file name
  fputs("Input file: ",stdout);
  // Read file name from stdin
  FILE* file = NULL;
  while (!file) {
    *name = str_get(stdin,false);
    file = fopen((*name)->word,"rb");
    // Check if file name is valid
    if (!file) {
      fputs("Cannot open file, try again.\nInput file: ",stdout);
      str_delete(*name);
    }
  }
  str_full(*name);
  // Return the open file
  return file;
}

/** Gets the necessary data from a file and closes it when finished. */
static CrypText* sec_getdata(FILE* file, const unsigned long long nonce) {
  // Initialize the data
  CrypText* data = malloc(sizeof(CrypText));
  data->nonce = nonce, data->len = 0;
  // Read the file
  size_t cap = 64;
  data->text = MALLOC(sizeof(char)*cap);
  for (int c = fgetc(file); c != EOF; c = fgetc(file)) {
    // Adjust the memory if necessary
    if (data->len == cap)
      data->text = REALLOC(data->text,sizeof(char)*(cap<<=1));
    // Append the last character
    data->text[data->len++] = (unsigned char)c;
  }
  // Fix the memory
  fclose(file);
  if (data->len)
    data->text = REALLOC(data->text,sizeof(char)*data->len);
  // Return the data
  return data;
}

/** Gets output file from stdin. */
static FILE* sec_getoutput(Str name) {
  // Wait for a file name
  fputs("Output file: ",stdout);
  // Read file name from stdin
  FILE* file = NULL;
  while (!file) {
    Str new = str_get(stdin,false);
    file = (new->len) ? fopen(new->word,"wb") : fopen(name->word,"wb");
    str_delete(new);
    if (!file)
      fputs("Cannot open file, try again.\nOutput file: ",stdout);
    else
      str_delete(name);
  }
  // Return the open file
  return file;
}

/** Encrypts a text with a key and a nonce. */
static void sec_encrypt(void) {
  // Get valid key
  unsigned char* key = sec_getkey();
  // Get valid nonce
  unsigned long long nonce = sec_getnonce();
  // Get input file and open it
  Str name;
  FILE* file = sec_getinput(&name);
  // Get the encryption data
  CrypText* data = sec_getdata(file,nonce);
  // Encrypt the plaintext
  aes_transform(data,key);
  // Free the used key
  for (size_t i = 0; i < 32; ++i)
    key[i] = '\0';
  free(key);
  // Get and open output file
  file = sec_getoutput(name);
  // Write the nonce and the ciphertext
  for (int i = 7; i >= 0; --i)
    fputc((int)(nonce>>(i<<3)),file);
  for (size_t i = 0; i < data->len; ++i)
    fputc(data->text[i],file);
  // Free extra memory
  fclose(file);
  if (data->text)
    free(data->text);
  free(data);
}

/** Gets the nonce from an encrypted file. */
static unsigned long long sec_getusednonce(FILE* file, bool* success) {
  // Initialize the nonce
  unsigned long long nonce = 0;
  // Read first 8 bytes if possible
  for (int i = 7; *success && i >= 0; --i) {
    int c = fgetc(file);
    if ((*success = c != EOF))
      nonce |= (unsigned long long)(c<<(i<<3));
  }
  // Return the nonce
  return nonce;
}

/** Decrypts a text with a key. */
static int sec_decrypt(void) {
  // Get valid key
  unsigned char* key = sec_getkey();
  // Get input file and open it
  Str name;
  FILE* file = sec_getinput(&name);
  // Get the used nonce from the file
  bool success = true;
  unsigned long long nonce = sec_getusednonce(file,&success);
  // Exit execution if an error was encountered
  if (!success) {
    fclose(file), fputs("ERROR: Input file cannot be decrypted.\n",stderr);
    for (size_t i = 0; i < 32; ++i)
      key[i] = '\0';
    free(key), str_delete(name);
    return EXIT_FAILURE;
  }
  // Get the decryption data
  CrypText* data = sec_getdata(file,nonce);
  // Decrypt the ciphertext
  aes_transform(data,key);
  // Free the used key
  for (size_t i = 0; i < 32; ++i)
    key[i] = '\0';
  free(key);
  // Get and open output file
  file = sec_getoutput(name);
  // Write the plaintext
  for (size_t i = 0; i < data->len; ++i)
    fputc(data->text[i],file);
  // Free extra memory
  fclose(file);
  if (data->text)
    free(data->text);
  free(data);
  // Return exit code
  return EXIT_SUCCESS;
}

//_____________________________________________________________________________

// ------ MAIN ------ //

int main(int argc, char** argv) {
  // Initialize option
  CrypOp option = NONE;
  if (argc > 1) {
    if (argc > 2)
      option = MANY;
    else if (!strcmp(argv[1],"-h"))
      option = HELP;
    else if (!strcmp(argv[1],"-e"))
      option = ENCRYPT;
    else if (!strcmp(argv[1],"-d"))
      option = DECRYPT;
    else
      option = INVALID;
  }
  // Continue execution according to chosen mode
  int ret = EXIT_SUCCESS;
  switch (option) {
    // Too many arguments
    case MANY:
      fputs("ERROR: Too many arguments given.\n",stderr), ret = EXIT_FAILURE;
      break;
    // Invalid argument
    case INVALID:
      fputs("ERROR: Invalid argument given.\n",stderr), ret = EXIT_FAILURE;
      break;
    // Print help
    case HELP:
      sec_help();
      break;
    // Encrypt a file
    case ENCRYPT:
      sec_encrypt();
      break;
    // Decrypt a file
    case DECRYPT:
      ret = sec_decrypt();
      break;
    // No arguments
    default:
      fputs("ERROR: No arguments given.\n",stderr), ret = EXIT_FAILURE;
  }
  // Finish execution
  return ret;
}

//_____________________________________________________________________________

#endif // __MAIN__

