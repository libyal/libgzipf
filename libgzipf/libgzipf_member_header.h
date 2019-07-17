/*
 * Member header functions
 *
 * Copyright (C) 2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBGZIPF_MEMBER_HEADER_H )
#define _LIBGZIPF_MEMBER_HEADER_H

#include <common.h>
#include <types.h>

#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libgzipf_member_header libgzipf_member_header_t;

struct libgzipf_member_header
{
	/* The modification date and time
	 */
	uint32_t modification_time;
};

int libgzipf_member_header_initialize(
     libgzipf_member_header_t **member_header,
     libcerror_error_t **error );

int libgzipf_member_header_free(
     libgzipf_member_header_t **member_header,
     libcerror_error_t **error );

int libgzipf_member_header_read_data(
     libgzipf_member_header_t *member_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libgzipf_member_header_read_file_io_handle(
     libgzipf_member_header_t *member_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_MEMBER_HEADER_H ) */
