/**
 * \file include/talloc/binary-tree.h
 *
 * `binary-tree.h` declares functions and data types for creating and
 * manipulating binary trees.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021.
 */

#ifndef TALLOC_BINARY_TREE_H_
#define TALLOC_BINARY_TREE_H_

#include "talloc/container.h"

/** Handle to a binary tree. */
typedef struct TkBinaryTree* TkBinaryTree;

/**
 * API for functions which compare two elements in a tree.
 *
 * \param lhs "Left hand" side to compare.
 * \param rhh "Right hand" side to compare.
 * \return 0: `lhs` == `rhs`; negative: `lhs` < `rhs`; positive `lhs` < `rhs`.
 */
typedef int (*TkBinaryTreeCompare)(void* lhs, void* rhs);

/**
 * Create a new binary tree.
 *
 * \param binaryTree Location to store a handle to the binary tree.
 * \return `TK_SUCCESS`, or an error code on failure.
 */
enum TkStatus
tkBinaryTreeCreate(TkBinaryTree* binaryTree);

/**
 * Create a new binary tree, using the generic container interface.
 *
 * \param container Location to store a handle to the container.
 * \return `TK_SUCCESS`, or an error code on failure.
 */
enum TkStatus
tkBinaryTreeCreateContainer(TkContainer* container);

/**
 * Destroy and free a binary tree.
 *
 * \param binaryTree The tree to destroy.
 * \return `TK_SUCCESS` or an error code on failure.
 */
enum TkStatus
tkBinaryTreeDestroy(TkBinaryTree binaryTree);

/**
 * Destroy a binary tree, using the generic container interface.
 *
 * |param container The binary tree instance to destroy.
 * \return `TK_SUCCESS` or an error on failure.
 */
enum TkStatus
tkBinaryTreeDestroyContainer(TkContainer container);

#endif
