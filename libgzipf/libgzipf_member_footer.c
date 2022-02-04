/*
 * Member footer functions
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
#include "libgzipf_io_handle.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcnotify.h"
#include "libgzipf_libfdatetime.h"
#include "libgzipf_member_footer.h"

#include "gzipf_member_footer.h"

/* Creates member footer
 * Make sure the value member_footer is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_footer_initialize(
     libgzipf_member_footer_t **member_footer,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_footer_initialize";

	if( member_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member footer.",
		 function );

		return( -1 );
	}
	if( *member_footer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid member footer value already set.",
		 function );

		return( -1 );
	}
	*member_footer = memory_allocate_structure(
	                  libgzipf_member_footer_t );

	if( *member_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create member footer.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *member_footer,
	     0,
	     sizeof( libgzipf_member_footer_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear member footer.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *member_footer != NULL )
	{
		memory_free(
		 *member_footer );

		*member_footer = NULL;
	}
	return( -1 );
}

/* Frees member footer
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_footer_free(
     libgzipf_member_footer_t **member_footer,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_footer_free";

	if( member_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member footer.",
		 function );

		return( -1 );
	}
	if( *member_footer != NULL )
	{
		memory_free(
		 *member_footer );

		*member_footer = NULL;
	}
	return( 1 );
}

/* Reads the member footer data
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_footer_read_data(
     libgzipf_member_footer_t *member_footer,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_footer_read_data";

	if( member_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member footer.",
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
	if( data_size < sizeof( gzipf_member_footer_t ) )
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
		 "%s: member footer:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( gzipf_member_footer_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (gzipf_member_footer_t *) data )->checksum,
	 member_footer->checksum );

	byte_stream_copy_to_uint32_little_endian(
	 ( (gzipf_member_footer_t *) data )->uncompressed_data_size,
	 member_footer->uncompressed_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 member_footer->checksum );

		libcnotify_printf(
		 "%s: uncompressed data size\t\t: %" PRIu32 "\n",
		 function,
		 member_footer->uncompressed_data_size );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the member footer
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_footer_read_file_io_handle(
     libgzipf_member_footer_t *member_footer,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t member_footer_data[ sizeof( gzipf_member_footer_t ) ];

	static char *function = "libgzipf_member_footer_read_file_io_handle";
	ssize_t read_count    = 0;

	if( member_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member footer.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading member footer at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              member_footer_data,
	              sizeof( gzipf_member_footer_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( gzipf_member_footer_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read member footer data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libgzipf_member_footer_read_data(
	     member_footer,
	     member_footer_data,
	     sizeof( gzipf_member_footer_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read member footer.",
		 function );

		return( -1 );
	}
	return( 1 );
}

