/**
 * \file include/status.h
 *
 * `status.h` defines `talloc` status codes, as well as functions and macros
 * for manipulating them.
 *
 * \author H Paterson <harley.paterson@postgrad.otago.ac.nz>
 * \copyright BSL-1.0
 * \date Feburary 2021.
 */

/** `TkStatus` indicates the success or otherwise of allocator operations. */
enum TkStatus
{
  /** Request successfully handled. */
  TK_SUCCESS = 0,

  /** Out of memory. */
  TK_ERROR_NOMEM = 1,

  /** Unexpected runtime situation. */
  TK_ERROR_PANIC = 2,

  /** Generic, or otherwise unspecified error. */
  TK_ERROR_GENERIC = 3,
} TkStatus;

/**
 * Test if a value is an error status code.
 *
 * \param x Status code to test.
 */
#define IS_ERROR(x) ((enum TkStatus) (x) != TK_SUCCESS)

/**
 * Fetch a human readable description associated with a status code.
 *
 * \param status The status code to query.
 * \return A short, human readable status description.
 */
const char*
tkStatusDescription(const enum TkStatus status);

/**
 * Fetch a human readable label associated with a status code.
 *
 * \param status The status code to query.
 * \return A short, human readable status label.
 */
const char*
tkStatusLabel(const enum TkStatus status);
