/**
 * \file include\talloc\talloc.h
 *
 * `talloc.h` declears a public interface to a managed memory allocator which
 * tracks the types of variables, and provides handles to access and
 * manipulate them.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021
 */

#ifndef TALLOC_TALLOC_H_
#define TALLOC_TALLOC_H_

#include <stddef.h>
#include <stdint.h>

/** Reference to a memory object managed by talloc. */
typedef struct TallocRef* Reference;

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

/**
 * Allocate a new talloc tracked memory reference.
 *
 * \param id Unique identifier for the object.
 * \param type Unique identifier for the type.
 * \size Size of the object to allocate.
 */
Reference
tallocAlloc(TallocHash id, TallocHash type, size_t size);

/**
 * Allocate a new tracked memory reference.
 *
 * \param id Unique string name for the memory object.
 * \param type The type to allocate.
 */
#define talloc(id, type)                                                       \
  (tallocAlloc(tallocHash(id), tallocHash(#type), sizeof(type)))

#endif
