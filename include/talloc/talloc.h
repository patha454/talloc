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

#include "talloc/reference.h"
#include "talloc/hash.h"
#include <stddef.h>
#include <stdint.h>

/**
 * Initialise talloc's internal state.
 *
 * \note `tallocInit()` must be called before any internal functions.
 */
void tallocInit();

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
 * Call a function with each reference talloc is tracking.
 *
 * \param lambda A function to call with each reference.
 */
void tallocForEachRef(void (*lambda)(Reference));

/**
 * Allocate a new tracked memory reference.
 *
 * \param id Unique string name for the memory object.
 * \param type The type to allocate.
 */
#define talloc(id, type)                                                       \
  (tallocAlloc(tallocHash(id), tallocHash(#type), sizeof(type)))

/**
 * Get the object a talloc reference tracks.
 *
 * \param x The talloc reference to read.
 * \param type The type to get a pointer to.
 * \return A `type` pointer to `x`.
 */
#define tallocDeref(x, type) (*(type*) tkDereference(x))

#endif
