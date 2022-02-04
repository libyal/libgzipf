/*
 * Member descriptor functions
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

#include "libgzipf_libcerror.h"
#include "libgzipf_libuna.h"
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

/* Retrieves the modification time
 * The timestamp is a 32-bit POSIX date and time value
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_modification_time(
     libgzipf_member_descriptor_t *member_descriptor,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_modification_time";

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
	if( posix_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid POSIX time.",
		 function );

		return( -1 );
	}
	*posix_time = member_descriptor->modification_time;

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_utf8_name_size(
     libgzipf_member_descriptor_t *member_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_utf8_name_size";

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
	if( member_descriptor->name == NULL )
	{
		if( utf8_string_size == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid UTF-8 string size.",
			 function );

			return( -1 );
		}
		*utf8_string_size = 0;
	}
	else
	{
		if( libuna_utf8_string_size_from_byte_stream(
		     member_descriptor->name,
		     member_descriptor->name_size,
		     LIBUNA_CODEPAGE_ISO_8859_1,
		     utf8_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine size of UTF-8 string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_utf8_name(
     libgzipf_member_descriptor_t *member_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_utf8_name";

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
	if( libuna_utf8_string_copy_from_byte_stream(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     member_descriptor->name,
	     member_descriptor->name_size,
	     LIBUNA_CODEPAGE_ISO_8859_1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_utf16_name_size(
     libgzipf_member_descriptor_t *member_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_utf16_name_size";

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
	if( member_descriptor->name == NULL )
	{
		if( utf16_string_size == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid UTF-16 string size.",
			 function );

			return( -1 );
		}
		*utf16_string_size = 0;
	}
	else
	{
		if( libuna_utf16_string_size_from_byte_stream(
		     member_descriptor->name,
		     member_descriptor->name_size,
		     LIBUNA_CODEPAGE_ISO_8859_1,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine size of UTF-16 string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_utf16_name(
     libgzipf_member_descriptor_t *member_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_utf16_name";

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
	if( libuna_utf16_string_copy_from_byte_stream(
	     (libuna_utf16_character_t *) utf16_string,
	     utf16_string_size,
	     member_descriptor->name,
	     member_descriptor->name_size,
	     LIBUNA_CODEPAGE_ISO_8859_1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded comments
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_utf8_comments_size(
     libgzipf_member_descriptor_t *member_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_utf8_comments_size";

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
	if( member_descriptor->comments == NULL )
	{
		if( utf8_string_size == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid UTF-8 string size.",
			 function );

			return( -1 );
		}
		*utf8_string_size = 0;
	}
	else
	{
		if( libuna_utf8_string_size_from_byte_stream(
		     member_descriptor->comments,
		     member_descriptor->comments_size,
		     LIBUNA_CODEPAGE_ISO_8859_1,
		     utf8_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine size of UTF-8 string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded comments
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_utf8_comments(
     libgzipf_member_descriptor_t *member_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_utf8_comments";

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
	if( libuna_utf8_string_copy_from_byte_stream(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     member_descriptor->comments,
	     member_descriptor->comments_size,
	     LIBUNA_CODEPAGE_ISO_8859_1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded comments
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_utf16_comments_size(
     libgzipf_member_descriptor_t *member_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_utf16_comments_size";

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
	if( member_descriptor->comments == NULL )
	{
		if( utf16_string_size == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid UTF-16 string size.",
			 function );

			return( -1 );
		}
		*utf16_string_size = 0;
	}
	else
	{
		if( libuna_utf16_string_size_from_byte_stream(
		     member_descriptor->comments,
		     member_descriptor->comments_size,
		     LIBUNA_CODEPAGE_ISO_8859_1,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine size of UTF-16 string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded comments
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_utf16_comments(
     libgzipf_member_descriptor_t *member_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_utf16_comments";

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
	if( libuna_utf16_string_copy_from_byte_stream(
	     (libuna_utf16_character_t *) utf16_string,
	     utf16_string_size,
	     member_descriptor->comments,
	     member_descriptor->comments_size,
	     LIBUNA_CODEPAGE_ISO_8859_1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the operating system
 * Returns 1 if successful or -1 on error
 */
int libgzipf_member_descriptor_get_operating_system(
     libgzipf_member_descriptor_t *member_descriptor,
     uint8_t *operating_system,
     libcerror_error_t **error )
{
	static char *function = "libgzipf_member_descriptor_get_operating_system";

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
	if( operating_system == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid operating system.",
		 function );

		return( -1 );
	}
	*operating_system = member_descriptor->operating_system;

	return( 1 );
}

