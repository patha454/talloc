/**
 * \file src/talloc.c
 *
 * `src/talloc.c` defines functions and data types for interacting with the
 * tracking memory allocator.
 *
 * \see `include/talloc/talloc.h` for detailed documentation comments and
 * API documentation.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021
 */

#include "talloc/talloc.h"
#include "talloc/ref-tree.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static TkRefTree idTree;

Reference
tallocAlloc(TallocHash id, TallocHash type, size_t size)
{
  void* object = malloc(size);
  if (object == NULL) {
    perror("Allocating talloc object");
    exit(EXIT_FAILURE);
  }
  Reference ref = tkCreateReference(id, type, object);
  tkRefTreeInsert(idTree, ref);
  return ref;
}

void tallocForEachRef(void (*lambda)(Reference))
{
  tkRefTreeForEach(idTree, lambda);
}

void tallocInit()
{
  idTree = tkRefTreeAlloc();
}
