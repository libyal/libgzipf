/*
 * Member functions
 *
 * Copyright (C) 2011-2020, Joachim Metz <joachim.metz@gmail.com>
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

#include "libgzipf_definitions.h"
#include "libgzipf_io_handle.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_member.h"

/* Creates member
 * Make sure the value member is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_initialize(
     libgzipf_member_t **member,
     libgzipf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libgzipf_internal_member_t *internal_member = NULL;
	static char *function                       = "libgzipf_member_initialize";

	if( member == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member.",
		 function );

		return( -1 );
	}
	if( *member != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid member value already set.",
		 function );

		return( -1 );
	}
	internal_member = memory_allocate_structure(
	                   libgzipf_internal_member_t );

	if( internal_member == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create internal member.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_member,
	     0,
	     sizeof( libgzipf_internal_member_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear internal member.",
		 function );

		memory_free(
		 internal_member );

		return( -1 );
	}
	internal_member->file_io_handle = file_io_handle;
	internal_member->io_handle      = io_handle;

	*member = (libgzipf_member_t *) internal_member;

	return( 1 );

on_error:
	if( internal_member != NULL )
	{
		memory_free(
		 internal_member );
	}
	return( -1 );
}

/* Frees a member
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_free(
     libgzipf_member_t **member,
     libcerror_error_t **error )
{
	libgzipf_internal_member_t *internal_member = NULL;
	static char *function                       = "libgzipf_member_free";

	if( member == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member.",
		 function );

		return( -1 );
	}
	if( *member != NULL )
	{
		internal_member = (libgzipf_internal_member_t *) *member;
		*member         = NULL;

		/* The file_io_handle, io_handle and member_values references are freed elsewhere
		 */
		memory_free(
		 internal_member );
	}
	return( 1 );
}

