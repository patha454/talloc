/**
 * \file src/talloc.c
 *
 * `src/talloc.c` defines functions and data types for interacting with the
 * tracking memory allocator.
 *
 * \see `include/talloc/talloc.h` for detailed documentation comments and
 * API documentation.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021.
 */

#include "talloc/talloc.h"
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

#include <stdio.h>
Reference
tallocAlloc(TallocHash id, TallocHash type, size_t size)
{
  printf("talloc id: %lx; type: %lx; size: %zu\n", id, type, size);
  return NULL;
}
