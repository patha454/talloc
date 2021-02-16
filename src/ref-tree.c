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

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "talloc/ref-tree.h"

/**
 * `struct TkRefTree` is a recursive binary tree storing talloc References.
 */
struct TkRefTree {
    Reference value;

    TkRefTree left;

    TkRefTree right;
};

TkRefTree tkRefTreeAlloc()
{
    struct TkRefTree* tree = malloc(sizeof (*tree));
    if (tree == NULL) {
        perror("Allocating reference tree");
        exit(EXIT_FAILURE);
    }
    tree->value = NULL;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

void tkRefTreeFree(TkRefTree tree)
{
    if (tree == NULL) {
        return;
    }
    tkRefTreeFree(tree->left);
    tkRefTreeFree(tree->right);
    free(tree);
    return;
}

void tkRefTreeInsert(TkRefTree tree, Reference value)
{
    assert(tree != NULL);
    int diff = 0;
    if (tree->value == NULL) {
        tree->value = value;
        return;
    }
    diff = tkReferenceId(tree->value) - tkReferenceId(value);
    if (diff == 0) {
        return;
    }
    if (diff < 0) {
        if (tree->right == NULL) {
            tree->right = tkRefTreeAlloc();
        }
        tkRefTreeInsert(tree->right, value);
    }
    else {
        if (tree->left == NULL) {
            tree->left = tkRefTreeAlloc();
        }
        tkRefTreeInsert(tree->left, value);
    }
}

void tkRefTreeForEach(TkRefTree tree, void (*lambda)(Reference))
{
    if (tree == NULL || tree->value == NULL) {
        return;
    }
    tkRefTreeForEach(tree->left, lambda);
    lambda(tree->value);
    tkRefTreeForEach(tree->right, lambda);
}

void tkRefTreeForEachInstance(TkRefTree tree, void (*lambda)(Reference), TallocHash type)
{
    if (tree == NULL || tree->value == NULL) {
        return;
    }
    tkRefTreeForEach(tree->left, lambda);
    if(tkReferenceType(tree->value) == type) {
      lambda(tree->value);
    }
    tkRefTreeForEach(tree->right, lambda);
}
