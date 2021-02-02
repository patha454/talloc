/**
 * \file src/binary-tree.c
 *
 * `binary-tree.c` implements a generic binary tree.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>.
 * \copyright BSL-1.0.
 * \date Feburary 2021.
 */

#include <stdlib.h>

/**
 * \struct TkBinaryTree
 *
 * `TkBinaryTree` stores the context for a binary tree.
 */
struct TkBinaryTree
{
  /** The root node of the tree stored. */
  struct TkBinaryTreeNode* root;
};

typedef struct TkBinaryTree* TkBinaryTree;

/**
 * \struct TkBinaryTreeNode represents a binary tree node.
 *
 * `TkBinaryTreeNode`s are internal state to a binary tree.
 * `TkBinaryTreeNodes`s should not be used directly. Instead, see
 * `struct TkBinaryTree`'s helper methods.
 */
struct TkBinaryTreeNode
{
  /** The object stored in the tree node, or NULL if empty. */
  void* node;

  /** The left-branch of the tree, or NULL if there is no such branch. */
  struct TkBinaryTreeNode* left;

  /** The right-branch of the tree, or NULL if there is no such branch. */
  struct TkBinaryTreeNode* right;
};

typedef struct TkBinaryTreeNode* TkBinaryTreeNode;

TkBinaryTreeNode
tkNewBinaryTreeNode()
{
  TkBinaryTreeNode node = malloc(sizeof(struct TkBinaryTreeNode));
  node->left = NULL;
  node->right = NULL;
  node->node = NULL;
  return node;
}
