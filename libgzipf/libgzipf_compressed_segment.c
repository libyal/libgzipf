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

#include <common.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_ZLIB ) || defined( ZLIB_DLL )
#include <zlib.h>
#endif

#include "libgzipf_compressed_segment.h"
#include "libgzipf_definitions.h"
#include "libgzipf_deflate.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcdata.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcnotify.h"
#include "libgzipf_libfdata.h"
#include "libgzipf_segment_descriptor.h"
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
int libgzipf_compressed_segment_read_data(
     libgzipf_compressed_segment_t *compressed_segment,
     libgzipf_segment_descriptor_t *segment_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
	z_stream zlib_stream;

	size_t data_offset                 = 0;
	size_t last_compressed_data_size   = 0;
	size_t safe_compressed_data_size   = 0;
	size_t safe_uncompressed_data_size = 0;
	uint8_t bit_shift                  = 0;
	uint8_t decompression_error        = 0;
	uint8_t is_last_block              = 0;
#else
	size_t uncompressed_data_size      = 0;
#endif

	static char *function              = "libgzipf_compressed_segment_read_data";
	int result                         = 0;

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
	if( compressed_segment->uncompressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed segment - missing uncompressed data.",
		 function );

		return( -1 );
	}
	if( segment_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment descriptor.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
	if( compressed_segment->uncompressed_data_size > (size_t) ULONG_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid uncompressed data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) ULONG_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     &zlib_stream,
	     0,
	     sizeof( z_stream ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear zlib stream.",
		 function );

		return( -1 );
	}
#if defined( HAVE_ZLIB_INFLATE_INIT2 ) || defined( ZLIB_DLL )
	result = inflateInit2(
	          &zlib_stream,
	          -15 );
#else
	result = _inflateInit2(
	          &zlib_stream,
	          -15 );
#endif
	if( result != Z_OK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize zlib stream.",
		 function );

		return( -1 );
	}
	if( segment_descriptor->number_of_bits > 0 )
	{
		bit_shift = 8 - segment_descriptor->number_of_bits;

		result = inflatePrime(
		          &zlib_stream,
		          (int) segment_descriptor->number_of_bits,
		          (int) data[ 0 ] >> bit_shift );

		if( result != Z_OK )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set compressed stream bits in zlib stream.",
			 function );

			return( -1 );
		}
		data_offset++;
	}
	result = inflateSetDictionary(
	          &zlib_stream,
	          segment_descriptor->distance_data,
	          (uInt) segment_descriptor->distance_data_size );

	if( result != Z_OK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set dictionary of zlib stream.",
		 function );

		return( -1 );
	}
	zlib_stream.next_in   = (Bytef *) &( data[ data_offset ] );
	zlib_stream.avail_in  = (uInt) data_size - data_offset;
	zlib_stream.next_out  = (Bytef *) compressed_segment->uncompressed_data;
	zlib_stream.avail_out = (uInt) compressed_segment->uncompressed_data_size;

	while( ( is_last_block == 0 )
	    && ( decompression_error == 0 ) )
	{
		last_compressed_data_size = safe_compressed_data_size;

		safe_compressed_data_size   += (size_t) zlib_stream.avail_in;
		safe_uncompressed_data_size += (size_t) zlib_stream.avail_out;

		result = inflate(
			  &zlib_stream,
			  Z_BLOCK );

		safe_compressed_data_size   -= (size_t) zlib_stream.avail_in;
		safe_uncompressed_data_size -= (size_t) zlib_stream.avail_out;

		if( ( result == Z_OK )
		 || ( result == Z_STREAM_END ) )
		{
			is_last_block = ( result == Z_STREAM_END );
		}
		else if( result == Z_DATA_ERROR )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to read compressed data: data error.",
			 function );

			return( -1 );
		}
		else if( result == Z_BUF_ERROR )
		{
			if( safe_compressed_data_size == last_compressed_data_size )
			{
				decompression_error = 1;
			}
			else
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to read compressed data: no progress possible.",
				 function );

				return( -1 );
			}
		}
		else if( result == Z_MEM_ERROR )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to read compressed data: insufficient memory.",
			 function );

			return( -1 );
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
			 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
			 "%s: zlib returned undefined error: %d.",
			 function,
			 result );

			return( -1 );
		}
	}
	if( inflateEnd(
	     &zlib_stream ) != Z_OK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to finalize zlib stream.",
		 function );

		return( -1 );
	}
/* TODO determine why size is sometimes 1-off
	if( safe_uncompressed_data_size != compressed_segment->uncompressed_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid uncompressed data size value out of bounds (%zd, %zd).",
		 function, safe_uncompressed_data_size, compressed_segment->uncompressed_data_size );

		return( -1 );
	}
*/
	return( 1 );

#else
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	uncompressed_data_size = compressed_segment->uncompressed_data_size;

	result = libgzipf_deflate_decompress(
	          data,
	          data_size,
	          compressed_segment->uncompressed_data,
	          &uncompressed_data_size,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ENCRYPTION,
		 LIBCERROR_ENCRYPTION_ERROR_GENERIC,
		 "%s: unable to decompress DEFLATE compressed data.",
		 function );

#if defined( HAVE_DEBUG_OUTPUT )
		if( ( error != NULL )
		 && ( *error != NULL ) )
		{
			libcnotify_print_error_backtrace(
			 *error );
		}
#endif
		libcerror_error_free(
		 error );

		result = 1;
	}
	return( result );

#endif /* ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL ) */
}

/* Reads the compressed segment
 * Returns 1 if successful or -1 on error
 */
int libgzipf_compressed_segment_read_file_io_handle(
     libgzipf_compressed_segment_t *compressed_segment,
     libgzipf_segment_descriptor_t *segment_descriptor,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_compressed_segment_read_file_io_handle";
	ssize_t read_count    = 0;

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
	if( segment_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment descriptor.",
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
	if( libgzipf_compressed_segment_read_data(
	     compressed_segment,
	     segment_descriptor,
	     compressed_segment->compressed_data,
	     (size_t) read_count,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads a compressed segment
 * Returns 1 if successful or -1 on error
 */
int libgzipf_compressed_segment_read_element_data(
     libcdata_array_t *segment_descriptors_array,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int segment_descriptor_index,
     off64_t data_range_offset,
     size64_t data_range_size,
     uint32_t data_range_flags LIBGZIPF_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBGZIPF_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libgzipf_compressed_segment_t *compressed_segment = NULL;
	libgzipf_segment_descriptor_t *segment_descriptor = NULL;
	static char *function                             = "libgzipf_compressed_segment_read_element_data";
	size64_t mapped_size                              = 0;

	LIBGZIPF_UNREFERENCED_PARAMETER( data_range_flags )
	LIBGZIPF_UNREFERENCED_PARAMETER( read_flags )

	if( libcdata_array_get_entry_by_index(
	     segment_descriptors_array,
	     segment_descriptor_index,
	     (intptr_t **) &segment_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment descriptor: %d.",
		 function,
		 segment_descriptor_index );

		goto on_error;
	}
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
	     segment_descriptor,
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


