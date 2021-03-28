/**
 * \file src/ref-tree.c
 *
 * `src/ref-tree.c` implements a binary tree used for looking up talloc
 * references based on the ID hash.
 *
 * \see `include/talloc/ref-tree.h` for detailed documentation comments and API
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021.
 */

#include "talloc/ref-tree.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * `struct TkRefTree` is a recursive binary tree storing talloc References.
 */
struct TkRefTree
{
  Reference value;

  TkRefTree left;

  TkRefTree right;
};

TkRefTree
tkRefTreeAlloc()
{
  struct TkRefTree* tree = malloc(sizeof(*tree));
  if (tree == NULL) {
    perror("Allocating reference tree");
    exit(EXIT_FAILURE);
  }
  tree->value = NULL;
  tree->left = NULL;
  tree->right = NULL;
  return tree;
}

/* NOLINTNEXTLINE(misc-no-recursion) */
void
tkRefTreeFree(TkRefTree tree)
{
  if (tree == NULL) {
    return;
  }
  tkRefTreeFree(tree->left);
  tkRefTreeFree(tree->right);
  free(tree);
}

/* NOLINTNEXTLINE(misc-no-recursion) */
TkRefTree
tkRefTreeInsert(TkRefTree tree, Reference value)
{
  assert(value != NULL);
  long diff = 0;
  if (tree == NULL) {
    tree = tkRefTreeAlloc();
    tree->value = value;
    return tree;
  }
  diff = tkReferenceId(tree->value) - tkReferenceId(value);
  if (diff == 0) {
    fprintf(
      stderr,
      "%s: An object with ID 0x%lx already exists and will be overwritten\n",
      __func__,
      tkReferenceId(value));
    tree->value = value;
  } else if (diff < 0) {
    tree->right = tkRefTreeInsert(tree->right, value);
  } else {
    tree->left = tkRefTreeInsert(tree->left, value);
  }
  return tree;
}

TkRefTree
tkRefTreeFindMin(TkRefTree tree)
{
  TkRefTree current_node = tree;
  while (current_node->left) {
    current_node = current_node->left;
  }
  return current_node;
}

/* NOLINTNEXTLINE(misc-no-recursion) */
TkRefTree
tkRefTreeDelete(TkRefTree tree, Reference value)
{
  if (tree == NULL) {
    return NULL;
  }
  TkRefTree temp = NULL;
  long diff = (long)(tkReferenceId(tree->value) - tkReferenceId(value));
  if (diff > 0) {
    tree->left = tkRefTreeDelete(tree->left, value);
  } else if (diff < 0) {
    tree->right = tkRefTreeDelete(tree->right, value);
  } else {
    if (tree->left == NULL && tree->right == NULL) {
      /*tkRefTreeFree(tree); */
      tree = NULL;
    } else if (tree->left == NULL) {
      /* tkRefTreeFree(tree); */
      tree = tree->right;
    } else if (tree->right == NULL) {
      /* tkRefTreeFree(tree); */
      tree = tree->left;
    } else {
      temp = tkRefTreeFindMin(tree->right);
      tree->value = temp->value;
      tree->right = tkRefTreeDelete(tree->right, temp->value);
    }
  }
  return tree;
}

/* NOLINTNEXTLINE(misc-no-recursion) */
void
tkRefTreeForEach(TkRefTree tree, void (*lambda)(Reference))
{
  if (tree == NULL || tree->value == NULL) {
    return;
  }
  tkRefTreeForEach(tree->left, lambda);
  lambda(tree->value);
  tkRefTreeForEach(tree->right, lambda);
}

void
tkRefTreeForEachInstance(TkRefTree tree,
                         void (*lambda)(Reference),
                         TallocHash type)
{
  if (tree == NULL || tree->value == NULL) {
    return;
  }
  tkRefTreeForEach(tree->left, lambda);
  if (tkReferenceType(tree->value) == type) {
    lambda(tree->value);
  }
  tkRefTreeForEach(tree->right, lambda);
}
