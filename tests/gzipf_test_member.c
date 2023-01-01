/*
 * Library member type test program
 *
 * Copyright (C) 2019-2023, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libgzipf/libgzipf_member.h"

#if defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT )

#endif /* defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT ) */

/* Tests the libgzipf_member_free function
 * Returns 1 if successful or 0 if not
 */
int gzipf_test_member_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libgzipf_member_free(
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

	/* TODO: add tests for libgzipf_member_initialize */

#endif /* defined( __GNUC__ ) && !defined( LIBGZIPF_DLL_IMPORT ) */

	GZIPF_TEST_RUN(
	 "libgzipf_member_free",
	 gzipf_test_member_free );

	/* TODO: add tests for libgzipf_member_get_modification_time */

	/* TODO: add tests for libgzipf_member_get_utf8_name_size */

	/* TODO: add tests for libgzipf_member_get_utf8_name */

	/* TODO: add tests for libgzipf_member_get_utf16_name_size */

	/* TODO: add tests for libgzipf_member_get_utf16_name */

	/* TODO: add tests for libgzipf_member_get_utf8_comments_size */

	/* TODO: add tests for libgzipf_member_get_utf8_comments */

	/* TODO: add tests for libgzipf_member_get_utf16_comments_size */

	/* TODO: add tests for libgzipf_member_get_utf16_comments */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

