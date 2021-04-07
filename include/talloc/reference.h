/**
 * \file include/talloc/reference.h
 *
 * `reference.h` declears functions and data types for manipulating talloc
 * references.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021
 */

#ifndef TALLOC_REFERENCE_H_
#define TALLOC_REFERENCE_H_

#include "talloc/hash.h"

/** Reference to a memory object managed by talloc. */
typedef struct TallocRef* Reference;

/**
 * Create a new talloc reference.
 *
 * \note `tkCreateReference` only creates the reference structure. It will not
 * enter the reference into any tracking structures.
 *
 * \param id The ID hash of the object to reference.
 * \param type The type hash of the object to reference.
 * \param memory Pointer to the object being referenced.
 */
Reference
tkCreateReference(TallocHash id, TallocHash type, void* object);

/**
 * Destory and deallocate a reference.
 *
 * \warning `tkDestoryReference` will not free the object the reference stores,
 * only the reference itself. The object should be freed separately, when
 * required, to prevent memory leaks.
 *
 * \param ref The reference to destroy.
 */
void
tkDestroyReference(Reference ref);

/**
 * Get the type associated with a referenced object.
 *
 * \param ref The reference in question.
 * \return A hash of the reference's type.
 */
TallocHash
tkReferenceType(Reference ref);

/**
 * Get the Id associated with a a referenced object.
 *
 * \param ref The reference in question.
 * \return A hash of the reference's ID.
 */
TallocHash
tkReferenceId(Reference ref);

/**
 * Get a pointer to an object associated with a reference.
 *
 * \param ref The reference to read.
 * \return A pointer to the object tracked by the reference.
 */
void*
tkDereference(Reference ref);

/**
 * Replace the object a reference tracks.
 * 
 * This will free the exisitng object being tracked.
 *
 * \param ref The reference to update.
 * \param newValue The object to track in the reference.
 */
void
tkReplaceValue(Reference ref, void* newValue);

#endif
