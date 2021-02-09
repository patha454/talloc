/**
 * \file src/binary-tree.c
 *
 * `binary-tree.c` implements a generic binary tree.
 *
 * \see `include/talloc/binary-tree.h` for detailed doccomments and API
 * documentation.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>.
 * \copyright BSL-1.0.
 * \date Feburary 2021.
 */

#include "talloc/binary-tree.h"
#include <assert.h>
#include <stdlib.h>

/** Magic number for binary tree types. */
#define TK_BINARY_TREE_MAGIC 0x70DDB44356EB38AF

/** Internal implementaiton context for a binary tree. */
struct TkBinaryTree
{
  /** Magic number confirms this is a binary tree. */
  size_t magic;
};

enum TkStatus
tkBinaryTreeCreate(TkBinaryTree* binaryTree)
{
  assert(binaryTree != NULL);
  struct TkBinaryTree* newTree = malloc(sizeof *newTree);
  if (newTree == NULL) {
    *binaryTree = NULL;
    return TK_ERROR_NOMEM;
  }
  newTree->magic = TK_BINARY_TREE_MAGIC;
  *binaryTree = newTree;
  return TK_SUCCESS;
}

enum TkStatus
tkBinaryTreeCreateContainer(TkContainer* container)
{
  assert(container != NULL);
  enum TkStatus status = TK_SUCCESS;
  struct TkContainer* newContainer = malloc(sizeof *newContainer);
  if (newContainer == NULL) {
    return TK_ERROR_NOMEM;
  }
  status = tkBinaryTreeCreate((TkBinaryTree*)&newContainer->context);
  if (IS_ERROR(status)) {
    tkBinaryTreeDestroyContainer(newContainer);
    return status;
  }
  newContainer->get = NULL;
  newContainer->set = NULL;
  *container = newContainer;
  return TK_SUCCESS;
}

enum TkStatus
tkBinaryTreeDestroyContainer(TkContainer container)
{
  enum TkStatus status = TK_SUCCESS;
  assert(container != NULL);
  if (container->context != NULL) {
    status = tkBinaryTreeDestroy(container->context);
    if (IS_ERROR(status)) {
      return status;
    }
  }
  container->context = NULL;
  container->get = NULL;
  container->set = NULL;
  free(container);
  return TK_SUCCESS;
}

enum TkStatus
tkBinaryTreeDestroy(TkBinaryTree binaryTree)
{
  assert(binaryTree != NULL);
  if (binaryTree->magic != TK_BINARY_TREE_MAGIC) {
    return TK_ERROR_TYPE;
  }
  free(binaryTree);
  return TK_SUCCESS;
}
