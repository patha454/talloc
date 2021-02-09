/**
 * \file tests/binary-tree.c
 *
 * Provides unit tests for `talloc`'s binary tree code.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0.
 * \date February 2021.
 */

#include "talloc/binary-tree.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
/* cmocka.h must be included after setjmp.h, stdarg.h, and stddef.h. */
// clang-format off
#include <cmocka.h>
// clang-format on

/** State for testing binary trees. */
struct TkBinaryTreeTestState
{
  TkBinaryTree tree;
};

/** State for testing binary tree containers. */
struct TkBinaryTreeContainerTestState
{
  TkContainer container;
};

/** Test `tkBinaryTreeCreate` */
static void
testTkBinaryTreeCreate(void** context) /* NOLINT */
{
  TkBinaryTree binaryTree = NULL;
  enum TkStatus status = TK_SUCCESS;
  status = tkBinaryTreeCreate(&binaryTree);
  assert_true(status == TK_SUCCESS);
  assert_ptr_not_equal(binaryTree, NULL);
  tkBinaryTreeDestroy(binaryTree);
}

/** Setup the binary tree test. */
static int
setupTkBinaryTreeDestroy(void** context)
{
  enum TkStatus status = TK_SUCCESS;
  struct TkBinaryTreeTestState* state = malloc(sizeof(*state));
  if (state == NULL) {
    return 1;
  }
  status = tkBinaryTreeCreate(&state->tree);
  if (IS_ERROR(status)) {
    return 1;
  }
  *context = state;
  return 0;
}

/** Test binary tree destruction. */
static void
testTkBinaryTreeDestory(void** context)
{
  struct TkBinaryTreeTestState* state = *context;
  enum TkStatus status = TK_SUCCESS;
  status = tkBinaryTreeDestroy(state->tree);
  assert_true(status == TK_SUCCESS);
}

/** Test binary tree container creation. */
static void
testTkBinaryTreeCreateContainer(void** context) /* NOLINT */
{
  TkContainer container = NULL;
  enum TkStatus status = TK_SUCCESS;
  status = tkBinaryTreeCreateContainer(&container);
  assert_true(status == TK_SUCCESS);
  assert_ptr_not_equal(container, NULL);
  tkBinaryTreeDestroyContainer(container);
}

/** Setup binary tree container destruction testing. */
static int
setupTkBinaryTreeContainerDestroy(void** context)
{
  enum TkStatus status = TK_SUCCESS;
  struct TkBinaryTreeContainerTestState* state = malloc(sizeof(*state));
  if (state == NULL) {
    return 1;
  }
  status = tkBinaryTreeCreateContainer(&state->container);
  if (IS_ERROR(status)) {
    return 1;
  }
  *context = state;
  return 0;
}

/** Test binary tree container destruction. */
static void
testTkBinaryTreeContainerDestroy(void** context)
{
  struct TkBinaryTreeContainerTestState* state = *context;
  enum TkStatus status = TK_SUCCESS;
  status = tkBinaryTreeDestroyContainer(state->container);
  assert_true(status == TK_SUCCESS);
}

/** Test the `src/binary-tree.c` complation unit. */
int
main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(testTkBinaryTreeCreate),
    cmocka_unit_test_setup(testTkBinaryTreeDestory, setupTkBinaryTreeDestroy),
    cmocka_unit_test(testTkBinaryTreeCreateContainer),
    cmocka_unit_test_setup(testTkBinaryTreeContainerDestroy,
                           setupTkBinaryTreeContainerDestroy),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
