/*
 * Member descriptor functions
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

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_MEMBER_DESCRIPTOR_H ) */

