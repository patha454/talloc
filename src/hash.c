/**
 * \file src/hash.c
 *
 * `hash.c` defines functions and types used by talloc for hashing data.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021
 */

#include "talloc/hash.h"
#include <stddef.h>

/* `tallocHash` current uses the Jenkins one-at-a-time hash function. */
TallocHash
tallocHash(const char* str)
{
  size_t i = 0;
  TallocHash hash = 0;
  while (str[i] != '\0') {
    hash += str[i++];
    /* These magic numbers are okay. They're Jenkins hash constants. */
    /* NOLINTNEXTLINE */
    hash += hash << 10U;
    /* NOLINTNEXTLINE */
    hash ^= hash >> 6U;
  }
  /* NOLINTNEXTLINE */
  hash += hash << 3U;
  /* NOLINTNEXTLINE */
  hash ^= hash >> 11U;
  /* NOLINTNEXTLINE */
  hash += hash << 15U;
  return hash;
}
