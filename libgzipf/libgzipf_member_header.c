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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libgzipf_debug.h"
#include "libgzipf_io_handle.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcnotify.h"
#include "libgzipf_libfdatetime.h"
#include "libgzipf_member_header.h"

#include "gzipf_member_header.h"

/* Creates member header
 * Make sure the value member_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_header_initialize(
     libgzipf_member_header_t **member_header,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_header_initialize";

	if( member_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member header.",
		 function );

		return( -1 );
	}
	if( *member_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid member header value already set.",
		 function );

		return( -1 );
	}
	*member_header = memory_allocate_structure(
	                  libgzipf_member_header_t );

	if( *member_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create member header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *member_header,
	     0,
	     sizeof( libgzipf_member_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear member header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *member_header != NULL )
	{
		memory_free(
		 *member_header );

		*member_header = NULL;
	}
	return( -1 );
}

/* Frees member header
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_header_free(
     libgzipf_member_header_t **member_header,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_header_free";

	if( member_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member header.",
		 function );

		return( -1 );
	}
	if( *member_header != NULL )
	{
		memory_free(
		 *member_header );

		*member_header = NULL;
	}
	return( 1 );
}

/* Reads the member header data
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_header_read_data(
     libgzipf_member_header_t *member_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_header_read_data";

	if( member_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member header.",
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
	if( data_size < sizeof( gzipf_member_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: member header:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( gzipf_member_header_t ),
		 0 );
	}
#endif
	if( ( ( ( (gzipf_member_header_t *) data )->signature[ 0 ] ) != 0x1f )
	 || ( ( ( (gzipf_member_header_t *) data )->signature[ 1 ] ) != 0x8b ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (gzipf_member_header_t *) data )->modification_time,
	 member_header->modification_time );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: \\x%02" PRIx8 "\\x%02" PRIx8 "\n",
		 function,
		 ( (gzipf_member_header_t *) data )->signature[ 0 ],
		 ( (gzipf_member_header_t *) data )->signature[ 1 ] );

		libcnotify_printf(
		 "%s: compression method\t\t\t: %" PRIu8 " (%s)\n",
		 function,
		 ( (gzipf_member_header_t *) data )->compression_method,
		 libgzipf_debug_print_compression_method(
		  ( (gzipf_member_header_t *) data )->compression_method ) );

		libcnotify_printf(
		 "%s: flags\t\t\t\t\t: %" PRIu8 "\n",
		 function,
		 ( (gzipf_member_header_t *) data )->flags );
		libgzipf_debug_print_flags(
		 ( (gzipf_member_header_t *) data )->flags );
		libcnotify_printf(
		 "\n" );

		if( libgzipf_debug_print_posix_time_value(
		     function,
		     "modification time\t\t\t",
		     ( (gzipf_member_header_t *) data )->modification_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print POSIX time value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: compression flags\t\t\t: %" PRIu8 "\n",
		 function,
		 ( (gzipf_member_header_t *) data )->compression_flags );

		libcnotify_printf(
		 "%s: operating system\t\t\t: %" PRIu8 "\n",
		 function,
		 ( (gzipf_member_header_t *) data )->operating_system );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( ( (gzipf_member_header_t *) data )->compression_method != 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported compression method: %" PRIu8 ".",
		 function,
		 ( (gzipf_member_header_t *) data )->compression_method );

		return( -1 );
	}
	return( 1 );
}

/* Reads the member header
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_header_read_file_io_handle(
     libgzipf_member_header_t *member_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t member_header_data[ sizeof( gzipf_member_header_t ) ];

	static char *function = "libgzipf_member_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( member_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading member header at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek member header offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              member_header_data,
	              sizeof( gzipf_member_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( gzipf_member_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read member header data.",
		 function );

		return( -1 );
	}
	if( libgzipf_member_header_read_data(
	     member_header,
	     member_header_data,
	     sizeof( gzipf_member_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read member header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

