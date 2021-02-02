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
  TK_SUCCSSS,

  /** Out of memory. */
  TK_ERROR_NOMEM,

  /** Unexpected runtime situation. */
  TK_ERROR_PANIC,

  /** Generic, or otherwise unspecified error. */
  TK_ERROR_GENERIC,
};
