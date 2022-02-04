/*
 * Segment descriptor functions
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

#if !defined( _LIBGZIPF_SEGMENT_DESCRIPTOR_H )
#define _LIBGZIPF_SEGMENT_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libgzipf_definitions.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libgzipf_segment_descriptor libgzipf_segment_descriptor_t;

struct libgzipf_segment_descriptor
{
	/* The compressed data offset
	 */
	off64_t compressed_data_offset;

	/* The compressed data size
	 */
	size_t compressed_data_size;

	/* The uncompressed data size
	 */
	size_t uncompressed_data_size;

	/* The intial number of bits of the compressed block
	 */
	uint8_t number_of_bits;

	/* The preceeding 32 KiB of uncompressed data for distance codes
	 */
	uint8_t distance_data[ LIBGZIPF_MAXIMUM_DEFLATE_DISTANCE ];

	/* The distance data size
	 */
	size_t distance_data_size;
};

int libgzipf_segment_descriptor_initialize(
     libgzipf_segment_descriptor_t **segment_descriptor,
     libcerror_error_t **error );

int libgzipf_segment_descriptor_free(
     libgzipf_segment_descriptor_t **segment_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_SEGMENT_DESCRIPTOR_H ) */

