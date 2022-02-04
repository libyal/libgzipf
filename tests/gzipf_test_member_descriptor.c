/*
 * Library member_descriptor type test program
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

#include "gzipf_test_libcerror.h"
#include "gzipf_test_libgzipf.h"
#include "gzipf_test_macros.h"
#include "gzipf_test_memory.h"
#include "gzipf_test_unused.h"

#include "../libgzipf/libgzipf_member_descriptor.h"

#if defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT )

/* Tests the libgzipf_member_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_initialize(
     void )
{
	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	int result                                      = 0;

#if defined( HAVE_GZIPF_TEST_MEMORY )
	int number_of_malloc_fail_tests                 = 1;
	int number_of_memset_fail_tests                 = 1;
	int test_number                                 = 0;
#endif

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libgzipf_member_descriptor_initialize(
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

	member_descriptor = (libgzipf_member_descriptor_t *) 0x12345678UL;

	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	member_descriptor = NULL;

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
		/* Test libgzipf_member_descriptor_initialize with malloc failing
		 */
		gzipf_test_malloc_attempts_before_fail = test_number;

		result = libgzipf_member_descriptor_initialize(
		          &member_descriptor,
		          &error );

		if( gzipf_test_malloc_attempts_before_fail != -1 )
		{
			gzipf_test_malloc_attempts_before_fail = -1;

			if( member_descriptor != NULL )
			{
				libgzipf_member_descriptor_free(
				 &member_descriptor,
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
			 "member_descriptor",
			 member_descriptor );

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
		/* Test libgzipf_member_descriptor_initialize with memset failing
		 */
		gzipf_test_memset_attempts_before_fail = test_number;

		result = libgzipf_member_descriptor_initialize(
		          &member_descriptor,
		          &error );

		if( gzipf_test_memset_attempts_before_fail != -1 )
		{
			gzipf_test_memset_attempts_before_fail = -1;

			if( member_descriptor != NULL )
			{
				libgzipf_member_descriptor_free(
				 &member_descriptor,
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
			 "member_descriptor",
			 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libgzipf_member_descriptor_free(
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

/* Tests the libgzipf_member_descriptor_get_modification_time function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_modification_time(
     void )
{
	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	uint32_t modification_time                      = 0;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_modification_time(
	          member_descriptor,
	          &modification_time,
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
	result = libgzipf_member_descriptor_get_modification_time(
	          NULL,
	          &modification_time,
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

	result = libgzipf_member_descriptor_get_modification_time(
	          member_descriptor,
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

	/* Clean up
	 */
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_get_utf8_name_size function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_utf8_name_size(
     void )
{
	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	size_t utf8_string_size                         = 0;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_utf8_name_size(
	          member_descriptor,
	          &utf8_string_size,
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
	result = libgzipf_member_descriptor_get_utf8_name_size(
	          NULL,
	          &utf8_string_size,
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

	result = libgzipf_member_descriptor_get_utf8_name_size(
	          member_descriptor,
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

	/* Clean up
	 */
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_get_utf8_name function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_utf8_name(
     void )
{
	uint8_t utf8_string[ 512 ];

	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_utf8_name(
	          member_descriptor,
	          utf8_string,
	          512,
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
	result = libgzipf_member_descriptor_get_utf8_name(
	          NULL,
	          utf8_string,
	          512,
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

	result = libgzipf_member_descriptor_get_utf8_name(
	          member_descriptor,
	          NULL,
	          512,
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

	result = libgzipf_member_descriptor_get_utf8_name(
	          member_descriptor,
	          utf8_string,
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

	result = libgzipf_member_descriptor_get_utf8_name(
	          member_descriptor,
	          utf8_string,
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
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_get_utf16_name_size function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_utf16_name_size(
     void )
{
	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	size_t utf16_string_size                        = 0;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_utf16_name_size(
	          member_descriptor,
	          &utf16_string_size,
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
	result = libgzipf_member_descriptor_get_utf16_name_size(
	          NULL,
	          &utf16_string_size,
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

	result = libgzipf_member_descriptor_get_utf16_name_size(
	          member_descriptor,
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

	/* Clean up
	 */
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_get_utf16_name function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_utf16_name(
     void )
{
	uint16_t utf16_string[ 512 ];

	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_utf16_name(
	          member_descriptor,
	          utf16_string,
	          512,
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
	result = libgzipf_member_descriptor_get_utf16_name(
	          NULL,
	          utf16_string,
	          512,
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

	result = libgzipf_member_descriptor_get_utf16_name(
	          member_descriptor,
	          NULL,
	          512,
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

	result = libgzipf_member_descriptor_get_utf16_name(
	          member_descriptor,
	          utf16_string,
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

	result = libgzipf_member_descriptor_get_utf16_name(
	          member_descriptor,
	          utf16_string,
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
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_get_utf8_comments_size function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_utf8_comments_size(
     void )
{
	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	size_t utf8_string_size                         = 0;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_utf8_comments_size(
	          member_descriptor,
	          &utf8_string_size,
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
	result = libgzipf_member_descriptor_get_utf8_comments_size(
	          NULL,
	          &utf8_string_size,
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

	result = libgzipf_member_descriptor_get_utf8_comments_size(
	          member_descriptor,
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

	/* Clean up
	 */
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_get_utf8_comments function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_utf8_comments(
     void )
{
	uint8_t utf8_string[ 512 ];

	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_utf8_comments(
	          member_descriptor,
	          utf8_string,
	          512,
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
	result = libgzipf_member_descriptor_get_utf8_comments(
	          NULL,
	          utf8_string,
	          512,
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

	result = libgzipf_member_descriptor_get_utf8_comments(
	          member_descriptor,
	          NULL,
	          512,
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

	result = libgzipf_member_descriptor_get_utf8_comments(
	          member_descriptor,
	          utf8_string,
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

	result = libgzipf_member_descriptor_get_utf8_comments(
	          member_descriptor,
	          utf8_string,
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
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_get_utf16_comments_size function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_utf16_comments_size(
     void )
{
	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	size_t utf16_string_size                        = 0;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_utf16_comments_size(
	          member_descriptor,
	          &utf16_string_size,
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
	result = libgzipf_member_descriptor_get_utf16_comments_size(
	          NULL,
	          &utf16_string_size,
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

	result = libgzipf_member_descriptor_get_utf16_comments_size(
	          member_descriptor,
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

	/* Clean up
	 */
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libgzipf_member_descriptor_get_utf16_comments function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_descriptor_get_utf16_comments(
     void )
{
	uint16_t utf16_string[ 512 ];

	libcerror_error_t *error                        = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libgzipf_member_descriptor_initialize(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NOT_NULL(
	 "member_descriptor",
	 member_descriptor );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libgzipf_member_descriptor_get_utf16_comments(
	          member_descriptor,
	          utf16_string,
	          512,
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
	result = libgzipf_member_descriptor_get_utf16_comments(
	          NULL,
	          utf16_string,
	          512,
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

	result = libgzipf_member_descriptor_get_utf16_comments(
	          member_descriptor,
	          NULL,
	          512,
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

	result = libgzipf_member_descriptor_get_utf16_comments(
	          member_descriptor,
	          utf16_string,
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

	result = libgzipf_member_descriptor_get_utf16_comments(
	          member_descriptor,
	          utf16_string,
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
	result = libgzipf_member_descriptor_free(
	          &member_descriptor,
	          &error );

	GZIPF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	GZIPF_TEST_ASSERT_IS_NULL(
	 "member_descriptor",
	 member_descriptor );

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
	if( member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &member_descriptor,
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
	 "libgzipf_member_descriptor_initialize",
	 gzipf_test_member_descriptor_initialize );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_free",
	 gzipf_test_member_descriptor_free );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_modification_time",
	 gzipf_test_member_descriptor_get_modification_time );

/* TODO
	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_utf8_name_size",
	 gzipf_test_member_descriptor_get_utf8_name_size );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_utf8_name",
	 gzipf_test_member_descriptor_get_utf8_name );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_utf16_name_size",
	 gzipf_test_member_descriptor_get_utf16_name_size );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_utf16_name",
	 gzipf_test_member_descriptor_get_utf16_name );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_utf8_comments_size",
	 gzipf_test_member_descriptor_get_utf8_comments_size );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_utf8_comments",
	 gzipf_test_member_descriptor_get_utf8_comments );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_utf16_comments_size",
	 gzipf_test_member_descriptor_get_utf16_comments_size );

	GZIPF_TEST_RUN(
	 "libgzipf_member_descriptor_get_utf16_comments",
	 gzipf_test_member_descriptor_get_utf16_comments );
*/

#endif /* defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

