/**
 * \file src/reference.c
 *
 * `reference.c` defines functions and data types for manipulating talloc
 * references.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021
 */

#include "talloc/reference.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct TallocRef
{
  /** Unique ID of the object stored in the reference. */
  TallocHash id;

  /** Type of the object stored in the reference. */
  TallocHash type;

  /** Pointer to the actual object stored in the reference. */
  void* object;
};

Reference tkCreateReference(TallocHash id, TallocHash type, void* object)
{
  struct TallocRef* ref = malloc(sizeof (*ref));
  if (ref == NULL) {
    perror("Allocating reference structure");
    exit(EXIT_FAILURE);
  }
  ref->id = id;
  ref->type = type;
  ref->object = object;
  return ref;
}

void tkDestroyReference(Reference ref)
{
  assert(ref != NULL);
  ref->object = NULL;
  ref->id = 0;
  ref->type = 0;
  free(ref);
}

TallocHash tkReferenceType(Reference ref)
{
  assert(ref != NULL);
  return ref->type;
}

TallocHash tkReferenceId(Reference ref)
{
  assert(ref != NULL);
  return ref->id;
}

void* tkDereference(Reference ref)
{
  assert(ref != NULL);
  return ref->object;
}
