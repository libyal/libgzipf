/*
 * Member header functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libgzipf_debug.h"
#include "libgzipf_definitions.h"
#include "libgzipf_io_handle.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcnotify.h"
#include "libgzipf_libfdatetime.h"
#include "libgzipf_libuna.h"
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
		if( ( *member_header )->name != NULL )
		{
			memory_free(
			 ( *member_header )->name );
		}
		if( ( *member_header )->comments != NULL )
		{
			memory_free(
			 ( *member_header )->comments );
		}
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
	static char *function   = "libgzipf_member_header_read_data";
	uint8_t supported_flags = 0x09;

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
	if( ( data_size < sizeof( gzipf_member_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
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
	member_header->flags = ( (gzipf_member_header_t *) data )->flags;

	byte_stream_copy_to_uint32_little_endian(
	 ( (gzipf_member_header_t *) data )->modification_time,
	 member_header->modification_time );

	member_header->operating_system = ( (gzipf_member_header_t *) data )->operating_system;

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
		 "%s: flags\t\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 member_header->flags );
		libgzipf_debug_print_flags(
		 member_header->flags );
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
		 "%s: compression flags\t\t\t: 0x%02" PRIx8 "\n",
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
	if( ( member_header->flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 member_header->flags );

		return( -1 );
	}
	return( 1 );
}

/* Reads the comments
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_header_read_comments(
     libgzipf_member_header_t *member_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t string_data[ 64 ];

	static char *function     = "libgzipf_member_header_read_comments";
	size_t string_data_offset = 0;
	size_t string_size        = 0;
	ssize_t read_count        = 0;
	off64_t read_size         = 0;
	int found_end_of_string   = 0;
	int recursion_depth       = 0;

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
	if( member_header->comments != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid member header - comments value already set.",
		 function );

		return( -1 );
	}
	while( found_end_of_string == 0 )
	{
		if( recursion_depth > LIBGZIPF_MAXIMUM_RECURSION_DEPTH )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid recursion depth value out of bounds.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
		              string_data,
		              64,
		              error );

		if( read_count < 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read member header data.",
			 function );

			goto on_error;
		}
		read_size += (size_t) read_count;

		for( string_data_offset = 0;
		     string_data_offset < 64;
		     string_data_offset++ )
		{
			string_size++;

			if( string_data[ string_data_offset ] == 0 )
			{
				found_end_of_string = 1;

				break;
			}
		}
		recursion_depth++;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: comments string size\t\t\t: %" PRIzd "\n",
		 function,
		 string_size );
	}
#endif
	if( ( string_size == 0 )
	 || ( string_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid comments string size value out of bounds.",
		 function );

		return( -1 );
	}
	member_header->comments = (uint8_t *) memory_allocate(
	                                       sizeof( uint8_t ) * string_size );

	if( member_header->comments == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create comments.",
		 function );

		goto on_error;
	}
	member_header->comments_size = string_size;

	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     -read_size,
	     SEEK_CUR,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek start of comments.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              member_header->comments,
	              string_size,
	              error );

	if( read_count != (ssize_t) string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read comments.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libgzipf_debug_print_string_value(
		     function,
		     "comments\t\t\t\t\t",
		     member_header->comments,
		     member_header->comments_size,
		     LIBUNA_CODEPAGE_ISO_8859_1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print string value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( member_header->comments != NULL )
	{
		memory_free(
		 member_header->comments );

		member_header->comments = NULL;
	}
	member_header->comments_size = 0;

	return( -1 );
}

/* Reads the name
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_header_read_name(
     libgzipf_member_header_t *member_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t string_data[ 64 ];

	static char *function     = "libgzipf_member_header_read_name";
	size_t string_data_offset = 0;
	size_t string_size        = 0;
	ssize_t read_count        = 0;
	off64_t read_size         = 0;
	int found_end_of_string   = 0;
	int recursion_depth       = 0;

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
	if( member_header->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid member header - name value already set.",
		 function );

		return( -1 );
	}
	while( found_end_of_string == 0 )
	{
		if( recursion_depth > LIBGZIPF_MAXIMUM_RECURSION_DEPTH )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid recursion depth value out of bounds.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
		              string_data,
		              64,
		              error );

		if( read_count < 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read member header data.",
			 function );

			goto on_error;
		}
		read_size += (size_t) read_count;

		for( string_data_offset = 0;
		     string_data_offset < 64;
		     string_data_offset++ )
		{
			string_size++;

			if( string_data[ string_data_offset ] == 0 )
			{
				found_end_of_string = 1;

				break;
			}
		}
		recursion_depth++;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: name string size\t\t\t: %" PRIzd "\n",
		 function,
		 string_size );
	}
#endif
	if( ( string_size == 0 )
	 || ( string_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid name string size value out of bounds.",
		 function );

		goto on_error;
	}
	member_header->name = (uint8_t *) memory_allocate(
	                                   sizeof( uint8_t ) * string_size );

	if( member_header->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		goto on_error;
	}
	member_header->name_size = string_size;

	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     -read_size,
	     SEEK_CUR,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek start of name.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              member_header->name,
	              string_size,
	              error );

	if( read_count != (ssize_t) string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read name.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libgzipf_debug_print_string_value(
		     function,
		     "name\t\t\t\t\t",
		     member_header->name,
		     member_header->name_size,
		     LIBUNA_CODEPAGE_ISO_8859_1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print string value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );

on_error:
	if( member_header->name != NULL )
	{
		memory_free(
		 member_header->name );

		member_header->name = NULL;
	}
	member_header->name_size = 0;

	return( -1 );
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
	if( member_header->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid member header - name value already set.",
		 function );

		return( -1 );
	}
	if( member_header->comments != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid member header - comments value already set.",
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
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              member_header_data,
	              sizeof( gzipf_member_header_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( gzipf_member_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read member header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
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

		goto on_error;
	}
	if( ( member_header->flags & 0x04 ) != 0 )
	{
/* TODO read 4 bytes and skip extra fields size */
	}
	if( ( member_header->flags & 0x08 ) != 0 )
	{
		if( libgzipf_member_header_read_name(
		     member_header,
		     file_io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read name.",
			 function );

			goto on_error;
		}
	}
	if( ( member_header->flags & 0x10 ) != 0 )
	{
		if( libgzipf_member_header_read_comments(
		     member_header,
		     file_io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read comments.",
			 function );

			goto on_error;
		}
	}
	if( ( member_header->flags & 0x02 ) != 0 )
	{
/* TODO read and check checksum */
	}
	return( 1 );

on_error:
	if( member_header->comments != NULL )
	{
		memory_free(
		 member_header->comments );

		member_header->comments = NULL;
	}
	member_header->comments_size = 0;

	if( member_header->name != NULL )
	{
		memory_free(
		 member_header->name );

		member_header->name = NULL;
	}
	member_header->name_size = 0;

	return( -1 );
}

