/*
 * Member functions
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBGZIPF_MEMBER_H )
#define _LIBGZIPF_MEMBER_H

#include <common.h>
#include <types.h>

#include "libgzipf_extern.h"
#include "libgzipf_io_handle.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcthreads.h"
#include "libgzipf_member_descriptor.h"
#include "libgzipf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libgzipf_internal_member libgzipf_internal_member_t;

struct libgzipf_internal_member
{
	/* The IO handle
	 */
	libgzipf_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The member descriptor
	 */
	libgzipf_member_descriptor_t *member_descriptor;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libgzipf_member_initialize(
     libgzipf_member_t **member,
     libgzipf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libgzipf_member_descriptor_t *member_descriptor,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_free(
     libgzipf_member_t **member,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_modification_time(
     libgzipf_member_t *member,
     uint32_t *posix_time,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_utf8_name_size(
     libgzipf_member_t *member,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_utf8_name(
     libgzipf_member_t *member,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_utf16_name_size(
     libgzipf_member_t *member,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_utf16_name(
     libgzipf_member_t *member,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_utf8_comments_size(
     libgzipf_member_t *member,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_utf8_comments(
     libgzipf_member_t *member,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_utf16_comments_size(
     libgzipf_member_t *member,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_utf16_comments(
     libgzipf_member_t *member,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_member_get_operating_system(
     libgzipf_member_t *member,
     uint8_t *operating_system,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_MEMBER_H ) */

