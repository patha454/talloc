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

#ifndef TALLOC_STATUS_H_
#define TALLOC_STATUS_H_

/** `TkStatus` indicates the success or otherwise of allocator operations. */
enum TkStatus
{
  /** Request successfully handled. */
  TK_SUCCESS = 0,

  /** Out of memory. */
  TK_ERROR_NOMEM = 1,

  /** Unexpected runtime situation. */
  TK_ERROR_PANIC = 2,

  /** Invalid or unexpected data type. */
  TK_ERROR_TYPE = 3,

  /** Generic, or otherwise unspecified error. */
  TK_ERROR_GENERIC = 4,
};

/**
 * Test if a value is an error status code.
 *
 * \param x Status code to test.
 */
#define IS_ERROR(x) ((enum TkStatus)(x) != TK_SUCCESS)

/**
 * Fetch a human readable description associated with a status code.
 *
 * \param status The status code to query.
 * \return A short, human readable status description.
 */
const char*
tkStatusDescription(enum TkStatus status);

/**
 * Fetch a human readable label associated with a status code.
 *
 * \param status The status code to query.
 * \return A short, human readable status label.
 */
const char*
tkStatusLabel(enum TkStatus status);

#endif
