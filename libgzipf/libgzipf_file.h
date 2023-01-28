/*
 * File functions
 *
 * Copyright (C) 2019-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_ZLIB ) || defined( ZLIB_DLL )
#include <zlib.h>
#endif  

#include "libgzipf_bit_stream.h"
#include "libgzipf_compressed_segment.h"
#include "libgzipf_extern.h"
#include "libgzipf_huffman_tree.h"
#include "libgzipf_io_handle.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcdata.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcthreads.h"
#include "libgzipf_libfdata.h"
#include "libgzipf_libfcache.h"
#include "libgzipf_member_descriptor.h"
#include "libgzipf_segment_descriptor.h"
#include "libgzipf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libgzipf_internal_file libgzipf_internal_file_t;

struct libgzipf_internal_file
{
	/* The current (uncompressed data) offset
	 */
	off64_t current_offset;

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

	/* The member descriptor
	 */
	libgzipf_member_descriptor_t *member_descriptor;

	/* The member descriptors array
	 */
	libcdata_array_t *member_descriptors_array;

	/* Value to indicate the members have been read
	 */
	uint8_t members_read;

	/* The segment descriptors array
	 */
	libcdata_array_t *segment_descriptors_array;

	/* The compressed data
	 */
	uint8_t *compressed_data;

#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
	/* The zlib stream
	 */
        z_stream zlib_stream;

	/* The last number of compressed stream bits
	 */
	uint8_t last_number_of_compressed_stream_bits;
#else
	/* The compressed data bit stream
	 */
	libgzipf_bit_stream_t *bit_stream;

	/* The fixed distances Huffman tree
	 */
        libgzipf_huffman_tree_t *fixed_huffman_distances_tree;

	/* The fixed literals Huffman tree
	 */
        libgzipf_huffman_tree_t *fixed_huffman_literals_tree;

	/* The last uncompressed block offset
	 */
	size_t last_uncompressed_block_offset;
#endif

	/* The uncompressed data
	 */
	uint8_t *uncompressed_data;

	/* The file size
	 */
	size64_t file_size;

	/* The compressed segments offset
	 */
	off64_t compressed_segments_offset;

	/* The uncompressed segments size
	 */
	size64_t uncompressed_segments_size;

	/* The compressed segments list
	 */
	libfdata_list_t *compressed_segments_list;

	/* The uncompressed data size
	 */
	size64_t uncompressed_data_size;

	/* The compressed segments cache
	 */
	libfcache_cache_t *compressed_segments_cache;

	/* Various flags
	 */
	uint8_t flags;

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

int libgzipf_internal_file_open_read(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libgzipf_internal_file_read_deflate_block(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libgzipf_member_descriptor_t *member_descriptor,
     libgzipf_segment_descriptor_t *segment_descriptor,
     size_t *compressed_block_size,
     uint8_t *is_last_block,
     uint8_t *decompression_error,
     libcerror_error_t **error );

int libgzipf_internal_file_read_deflate_stream(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libgzipf_member_descriptor_t *member_descriptor,
     libcerror_error_t **error );

int libgzipf_internal_file_read_member_header(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libgzipf_member_descriptor_t **member_descriptor,
     libcerror_error_t **error );

int libgzipf_internal_file_read_member_footer(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libgzipf_member_descriptor_t *member_descriptor,
     libcerror_error_t **error );

int libgzipf_internal_file_read_members(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libgzipf_internal_file_get_compressed_segment_at_offset(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     off64_t offset,
     off64_t *element_data_offset,
     libgzipf_compressed_segment_t **compressed_segment,
     libcerror_error_t **error );

ssize_t libgzipf_internal_file_read_buffer_from_file_io_handle(
         libgzipf_internal_file_t *internal_file,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBGZIPF_EXTERN \
ssize_t libgzipf_file_read_buffer(
         libgzipf_file_t *file,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBGZIPF_EXTERN \
ssize_t libgzipf_file_read_buffer_at_offset(
         libgzipf_file_t *file,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

off64_t libgzipf_internal_file_seek_offset(
         libgzipf_internal_file_t *internal_file,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBGZIPF_EXTERN \
off64_t libgzipf_file_seek_offset(
         libgzipf_file_t *file,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_get_offset(
     libgzipf_file_t *file,
     off64_t *offset,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_is_corrupted(
     libgzipf_file_t *file,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_get_uncompressed_data_size(
     libgzipf_file_t *file,
     size64_t *uncompressed_data_size,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_get_number_of_members(
     libgzipf_file_t *file,
     int *number_of_members,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_get_member_by_index(
     libgzipf_file_t *file,
     int member_index,
     libgzipf_member_t **member,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_FILE_H ) */

