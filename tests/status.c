/**
 * \file tests/status.c
 *
 * Provides unit tests for `talloc`'s status handling code.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0.
 * \date February 2021.
 */

#include "talloc/status.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
/* cmocka.h must be included after setjmp.h, stdarg.h, and stddef.h. */
// clang-format off
#include <cmocka.h>
// clang-format on

/** Test `tkStatusLabel` under normal conditions. */
static void
testTkStatusLabelNormal(void** state)
{
  assert_string_equal(tkStatusLabel(TK_SUCCESS), "TK_SUCCESS");
  assert_string_equal(tkStatusLabel(TK_ERROR_PANIC), "TK_ERROR_PANIC");
}

/** Test `tkStatusStatusLabelAbnormal` with an invalid parameter. */
static void
testTKStatusLabelInvalid(void** state)
{
  assert_string_equal(tkStatusLabel(-1), "<unknown status>");
}

/** Test `tkStatusDescription under normal conditions. */
static void
testTkStatusDescriptionNormal(void** state)
{
  assert_string_equal(tkStatusDescription(TK_SUCCESS),
                      "Operation completed successfully");
  assert_string_equal(tkStatusDescription(TK_ERROR_NOMEM), "Out of memory");
}

/** Test `tkStatusDescription` with an invalid parameter. */
static void
testTkStatusDescriptionInvalid(void** state)
{
  assert_string_equal(
    tkStatusDescription(-1),
    "<unknown status - this is probably a bug in error handling code.");
}

/** Test the `src/status.c` complation unit. */
int
main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(testTkStatusLabelNormal),
    cmocka_unit_test(testTKStatusLabelInvalid),
    cmocka_unit_test(testTkStatusDescriptionNormal),
    cmocka_unit_test(testTkStatusDescriptionInvalid)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
