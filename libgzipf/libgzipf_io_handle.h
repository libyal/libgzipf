/*
 * Input/Output (IO) handle
 *
 * Copyright (C) 2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBGZIPF_IO_HANDLE_H )
#define _LIBGZIPF_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libgzipf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libgzipf_io_handle libgzipf_io_handle_t;

struct libgzipf_io_handle
{
	/* Value to indicate if the string data is in Unicode (UTF-16 little-endian)
	 */
	uint8_t is_unicode;

	/* Flags
	 */
	uint8_t flags;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libgzipf_io_handle_initialize(
     libgzipf_io_handle_t **io_handle,
     libcerror_error_t **error );

int libgzipf_io_handle_free(
     libgzipf_io_handle_t **io_handle,
     libcerror_error_t **error );

int libgzipf_io_handle_clear(
     libgzipf_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_IO_HANDLE_H ) */

