/**
 * \file include/talloc/hash.h
 *
 * `hash.h` declears has functions and types used by talloc.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021
 */

#ifndef TALLOC_HASH_H_
#define TALLOC_HASH_H_

#include <stdint.h>

/** Talloc type used to refer to types and objects. */
typedef uint64_t TallocHash;

/**
 * Construct a talloc hash from a string representing a unique object or type.
 *
 * \param str String to hash.
 * \return A hash of the string, used to access the object or type.
 */
TallocHash
tallocHash(const char* str);

#endif
