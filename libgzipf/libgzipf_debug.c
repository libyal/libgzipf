/*
 * Debug functions
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
#include <memory.h>
#include <types.h>

#include "libgzipf_debug.h"
#include "libgzipf_definitions.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcnotify.h"
#include "libgzipf_libfdatetime.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the flags
 */
void libgzipf_debug_print_flags(
      uint8_t flags )
{
	if( ( flags & 0x01 ) != 0 )
	{
		libcnotify_printf(
		 "\tData is text (FTEXT)\n" );
	}
	if( ( flags & 0x02 ) != 0 )
	{
		libcnotify_printf(
		 "\tHas header checksum (FHCRC)\n" );
	}
	if( ( flags & 0x04 ) != 0 )
	{
		libcnotify_printf(
		 "\tHas extra fields (FEXTRA)\n" );
	}
	if( ( flags & 0x08 ) != 0 )
	{
		libcnotify_printf(
		 "\tHas name (FNAME)\n" );
	}
	if( ( flags & 0x10 ) != 0 )
	{
		libcnotify_printf(
		 "\tHas comment (FCOMMENT)\n" );
	}

	if( ( flags & 0x20 ) != 0 )
	{
		libcnotify_printf(
		 "\tUnknown 0x20\n" );
	}
	if( ( flags & 0x40 ) != 0 )
	{
		libcnotify_printf(
		 "\tUnknown 0x40\n" );
	}
	if( ( flags & 0x80 ) != 0 )
	{
		libcnotify_printf(
		 "\tUnknown 0x80\n" );
	}
}

/* Prints the compression method
 */
const char *libgzipf_debug_print_compression_method(
             uint8_t compression_method )
{
	switch( compression_method )
	{
		case 8:
			return( "deflate" );
	}
	return( "_UNKNOWN_" );
}

/* Prints a POSIX value
 * Returns 1 if successful or -1 on error
 */
int libgzipf_debug_print_posix_time_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint8_t value_type,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	char date_time_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	static char *function                 = "libgzipf_debug_print_posix_time_value";

	if( libfdatetime_posix_time_initialize(
	     &posix_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create POSIX time.",
		 function );

		goto on_error;
	}
	if( libfdatetime_posix_time_copy_from_byte_stream(
	     posix_time,
	     byte_stream,
	     byte_stream_size,
	     byte_order,
	     value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream to POSIX time.",
		 function );

		goto on_error;
	}
	if( libfdatetime_posix_time_copy_to_utf8_string(
	     posix_time,
	     (uint8_t *) date_time_string,
	     32,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy POSIX time to string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s UTC\n",
	 function_name,
	 value_name,
	 date_time_string );

	if( libfdatetime_posix_time_free(
	     &posix_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free POSIX time.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( -1 );
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libgzipf_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file io handle.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 offset_iterator );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + size,
		 offset + size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

