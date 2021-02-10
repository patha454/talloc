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

/** Internal implementation for a binary tree node. */
struct TkBinaryTreeNode
{
  /** Pointer to data stored in the node. */
  void* element;

  /** Left child, or NULL. */
  struct TkBinaryTreeNode* left;

  /** Right child, or NULL. */
  struct TkBinaryTreeNode* right;
};

/** Internal implementaiton context for a binary tree. */
struct TkBinaryTree
{
  /** Magic number confirms this is a binary tree. */
  size_t magic;

  /** Root of the tree. */
  struct TkBinaryTreeNode* root;

  /** Function to compare two instances of the type stored in the tree. */
  TkBinaryTreeCompare comparisionFunction;
};

/**
 * Create a new binary tree node.
 *
 * \param node Location to store a pointer to the new node.
 * \return `TK_SUCCESS` or an error code on failure.
 */
enum TkStatus
tkBinaryTreeNodeCreate(struct TkBinaryTreeNode** node)
{
  struct TkBinaryTreeNode* newNode = malloc(sizeof *node);
  if (newNode == NULL) {
    *node = NULL;
    return TK_ERROR_NOMEM;
  }
  newNode->element = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  *node = newNode;
  return TK_SUCCESS;
}

/**
 * Destroy a binary tree node.
 *
 * \note `tkBinaryTreeNodeDestroy` will not free the element in the node.
 *
 * \param node Binary tree node to destroy.
 */
void tkBinaryTreeNodeDestroy(struct TkBinaryTreeNode* node)
{
  assert(node != NULL);
  node->element = NULL;
  node->left = NULL;
  node->right = NULL;
  free(node);
}

/**
 * Insert an element into the binary tree.
 *
 * \note This does nothing if the element already exists according to the
 * comparon function.
 *
 * \param node The tree node to make a recursive insert into.
 * \param element The element to insert.
 * \param comparison Function to determine the ordering of elements.
 * \return `TK_SUCCESS` or an error code on failure.
 */
enum tkStatus tkBinaryTreeNodeInsert(struct TkBinaryTreeNode* node, void* element, TkBinaryTreeCompare comparision)
{
  assert(node != NULL);
  assert(element != NULL);
  int diff = 0;
  enum TkStatus status = TK_SUCCESS;
  if (node->element == NULL) {
    node->element = element;
    return TK_SUCCESS;
  }
  diff = comparision(element, node->element);
  if (diff == 0) {
    return TK_SUCCESS;
  }
  if (diff < 0) {
    if (node->left == NULL) {
      status = tkBinaryTreeNodeCreate(node->left);
      if (IS_ERROR(status)) {
        return status;
      }
      return tkBinaryTreeNodeInsert(node->left, element, comparision);
    }
  }
  else {
    if (node->right == NULL) {
      status = tkBinaryTreeNodeCreate(node->right);
      if (IS_ERROR(status)) {
        return status;
      }
      return tkBinaryTreeNodeInsert(node->right, element, comparision);
    }
  }
  return TK_SUCCESS;
}

/**
 * Insert a node into a binary tree.
 *
 * \param binaryTree The tree to insert into.
 * \param element The element to insert.
 * \return `TK_SUCCESS` or an error on failure.
 */
enum TkStatus
tkBinaryTreeInsert(TkBinaryTree binaryTree, void* element)
{
  assert(binaryTree != NULL);
  return tkBinaryTreeNodeInsert(binaryTree->root, element, binaryTree->comparisionFunction);
}

// TODO... Add tree creation to creato fucntion.

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
