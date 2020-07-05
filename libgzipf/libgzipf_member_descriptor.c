/*
 * Member descriptor functions
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

#include "libgzipf_libcerror.h"
#include "libgzipf_member_descriptor.h"

/* Creates member descriptor
 * Make sure the value member_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_initialize(
     libgzipf_member_descriptor_t **member_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_initialize";

	if( member_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member descriptor.",
		 function );

		return( -1 );
	}
	if( *member_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid member descriptor value already set.",
		 function );

		return( -1 );
	}
	*member_descriptor = memory_allocate_structure(
	                  libgzipf_member_descriptor_t );

	if( *member_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create member descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *member_descriptor,
	     0,
	     sizeof( libgzipf_member_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear member descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *member_descriptor != NULL )
	{
		memory_free(
		 *member_descriptor );

		*member_descriptor = NULL;
	}
	return( -1 );
}

/* Frees member descriptor
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_free(
     libgzipf_member_descriptor_t **member_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_free";

	if( member_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid member descriptor.",
		 function );

		return( -1 );
	}
	if( *member_descriptor != NULL )
	{
		if( ( *member_descriptor )->name != NULL )
		{
			memory_free(
			 ( *member_descriptor )->name );
		}
		if( ( *member_descriptor )->comments != NULL )
		{
			memory_free(
			 ( *member_descriptor )->comments );
		}
		memory_free(
		 *member_descriptor );

		*member_descriptor = NULL;
	}
	return( 1 );
}

