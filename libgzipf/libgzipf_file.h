/*
 * File functions
 *
 * Copyright (C) 2019-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBGZIPF_FILE_H )
#define _LIBGZIPF_FILE_H

#include <common.h>
#include <types.h>

#include "libgzipf_extern.h"
#include "libgzipf_io_handle.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcthreads.h"
#include "libgzipf_libfcache.h"
#include "libgzipf_libfdata.h"
#include "libgzipf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libgzipf_internal_file libgzipf_internal_file_t;

struct libgzipf_internal_file
{
	/* The IO handle
	 */
	libgzipf_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The members list
	 */
	libfdata_list_t *members_list;

	/* The members cache
	 */
	libfcache_cache_t *members_cache;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBGZIPF_EXTERN \
int libgzipf_file_initialize(
     libgzipf_file_t **file,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_free(
     libgzipf_file_t **file,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_signal_abort(
     libgzipf_file_t *file,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_open(
     libgzipf_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBGZIPF_EXTERN \
int libgzipf_file_open_wide(
     libgzipf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBGZIPF_EXTERN \
int libgzipf_file_open_file_io_handle(
     libgzipf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_close(
     libgzipf_file_t *file,
     libcerror_error_t **error );

int libgzipf_file_open_read(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_get_number_of_members(
     libgzipf_file_t *file,
     int *number_of_members,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_get_member(
     libgzipf_file_t *file,
     int member_index,
     libgzipf_member_t **member,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_FILE_H ) */

