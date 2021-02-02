/**
 * \file src/status.c
 *
 * `status.c` implements functions for handling `talloc` status codes.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date Feburary 2020
 */

#include "talloc/status.h"
#include <stdlib.h>

/**
 * `TkStatusString` maps a `TkStatus` to a human readable error string.
 */
struct TkStatusString
{
  /** The error message represented. */
  enum TkStatus status;

  /** A short label for the error. */
  char* label;

  /** The human readable error. */
  char* string;
};

static const struct TkStatusString tkStatusStrings[] = {
  { TK_SUCCSSS, "TK_SUCCSSS", "Operation completed successfully" },
  { TK_ERROR_NOMEM, "TK_ERROR_NOMEM", "Out of memory" },
  { TK_ERROR_PANIC, "TK_ERROR_PANIC", "Unexpected runtime condition" },
  { TK_ERROR_GENERIC, "TK_ERROR_GENERIC", "Unknown error" }
};

/**
 * Fetch a human readable label associated with a status code.
 *
 * \param status The status code to query.
 * \return A short, human readable status label.
 */
char*
tkStatusLabel(enum TkStatus status)
{
  const struct TkStatusString* string = NULL;
  string = &tkStatusStrings[status];
  if (string->status != status) {
    /* TODO: Improve handling for out-of-order error tables. */
    exit(TK_ERROR_PANIC);
  }
  return string->label;
}

/**
 * Fetch a human readable description associated with a status code.
 *
 * \param status The status code to query.
 * \return A short, human readable status description.
 */
char*
tkStatusDescription(enum TkStatus status)
{
  const struct TkStatusString* string = NULL;
  string = &tkStatusStrings[status];
  if (string->status != status) {
    /* TODO: Improve handling for out-of-order error tables. */
    exit(TK_ERROR_PANIC);
  }
  return string->string;
}
