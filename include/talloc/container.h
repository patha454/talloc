/**
 * \file include/talloc/container.h
 *
 * `container.h` defines an API for interacting with data structures which
 * store a value by key.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2021.
 */

#ifndef TALLOC_CONTAINER_H_
#define TALLOC_CONTAINER_H_

#include "talloc/status.h"

/**
 * Interface for a container function which gets an item based on a key.
 *
 * \param context The implementation specific context of the container to
 * get from.
 * \param key The key to get.
 * \return A pointer to the requested item, or NULL if it does not exist.
 */
typedef void* (*TkContainerGet)(void* context, void* key);

/**
 * Interface for a container function which sets an item based on a key.
 *
 * The item will be created if it does not already exist.
 *
 * \param context The implementation specific context of the container to
 * set into.
 * \param key The key to set.
 * \return `TK_SUCCESS` or an error on failure.
 */
typedef enum TkStatus (*TkContainerSet)(void* context, void* key);

/** Vtable for managing and interacting with a container. */
struct TkContainer
{
  /** Pointer to implementation specific context. */
  void* context;

  TkContainerGet get;

  TkContainerSet set;
};

/** Opaque handle to a container. */
typedef struct TkContainer* TkContainer;

#endif
