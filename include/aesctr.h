/// HEADER - ENCRYPTION
/** Header file for an AES-CTR 256-bit key implementation. */
#ifndef __AESCTR_H__
#define __AESCTR_H__

//_____________________________________________________________________________

// ------ INCLUDES ------ //

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

//_____________________________________________________________________________

// ------ TYPES ------ //

/** Necessary data for cryptographic transformation. */
typedef struct _CrypText {
  unsigned char* text; // stored text
  unsigned long long nonce; // upper 64 bits of the 128-bit IV
  size_t len; // length of the text
} /** Cryptographic data type alias. */ CrypText;

//_____________________________________________________________________________

// ------ FUNCTIONS ------ //

/** Performs a cryptographic transformation to the text with the given key. */
void aes_transform(CrypText* data, const unsigned char key[32]);

//_____________________________________________________________________________

// ------ AUXILIARIES ------ //

/** Expands the given 256-bit key into the encryption key schedule rk. */
void aes_setenc(uint32_t rk[60], const unsigned char key[32]);

/** Encrypts the given 128-bit block using the expanded key rk. */
void aes_encblock(const uint32_t rk[60], unsigned char pb[16]);

//_____________________________________________________________________________

#endif // __AESCTR_H__
