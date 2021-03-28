/**
 * \file include/talloc/ref-tree.h
 *
 * `ref-tree.h` declears functions and data types for manipulating trees of
 * talloc references.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BLS-1.0
 * \date February 2021
 */

#ifndef TALLOC_REF_TREE_H_
#define TALLOC_REF_TREE_H_

#include "talloc/reference.h"

/** Handle to a talloc reference tree. */
typedef struct TkRefTree* TkRefTree;

/**
 * Allocate and initialise a new ref tree.
 *
 * \return The new talloc ref tree.
 */
TkRefTree
tkRefTreeAlloc();

/**
 * Free and deallocate an existing ref tree.
 *
 * \warning `tkRefTreeFree` will not free the objects referenced, only the
 * references themselve. The object pointers must be freed separably, if
 * required, to prevent memory leaks.
 *
 * \param tree The tree to insert into.
 */
void
tkRefTreeFree(TkRefTree tree);

/**
 * Insert a reference into the tree.
 *
 * \param tree The tree to insert into.
 * \param value The value to insert.
 * \return An updated reference to `tree`.
 */
TkRefTree
tkRefTreeInsert(TkRefTree tree, Reference value);

/**
 * Iterate over every reference in the tree, calling a function with each
 * reference.
 *
 * \param tree The tree to iterate over.
 * \param lambda The function to call with each reference.
 */
void
tkRefTreeForEach(TkRefTree tree, void (*lambda)(Reference));

/**
 * Iterate over every reference in the tree, calling a function for each instace
 * of a type.
 *
 * \param tree The tree to iterate over.
 * \param lambda The function to call with the reference.
 * \param type The type to iterate over instaces of.
 */
void
tkRefTreeForEachInstance(TkRefTree tree,
                         void (*lambda)(Reference),
                         TallocHash type);

/**
 * Delete a reference from the reference tree.
 *
 * \param tree The tree to delete from.
 * \param value The value to remove.
 * \return An updated reference to the `tree`.
 */
TkRefTree
tkRefTreeDelete(TkRefTree tree, Reference value);

#endif
