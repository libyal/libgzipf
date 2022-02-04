/*
 * Library member_footer type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "gzipf_test_functions.h"
#include "gzipf_test_libcerror.h"
#include "gzipf_test_libgzipf.h"
#include "gzipf_test_macros.h"
#include "gzipf_test_memory.h"
#include "gzipf_test_unused.h"

#include "../libgzipf/libgzipf_member_footer.h"

uint8_t gzipf_test_member_footer_data1[ 8 ] = {
	0xcc, 0x0e, 0x51, 0x9d, 0xdf, 0x04, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT )

/* Tests the libgzipf_member_footer_initialize function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_footer_initialize(
     void )
{
	libcerror_error_t *error                = NULL;
	libgzipf_member_footer_t *member_footer = NULL;
	int result                              = 0;

#if defined( HAVE_GZIPF_TEST_MEMORY )
	int number_of_malloc_fail_tests         = 1;
	int number_of_memset_fail_tests         = 1;
	int test_number                         = 0;
#endif

	/* Test regular cases
	 */
	result = libgzipf_member_footer_initialize(
	          &member_footer,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_footer",
	 member_footer );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libgzipf_member_footer_free(
	          &member_footer,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_footer",
	 member_footer );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_member_footer_initialize(
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

	member_footer = (libgzipf_member_footer_t *) 0x12345678UL;

	result = libgzipf_member_footer_initialize(
	          &member_footer,
	          &error );

	member_footer = NULL;

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
		/* Test libgzipf_member_footer_initialize with malloc failing
		 */
		gzipf_test_malloc_attempts_before_fail = test_number;

		result = libgzipf_member_footer_initialize(
		          &member_footer,
		          &error );

		if( gzipf_test_malloc_attempts_before_fail != -1 )
		{
			gzipf_test_malloc_attempts_before_fail = -1;

			if( member_footer != NULL )
			{
				libgzipf_member_footer_free(
				 &member_footer,
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
			 "member_footer",
			 member_footer );

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
		/* Test libgzipf_member_footer_initialize with memset failing
		 */
		gzipf_test_memset_attempts_before_fail = test_number;

		result = libgzipf_member_footer_initialize(
		          &member_footer,
		          &error );

		if( gzipf_test_memset_attempts_before_fail != -1 )
		{
			gzipf_test_memset_attempts_before_fail = -1;

			if( member_footer != NULL )
			{
				libgzipf_member_footer_free(
				 &member_footer,
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
			 "member_footer",
			 member_footer );

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
	if( member_footer != NULL )
	{
		libgzipf_member_footer_free(
		 &member_footer,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_footer_free function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_footer_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libgzipf_member_footer_free(
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

/* Tests the libgzipf_member_footer_read_data function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_footer_read_data(
     void )
{
	libcerror_error_t *error                = NULL;
	libgzipf_member_footer_t *member_footer = NULL;
	int result                              = 0;

	/* Initialize test
	 */
	result = libgzipf_member_footer_initialize(
	          &member_footer,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_footer",
	 member_footer );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_footer_read_data(
	          member_footer,
	          gzipf_test_member_footer_data1,
	          8,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	GZIPF_TEST_ASSERT_EQUAL_UINT32(
	 "member_footer->uncompressed_data_size",
	 member_footer->uncompressed_data_size,
	 1247 );

	/* Test error cases
	 */
	result = libgzipf_member_footer_read_data(
	          NULL,
	          gzipf_test_member_footer_data1,
	          8,
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

	result = libgzipf_member_footer_read_data(
	          member_footer,
	          NULL,
	          8,
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

	result = libgzipf_member_footer_read_data(
	          member_footer,
	          gzipf_test_member_footer_data1,
	          0,
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

	result = libgzipf_member_footer_read_data(
	          member_footer,
	          gzipf_test_member_footer_data1,
	          (size_t) SSIZE_MAX + 1,
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
	result = libgzipf_member_footer_free(
	          &member_footer,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_footer",
	 member_footer );

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
	if( member_footer != NULL )
	{
		libgzipf_member_footer_free(
		 &member_footer,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_footer_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_footer_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle        = NULL;
	libcerror_error_t *error                = NULL;
	libgzipf_member_footer_t *member_footer = NULL;
	int result                              = 0;

	/* Initialize test
	 */
	result = libgzipf_member_footer_initialize(
	          &member_footer,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_footer",
	 member_footer );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = gzipf_test_open_file_io_handle(
	          &file_io_handle,
	          gzipf_test_member_footer_data1,
	          8,
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

	/* Test regular cases
	 */
	result = libgzipf_member_footer_read_file_io_handle(
	          member_footer,
	          file_io_handle,
	          0,
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
	result = libgzipf_member_footer_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
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

	result = libgzipf_member_footer_read_file_io_handle(
	          member_footer,
	          NULL,
	          0,
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

	/* Clean up file IO handle
	 */
	result = gzipf_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small
	 */
	result = gzipf_test_open_file_io_handle(
	          &file_io_handle,
	          gzipf_test_member_footer_data1,
	          4,
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

	result = libgzipf_member_footer_read_file_io_handle(
	          member_footer,
	          file_io_handle,
	          0,
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

	result = gzipf_test_close_file_io_handle(
	          &file_io_handle,
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
	result = libgzipf_member_footer_free(
	          &member_footer,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_footer",
	 member_footer );

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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( member_footer != NULL )
	{
		libgzipf_member_footer_free(
		 &member_footer,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc GZIPF_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] GZIPF_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc GZIPF_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] GZIPF_TEST_ATTRIBUTE_UNUSED )
#endif
{
	GZIPF_TEST_UNREFERENCED_PARAMETER( argc )
	GZIPF_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT )

	GZIPF_TEST_RUN(
	 "libgzipf_member_footer_initialize",
	 gzipf_test_member_footer_initialize );

	GZIPF_TEST_RUN(
	 "libgzipf_member_footer_free",
	 gzipf_test_member_footer_free );

	GZIPF_TEST_RUN(
	 "libgzipf_member_footer_read_data",
	 gzipf_test_member_footer_read_data );

	GZIPF_TEST_RUN(
	 "libgzipf_member_footer_read_file_io_handle",
	 gzipf_test_member_footer_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

