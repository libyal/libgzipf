/*
 * Compressed segment functions
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libgzipf_compressed_segment.h"
#include "libgzipf_compression.h"
#include "libgzipf_definitions.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcnotify.h"
#include "libgzipf_libfdata.h"
#include "libgzipf_unused.h"

/* Creates compressed segment
 * Make sure the value compressed_segment is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libgzipf_compressed_segment_initialize(
     libgzipf_compressed_segment_t **compressed_segment,
     size64_t compressed_data_size,
     size64_t uncompressed_data_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_compressed_segment_initialize";

	if( compressed_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed segment.",
		 function );

		return( -1 );
	}
	if( *compressed_segment != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid compressed segment value already set.",
		 function );

		return( -1 );
	}
	if( ( compressed_data_size == 0 )
	 || ( compressed_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid compressed data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( uncompressed_data_size == 0 )
	 || ( uncompressed_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid uncompressed data size value out of bounds.",
		 function );

		return( -1 );
	}
	*compressed_segment = memory_allocate_structure(
	                       libgzipf_compressed_segment_t );

	if( *compressed_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed segment.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *compressed_segment,
	     0,
	     sizeof( libgzipf_compressed_segment_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear compressed segment.",
		 function );

		memory_free(
		 *compressed_segment );

		*compressed_segment = NULL;

		return( -1 );
	}
	( *compressed_segment )->compressed_data = (uint8_t *) memory_allocate(
	                                                        sizeof( uint8_t ) * (size_t) compressed_data_size );

	if( ( *compressed_segment )->compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed data.",
		 function );

		goto on_error;
	}
	( *compressed_segment )->compressed_data_size = compressed_data_size;

	( *compressed_segment )->uncompressed_data = (uint8_t *) memory_allocate(
	                                                          sizeof( uint8_t ) * (size_t) uncompressed_data_size );

	if( ( *compressed_segment )->uncompressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create uncompressed data.",
		 function );

		goto on_error;
	}
	( *compressed_segment )->uncompressed_data_size = uncompressed_data_size;

	return( 1 );

on_error:
	if( *compressed_segment != NULL )
	{
		if( ( *compressed_segment )->compressed_data != NULL )
		{
			memory_free(
			 ( *compressed_segment )->compressed_data );
		}
		memory_free(
		 *compressed_segment );

		*compressed_segment = NULL;
	}
	return( -1 );
}

/* Frees compressed segment
 * Returns 1 if successful or -1 on error
 */
int libgzipf_compressed_segment_free(
     libgzipf_compressed_segment_t **compressed_segment,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_compressed_segment_free";
	int result            = 1;

	if( compressed_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed segment.",
		 function );

		return( -1 );
	}
	if( *compressed_segment != NULL )
	{
		if( ( *compressed_segment )->uncompressed_data != NULL )
		{
			if( memory_set(
			     ( *compressed_segment )->uncompressed_data,
			     0,
			     ( *compressed_segment )->uncompressed_data_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_SET_FAILED,
				 "%s: unable to clear uncompressed data.",
				 function );

				result = -1;
			}
			memory_free(
			 ( *compressed_segment )->uncompressed_data );
		}
		if( ( *compressed_segment )->compressed_data != NULL )
		{
			if( memory_set(
			     ( *compressed_segment )->compressed_data,
			     0,
			     ( *compressed_segment )->compressed_data_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_SET_FAILED,
				 "%s: unable to clear compressed data.",
				 function );

				result = -1;
			}
			memory_free(
			 ( *compressed_segment )->compressed_data );
		}
		memory_free(
		 *compressed_segment );

		*compressed_segment = NULL;
	}
	return( result );
}

/* Reads the compressed segment
 * Returns 1 if successful or -1 on error
 */
int libgzipf_compressed_segment_read_file_io_handle(
     libgzipf_compressed_segment_t *compressed_segment,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	static char *function         = "libgzipf_compressed_segment_read_file_io_handle";
	size_t uncompressed_data_size = 0;
	ssize_t read_count            = 0;
	uint8_t is_last_segment       = 0;

	if( compressed_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed segment.",
		 function );

		return( -1 );
	}
	if( compressed_segment->compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid compressed segment - missing compressed data value.",
		 function );

		return( -1 );
	}
	if( compressed_segment->uncompressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid compressed segment - missing uncompressed data value.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading compressed segment at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              compressed_segment->compressed_data,
	              compressed_segment->compressed_data_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) compressed_segment->compressed_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	uncompressed_data_size = compressed_segment->uncompressed_data_size;

/* TODO decompress more than 1 block */
	if( libgzipf_decompress_data(
	     compressed_segment->compressed_data,
	     (size_t *) &read_count,
	     LIBGZIPF_COMPRESSION_METHOD_DEFLATE,
	     compressed_segment->uncompressed_data,
	     &uncompressed_data_size,
	     &is_last_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ENCRYPTION,
		 LIBCERROR_ENCRYPTION_ERROR_GENERIC,
		 "%s: unable to decompress data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
/* TODO compare uncompressed_data_size  and compressed_segment->uncompressed_data_size */

	return( 1 );
}

/* Reads a compressed segment
 * Returns 1 if successful or -1 on error
 */
int libgzipf_compressed_segment_read_element_data(
     intptr_t *data_handle LIBGZIPF_ATTRIBUTE_UNUSED,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int data_range_file_index LIBGZIPF_ATTRIBUTE_UNUSED,
     off64_t data_range_offset,
     size64_t data_range_size,
     uint32_t data_range_flags LIBGZIPF_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBGZIPF_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libgzipf_compressed_segment_t *compressed_segment = NULL;
	static char *function                             = "libgzipf_compressed_segment_read_element_data";
	size64_t mapped_size                              = 0;

	LIBGZIPF_UNREFERENCED_PARAMETER( data_handle )
	LIBGZIPF_UNREFERENCED_PARAMETER( data_range_file_index )
	LIBGZIPF_UNREFERENCED_PARAMETER( data_range_flags )
	LIBGZIPF_UNREFERENCED_PARAMETER( read_flags )

	if( libfdata_list_element_get_mapped_size(
	     element,
	     &mapped_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element mapped size.",
		 function );

		goto on_error;
	}
	if( libgzipf_compressed_segment_initialize(
	     &compressed_segment,
	     data_range_size,
	     mapped_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create compressed segment.",
		 function );

		goto on_error;
	}
	if( libgzipf_compressed_segment_read_file_io_handle(
	     compressed_segment,
	     file_io_handle,
	     data_range_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed segment at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 data_range_offset,
		 data_range_offset );

		goto on_error;
	}
	if( libfdata_list_element_set_element_value(
	     element,
	     (intptr_t *) file_io_handle,
	     cache,
	     (intptr_t *) compressed_segment,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libgzipf_compressed_segment_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set compressed segment as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( compressed_segment != NULL )
	{
		libgzipf_compressed_segment_free(
		 &compressed_segment,
		 NULL );
	}
	return( -1 );
}


