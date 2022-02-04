/*
 * Member descriptor functions
 *
 * Copyright (C) 2019-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBGZIPF_MEMBER_DESCRIPTOR_H )
#define _LIBGZIPF_MEMBER_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libgzipf_member_descriptor libgzipf_member_descriptor_t;

struct libgzipf_member_descriptor
{
	/* The flags
	 */
	uint8_t flags;

	/* The modification date and time
	 */
	uint32_t modification_time;

	/* The name
	 */
	uint8_t *name;

	/* The name size
	 */
	size_t name_size;

	/* The comments
	 */
	uint8_t *comments;

	/* The comments size
	 */
	size_t comments_size;

	/* The operating system
	 */
	uint8_t operating_system;

	/* The compressed data offset
	 */
	off64_t compressed_data_offset;

	/* The uncompressed data size
	 */
	uint32_t uncompressed_data_size;

	/* The uncompressed data checksum
	 */
	uint32_t uncompressed_data_checksum;
};

int libgzipf_member_descriptor_initialize(
     libgzipf_member_descriptor_t **member_descriptor,
     libcerror_error_t **error );

int libgzipf_member_descriptor_free(
     libgzipf_member_descriptor_t **member_descriptor,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_modification_time(
     libgzipf_member_descriptor_t *member_descriptor,
     uint32_t *posix_time,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_utf8_name_size(
     libgzipf_member_descriptor_t *member_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_utf8_name(
     libgzipf_member_descriptor_t *member_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_utf16_name_size(
     libgzipf_member_descriptor_t *member_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_utf16_name(
     libgzipf_member_descriptor_t *member_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_utf8_comments_size(
     libgzipf_member_descriptor_t *member_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_utf8_comments(
     libgzipf_member_descriptor_t *member_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_utf16_comments_size(
     libgzipf_member_descriptor_t *member_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_utf16_comments(
     libgzipf_member_descriptor_t *member_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libgzipf_member_descriptor_get_operating_system(
     libgzipf_member_descriptor_t *member_descriptor,
     uint8_t *operating_system,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_MEMBER_DESCRIPTOR_H ) */

