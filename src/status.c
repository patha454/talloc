/**
 * \file src/status.c
 *
 * `status.c` implements functions for handling `talloc` status codes.
 *
 * \see `include/talloc/status.h` for detailed API documentation.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date February 2020
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
  { TK_SUCCESS, "TK_SUCCESS", "Operation completed successfully" },
  { TK_ERROR_NOMEM, "TK_ERROR_NOMEM", "Out of memory" },
  { TK_ERROR_PANIC, "TK_ERROR_PANIC", "Unexpected runtime condition" },
  { TK_ERROR_GENERIC, "TK_ERROR_GENERIC", "Unknown error" }
};

const char*
tkStatusLabel(const enum TkStatus status)
{
  const struct TkStatusString* string = NULL;
  const char* const unknowStatusLabel = "<unknown status>";
  const size_t statusCount =
    sizeof(tkStatusStrings) / sizeof(tkStatusStrings[0]);
  if (status < 0 || status > statusCount) {
    return unknowStatusLabel;
  }
  string = &tkStatusStrings[status];
  if (string->status != status) {
    /* TODO: Improve handling for out-of-order error tables. */
    exit(TK_ERROR_PANIC);
  }
  return string->label;
}

const char*
tkStatusDescription(const enum TkStatus status)
{
  const struct TkStatusString* string = NULL;
  const char* const unknownStatusDescription =
    "<unknown status - this is probably a bug in error handling code.";
  const size_t descriptionCount =
    sizeof(tkStatusStrings) / sizeof(tkStatusStrings[0]);
  if (status < 0 || status > descriptionCount) {
    return unknownStatusDescription;
  }
  string = &tkStatusStrings[status];
  if (string->status != status) {
    /* TODO: Improve handling for out-of-order error tables. */
    exit(TK_ERROR_PANIC);
  }
  return string->string;
}
