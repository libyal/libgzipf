/*
 * Compression functions
 *
 * Copyright (C) 2018-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_ZLIB ) || defined( ZLIB_DLL )
#include <zlib.h>
#endif

#include "libgzipf_compression.h"
#include "libgzipf_definitions.h"
#include "libgzipf_deflate.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcnotify.h"

/* Decompresses data using the compression method
 * Returns 1 on success, 0 on failure or -1 on error
 */
int libgzipf_decompress_data(
     const uint8_t *compressed_data,
     size_t *compressed_data_size,
     int compression_method,
     uint8_t *uncompressed_data,
     size_t *uncompressed_data_size,
     uint8_t *is_last_block,
     libcerror_error_t **error )
{
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
	z_stream zlib_stream;

	size_t last_compressed_data_size   = 0;
	size_t safe_compressed_data_size   = 0;
	size_t safe_uncompressed_data_size = 0;
	uint8_t decompression_error        = 0;
	uint8_t safe_is_last_block         = 0;
#else
	libgzipf_deflate_bit_stream_t bit_stream;

	size_t uncompressed_data_offset    = 0;
#endif

	static char *function              = "libgzipf_decompress_data";
	int result                         = 0;

	if( compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed data buffer.",
		 function );

		return( -1 );
	}
	if( compressed_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed data size.",
		 function );

		return( -1 );
	}
	if( compression_method != LIBGZIPF_COMPRESSION_METHOD_DEFLATE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported compression method.",
		 function );

		return( -1 );
	}
	if( uncompressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid uncompressed data buffer.",
		 function );

		return( -1 );
	}
	if( uncompressed_data == compressed_data )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed data buffer equals uncompressed data buffer.",
		 function );

		return( -1 );
	}
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
	if( *compressed_data_size > (size_t) ULONG_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid compressed data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( *uncompressed_data_size > (size_t) ULONG_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid uncompressed data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( is_last_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid is last block.",
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
	zlib_stream.next_in   = (Bytef *) compressed_data;
	zlib_stream.avail_in  = (uInt) *compressed_data_size;
	zlib_stream.next_out  = (Bytef *) uncompressed_data;
	zlib_stream.avail_out = (uInt) *uncompressed_data_size;

	while( ( safe_is_last_block == 0 )
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
			safe_is_last_block = ( result == Z_STREAM_END );
		}
		else if( result == Z_DATA_ERROR )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unable to read compressed data: data error.\n",
				 function );
			}
#endif
			return( -1 );
		}
		else if( result == Z_BUF_ERROR )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				"%s: unable to read compressed data: no progress possible.\n",
				 function );
			}
#endif
			if( safe_compressed_data_size == last_compressed_data_size )
			{
				decompression_error = 1;
			}
			else
			{
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
	result = 1;

	*compressed_data_size   = safe_compressed_data_size;
	*uncompressed_data_size = safe_uncompressed_data_size;
	*is_last_block          = safe_is_last_block;

#else
	if( *compressed_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid compressed data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	bit_stream.byte_stream        = compressed_data;
	bit_stream.byte_stream_size   = *compressed_data_size;
	bit_stream.byte_stream_offset = 0;
	bit_stream.bit_buffer         = 0;
	bit_stream.bit_buffer_size    = 0;

	result = libgzipf_deflate_read_block(
	          &bit_stream,
	          uncompressed_data,
	          *uncompressed_data_size,
	          &uncompressed_data_offset,
	          is_last_block,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ENCRYPTION,
		 LIBCERROR_ENCRYPTION_ERROR_GENERIC,
		 "%s: unable to decompress DEFLATE compressed data.",
		 function );

		return( -1 );
	}
	/* Correct for the remaining bytes in the bit-stream buffer
	 */
	while( bit_stream.bit_buffer_size >= 8 )
	{
		bit_stream.byte_stream_offset -= 1;
		bit_stream.bit_buffer_size    -= 8;
	}
	*compressed_data_size   = bit_stream.byte_stream_offset;
	*uncompressed_data_size = uncompressed_data_offset;

#endif /* ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL ) */

	return( result );
}

