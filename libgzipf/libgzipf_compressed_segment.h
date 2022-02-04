/*
 * Compressed segment functions
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

#if !defined( _LIBGZIPF_COMPRESSED_SEGMENT_H )
#define _LIBGZIPF_COMPRESSED_SEGMENT_H

#include <common.h>
#include <types.h>

#include "libgzipf_libbfio.h"
#include "libgzipf_libcdata.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libfdata.h"
#include "libgzipf_segment_descriptor.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libgzipf_compressed_segment libgzipf_compressed_segment_t;

struct libgzipf_compressed_segment
{
	/* The compressed data
	 */
	uint8_t *compressed_data;

	/* The compressed data size
	 */
	size_t compressed_data_size;

	/* The uncompressed data
	 */
	uint8_t *uncompressed_data;

	/* The uncompressed data size
	 */
	size_t uncompressed_data_size;
};

int libgzipf_compressed_segment_initialize(
     libgzipf_compressed_segment_t **compressed_segment,
     size64_t compressed_data_size,
     size64_t uncompressed_data_size,
     libcerror_error_t **error );

int libgzipf_compressed_segment_free(
     libgzipf_compressed_segment_t **compressed_segment,
     libcerror_error_t **error );

int libgzipf_compressed_segment_read_data(
     libgzipf_compressed_segment_t *compressed_segment,
     libgzipf_segment_descriptor_t *segment_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libgzipf_compressed_segment_read_file_io_handle(
     libgzipf_compressed_segment_t *compressed_segment,
     libgzipf_segment_descriptor_t *segment_descriptor,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libgzipf_compressed_segment_read_element_data(
     libcdata_array_t *segment_descriptors_array,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int segment_descriptor_index,
     off64_t data_range_offset,
     size64_t data_range_size,
     uint32_t data_range_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_COMPRESSED_SEGMENT_H ) */

