/*
 * Library file type test program
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
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( TIME_WITH_SYS_TIME )
#include <sys/time.h>
#include <time.h>
#elif defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#else
#include <time.h>
#endif

#include "gzipf_test_functions.h"
#include "gzipf_test_getopt.h"
#include "gzipf_test_libbfio.h"
#include "gzipf_test_libcerror.h"
#include "gzipf_test_libgzipf.h"
#include "gzipf_test_macros.h"
#include "gzipf_test_memory.h"

#include "../libgzipf/libgzipf_file.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make gzipf_test_file generate verbose output
#define GZIPF_TEST_FILE_VERBOSE
 */

#define GZIPF_TEST_FILE_READ_BUFFER_SIZE	4096

#if !defined( LIBGZIPF_HAVE_BFIO )

LIBGZIPF_EXTERN \
int libgzipf_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBGZIPF_EXTERN \
int libgzipf_file_open_file_io_handle(
     libgzipf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libgzipf_error_t **error );

#endif /* !defined( LIBGZIPF_HAVE_BFIO ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int gzipf_test_file_open_source(
     libgzipf_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "gzipf_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libgzipf_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = libgzipf_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBGZIPF_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libgzipf_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int gzipf_test_file_close_source(
     libgzipf_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "gzipf_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libgzipf_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libgzipf_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libgzipf_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libgzipf_file_t *file           = NULL;
	int result                      = 0;

#if defined( HAVE_GZIPF_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libgzipf_file_initialize(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libgzipf_file_free(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_initialize(
	          NULL,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = (libgzipf_file_t *) 0x12345678UL;

	result = libgzipf_file_initialize(
	          &file,
	          &error );

	file = NULL;

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_GZIPF_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libgzipf_file_initialize with malloc failing
		 */
		gzipf_test_malloc_attempts_before_fail = test_number;

		result = libgzipf_file_initialize(
		          &file,
		          &error );

		if( gzipf_test_malloc_attempts_before_fail != -1 )
		{
			gzipf_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libgzipf_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			GZIPF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			GZIPF_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			GZIPF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libgzipf_file_initialize with memset failing
		 */
		gzipf_test_memset_attempts_before_fail = test_number;

		result = libgzipf_file_initialize(
		          &file,
		          &error );

		if( gzipf_test_memset_attempts_before_fail != -1 )
		{
			gzipf_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libgzipf_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			GZIPF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			GZIPF_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			GZIPF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_GZIPF_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libgzipf_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_file_free function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libgzipf_file_free(
	          NULL,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libgzipf_file_open function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libgzipf_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = gzipf_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libgzipf_file_initialize(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libgzipf_file_open(
	          file,
	          narrow_source,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_open(
	          NULL,
	          narrow_source,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_open(
	          file,
	          NULL,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_open(
	          file,
	          narrow_source,
	          -1,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libgzipf_file_open(
	          file,
	          narrow_source,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libgzipf_file_free(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libgzipf_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libgzipf_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libgzipf_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = gzipf_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libgzipf_file_initialize(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libgzipf_file_open_wide(
	          file,
	          wide_source,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_open_wide(
	          NULL,
	          wide_source,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_open_wide(
	          file,
	          NULL,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_open_wide(
	          file,
	          wide_source,
	          -1,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libgzipf_file_open_wide(
	          file,
	          wide_source,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libgzipf_file_free(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libgzipf_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libgzipf_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libgzipf_file_t *file            = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libgzipf_file_initialize(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libgzipf_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          -1,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libgzipf_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBGZIPF_OPEN_READ,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libgzipf_file_free(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libgzipf_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_file_close function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libgzipf_file_close(
	          NULL,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libgzipf_file_open and libgzipf_file_close functions
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libgzipf_file_t *file    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libgzipf_file_initialize(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libgzipf_file_open_wide(
	          file,
	          source,
	          LIBGZIPF_OPEN_READ,
	          &error );
#else
	result = libgzipf_file_open(
	          file,
	          source,
	          LIBGZIPF_OPEN_READ,
	          &error );
#endif

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libgzipf_file_close(
	          file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libgzipf_file_open_wide(
	          file,
	          source,
	          LIBGZIPF_OPEN_READ,
	          &error );
#else
	result = libgzipf_file_open(
	          file,
	          source,
	          LIBGZIPF_OPEN_READ,
	          &error );
#endif

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libgzipf_file_close(
	          file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libgzipf_file_free(
	          &file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libgzipf_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_signal_abort(
     libgzipf_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libgzipf_file_signal_abort(
	          file,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_signal_abort(
	          NULL,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT )

/* Tests the libgzipf_internal_file_read_buffer_from_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_internal_file_read_buffer_from_file_io_handle(
     libgzipf_file_t *file )
{
	uint8_t buffer[ GZIPF_TEST_FILE_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	time_t timestamp         = 0;
	size64_t remaining_size  = 0;
	size64_t size            = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	off64_t read_offset      = 0;
	int number_of_tests      = 1024;
	int random_number        = 0;
	int result               = 0;
	int test_number          = 0;

	/* Determine size
	 */
	result = libgzipf_file_get_uncompressed_data_size(
	          file,
	          &size,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = GZIPF_TEST_FILE_READ_BUFFER_SIZE;

	if( size < GZIPF_TEST_FILE_READ_BUFFER_SIZE )
	{
		read_size = (size_t) size;
	}
	read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
	              (libgzipf_internal_file_t *) file,
	              ( (libgzipf_internal_file_t *) file )->file_io_handle,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( size > 8 )
	{
		/* Set offset to size - 8
		 */
		offset = libgzipf_file_seek_offset(
		          file,
		          -8,
		          SEEK_END,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) size - 8 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer on size boundary
		 */
		read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
		              (libgzipf_internal_file_t *) file,
		              ( (libgzipf_internal_file_t *) file )->file_io_handle,
		              buffer,
		              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
		              &error );

		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond size boundary
		 */
		read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
		              (libgzipf_internal_file_t *) file,
		              ( (libgzipf_internal_file_t *) file )->file_io_handle,
		              buffer,
		              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
		              &error );

		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	remaining_size = size;

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		GZIPF_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		read_size = (size_t) random_number % GZIPF_TEST_FILE_READ_BUFFER_SIZE;

#if defined( GZIPF_TEST_FILE_VERBOSE )
		fprintf(
		 stdout,
		 "libgzipf_file_read_buffer: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 read_offset,
		 read_offset,
		 read_size );
#endif
		read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
		              (libgzipf_internal_file_t *) file,
		              ( (libgzipf_internal_file_t *) file )->file_io_handle,
		              buffer,
		              read_size,
		              &error );

		if( read_size > remaining_size )
		{
			read_size = (size_t) remaining_size;
		}
		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		read_offset += read_count;

		result = libgzipf_file_get_offset(
		          file,
		          &offset,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		GZIPF_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 read_offset );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		remaining_size -= read_count;

		if( remaining_size == 0 )
		{
			offset = libgzipf_file_seek_offset(
			          file,
			          0,
			          SEEK_SET,
			          &error );

			GZIPF_TEST_ASSERT_EQUAL_INT64(
			 "offset",
			 offset,
			 (int64_t) 0 );

			GZIPF_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			read_offset = 0;

			remaining_size = size;
		}
	}
	/* Reset offset to 0
	 */
	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
	              NULL,
	              ( (libgzipf_internal_file_t *) file )->file_io_handle,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
	              (libgzipf_internal_file_t *) file,
	              ( (libgzipf_internal_file_t *) file )->file_io_handle,
	              NULL,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
	              (libgzipf_internal_file_t *) file,
	              ( (libgzipf_internal_file_t *) file )->file_io_handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT ) */

/* Tests the libgzipf_file_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_read_buffer(
     libgzipf_file_t *file )
{
	uint8_t buffer[ GZIPF_TEST_FILE_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	time_t timestamp         = 0;
	size64_t remaining_size  = 0;
	size64_t size            = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	off64_t read_offset      = 0;
	int number_of_tests      = 1024;
	int random_number        = 0;
	int result               = 0;
	int test_number          = 0;

	/* Determine size
	 */
	result = libgzipf_file_get_uncompressed_data_size(
	          file,
	          &size,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = GZIPF_TEST_FILE_READ_BUFFER_SIZE;

	if( size < GZIPF_TEST_FILE_READ_BUFFER_SIZE )
	{
		read_size = (size_t) size;
	}
	read_count = libgzipf_file_read_buffer(
	              file,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( size > 8 )
	{
		/* Set offset to size - 8
		 */
		offset = libgzipf_file_seek_offset(
		          file,
		          -8,
		          SEEK_END,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) size - 8 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer on size boundary
		 */
		read_count = libgzipf_file_read_buffer(
		              file,
		              buffer,
		              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
		              &error );

		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond size boundary
		 */
		read_count = libgzipf_file_read_buffer(
		              file,
		              buffer,
		              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
		              &error );

		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	remaining_size = size;

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		GZIPF_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		read_size = (size_t) random_number % GZIPF_TEST_FILE_READ_BUFFER_SIZE;

#if defined( GZIPF_TEST_FILE_VERBOSE )
		fprintf(
		 stdout,
		 "libgzipf_file_read_buffer: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 read_offset,
		 read_offset,
		 read_size );
#endif
		read_count = libgzipf_file_read_buffer(
		              file,
		              buffer,
		              read_size,
		              &error );

		if( read_size > remaining_size )
		{
			read_size = (size_t) remaining_size;
		}
		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		read_offset += read_count;

		result = libgzipf_file_get_offset(
		          file,
		          &offset,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		GZIPF_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 read_offset );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		remaining_size -= read_count;

		if( remaining_size == 0 )
		{
			offset = libgzipf_file_seek_offset(
			          file,
			          0,
			          SEEK_SET,
			          &error );

			GZIPF_TEST_ASSERT_EQUAL_INT64(
			 "offset",
			 offset,
			 (int64_t) 0 );

			GZIPF_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			read_offset = 0;

			remaining_size = size;
		}
	}
	/* Reset offset to 0
	 */
	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libgzipf_file_read_buffer(
	              NULL,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libgzipf_file_read_buffer(
	              file,
	              NULL,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libgzipf_file_read_buffer(
	              file,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_GZIPF_TEST_RWLOCK )

	/* Test libgzipf_file_read_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	gzipf_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libgzipf_file_read_buffer(
	              file,
	              buffer,
	              GZIPF_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	if( gzipf_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		gzipf_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		GZIPF_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libgzipf_file_read_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	gzipf_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libgzipf_file_read_buffer(
	              file,
	              buffer,
	              GZIPF_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	if( gzipf_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		gzipf_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		GZIPF_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GZIPF_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libgzipf_file_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_read_buffer_at_offset(
     libgzipf_file_t *file )
{
	uint8_t buffer[ GZIPF_TEST_FILE_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	time_t timestamp         = 0;
	size64_t remaining_size  = 0;
	size64_t size            = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	off64_t read_offset      = 0;
	int number_of_tests      = 1024;
	int random_number        = 0;
	int result               = 0;
	int test_number          = 0;

	/* Determine size
	 */
	result = libgzipf_file_get_uncompressed_data_size(
	          file,
	          &size,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = GZIPF_TEST_FILE_READ_BUFFER_SIZE;

	if( size < GZIPF_TEST_FILE_READ_BUFFER_SIZE )
	{
		read_size = (size_t) size;
	}
	read_count = libgzipf_file_read_buffer_at_offset(
	              file,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( size > 8 )
	{
		/* Read buffer on size boundary
		 */
		read_count = libgzipf_file_read_buffer_at_offset(
		              file,
		              buffer,
		              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
		              size - 8,
		              &error );

		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond size boundary
		 */
		read_count = libgzipf_file_read_buffer_at_offset(
		              file,
		              buffer,
		              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
		              size + 8,
		              &error );

		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		GZIPF_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		if( size > 0 )
		{
			read_offset = (off64_t) random_number % size;
		}
		read_size = (size_t) random_number % GZIPF_TEST_FILE_READ_BUFFER_SIZE;

#if defined( GZIPF_TEST_FILE_VERBOSE )
		fprintf(
		 stdout,
		 "libgzipf_file_read_buffer_at_offset: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 read_offset,
		 read_offset,
		 read_size );
#endif
		read_count = libgzipf_file_read_buffer_at_offset(
		              file,
		              buffer,
		              read_size,
		              read_offset,
		              &error );

		remaining_size = size - read_offset;

		if( read_size > remaining_size )
		{
			read_size = (size_t) remaining_size;
		}
		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		read_offset += read_count;

		result = libgzipf_file_get_offset(
		          file,
		          &offset,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		GZIPF_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 read_offset );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	read_count = libgzipf_file_read_buffer_at_offset(
	              NULL,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libgzipf_file_read_buffer_at_offset(
	              file,
	              NULL,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libgzipf_file_read_buffer_at_offset(
	              file,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              0,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libgzipf_file_read_buffer_at_offset(
	              file,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              -1,
	              &error );

	GZIPF_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_GZIPF_TEST_RWLOCK )

	/* Test libgzipf_file_read_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	gzipf_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libgzipf_file_read_buffer_at_offset(
	              file,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	if( gzipf_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		gzipf_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		GZIPF_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libgzipf_file_read_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	gzipf_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libgzipf_file_read_buffer_at_offset(
	              file,
	              buffer,
	              GZIPF_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	if( gzipf_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		gzipf_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		GZIPF_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		GZIPF_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GZIPF_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libgzipf_file_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_seek_offset(
     libgzipf_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;

	/* Test regular cases
	 */
	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_END,
	          &error );

	GZIPF_TEST_ASSERT_NOT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size = (size64_t) offset;

	offset = libgzipf_file_seek_offset(
	          file,
	          1024,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 1024 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libgzipf_file_seek_offset(
	          file,
	          -512,
	          SEEK_CUR,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 512 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libgzipf_file_seek_offset(
	          file,
	          (off64_t) ( size + 512 ),
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) ( size + 512 ) );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libgzipf_file_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libgzipf_file_seek_offset(
	          file,
	          -1,
	          SEEK_SET,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libgzipf_file_seek_offset(
	          file,
	          -1,
	          SEEK_CUR,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	offset = libgzipf_file_seek_offset(
	          file,
	          (off64_t) ( -1 * ( size + 1 ) ),
	          SEEK_END,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_GZIPF_TEST_RWLOCK )

	/* Test libgzipf_file_seek_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	gzipf_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	if( gzipf_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		gzipf_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		GZIPF_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		GZIPF_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libgzipf_file_seek_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	gzipf_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	offset = libgzipf_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	if( gzipf_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		gzipf_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		GZIPF_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		GZIPF_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GZIPF_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libgzipf_file_get_offset function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_get_offset(
     libgzipf_file_t *file )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libgzipf_file_get_offset(
	          file,
	          &offset,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_get_offset(
	          NULL,
	          &offset,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_get_offset(
	          file,
	          NULL,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libgzipf_file_get_uncompressed_data_size function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_get_uncompressed_data_size(
     libgzipf_file_t *file )
{
	libcerror_error_t *error        = NULL;
	size64_t uncompressed_data_size = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libgzipf_file_get_uncompressed_data_size(
	          file,
	          &uncompressed_data_size,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_get_uncompressed_data_size(
	          NULL,
	          &uncompressed_data_size,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_get_uncompressed_data_size(
	          file,
	          NULL,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libgzipf_file_get_number_of_members function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_get_number_of_members(
     libgzipf_file_t *file )
{
	libcerror_error_t *error = NULL;
	int number_of_members    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libgzipf_file_get_number_of_members(
	          file,
	          &number_of_members,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_get_number_of_members(
	          NULL,
	          &number_of_members,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_get_number_of_members(
	          file,
	          NULL,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libgzipf_file_get_member_by_index function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_file_get_member_by_index(
     libgzipf_file_t *file )
{
	libcerror_error_t *error  = NULL;
	libgzipf_member_t *member = NULL;
	int result                = 0;

	/* Test regular cases
	 */
	result = libgzipf_file_get_member_by_index(
	          file,
	          0,
	          &member,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member",
	 member );

	result = libgzipf_member_free(
	          &member,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_file_get_member_by_index(
	          NULL,
	          0,
	          &member,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member",
	 member );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_get_member_by_index(
	          file,
	          -1,
	          &member,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member",
	 member );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libgzipf_file_get_member_by_index(
	          file,
	          0,
	          NULL,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member",
	 member );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( member != NULL )
	{
		libgzipf_member_free(
		 &member,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libgzipf_file_t *file            = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = gzipf_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( GZIPF_TEST_FILE_VERBOSE )
	libgzipf_notify_set_verbose(
	 1 );
	libgzipf_notify_set_stream(
	 stderr,
	 NULL );
#endif

	GZIPF_TEST_RUN(
	 "libgzipf_file_initialize",
	 gzipf_test_file_initialize );

	GZIPF_TEST_RUN(
	 "libgzipf_file_free",
	 gzipf_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        GZIPF_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        GZIPF_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		GZIPF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        GZIPF_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libgzipf_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		GZIPF_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_open",
		 gzipf_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_open_wide",
		 gzipf_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_open_file_io_handle",
		 gzipf_test_file_open_file_io_handle,
		 source );

		GZIPF_TEST_RUN(
		 "libgzipf_file_close",
		 gzipf_test_file_close );

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_open_close",
		 gzipf_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = gzipf_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		GZIPF_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_signal_abort",
		 gzipf_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT )

		/* TODO: add tests for libgzipf_internal_file_open_read */

		/* TODO: add tests for libgzipf_internal_file_read_deflate_compressed_stream */

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_internal_file_read_buffer_from_file_io_handle",
		 gzipf_test_internal_file_read_buffer_from_file_io_handle,
		 file );

#endif /* defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT ) */

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_read_buffer",
		 gzipf_test_file_read_buffer,
		 file );

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_read_buffer_at_offset",
		 gzipf_test_file_read_buffer_at_offset,
		 file );

#if defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT )

		/* TODO: add tests for libgzipf_internal_file_seek_offset */

#endif /* defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT ) */

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_seek_offset",
		 gzipf_test_file_seek_offset,
		 file );

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_get_offset",
		 gzipf_test_file_get_offset,
		 file );

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_get_uncompressed_data_size",
		 gzipf_test_file_get_uncompressed_data_size,
		 file );

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_get_number_of_members",
		 gzipf_test_file_get_number_of_members,
		 file );

		GZIPF_TEST_RUN_WITH_ARGS(
		 "libgzipf_file_get_member_by_index",
		 gzipf_test_file_get_member_by_index,
		 file );

		/* Clean up
		 */
		result = gzipf_test_file_close_source(
		          &file,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		GZIPF_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		GZIPF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		GZIPF_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        GZIPF_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libgzipf_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

