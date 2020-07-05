/*
 * Members list functions
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

#include "libgzipf_libbfio.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libfdata.h"
#include "libgzipf_member_header.h"
#include "libgzipf_unused.h"

/* Reads a member
 * Returns 1 if successful or -1 on error
 */
int libgzipf_members_list_read_element_data(
     intptr_t *data_handle LIBGZIPF_ATTRIBUTE_UNUSED,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int data_range_file_index LIBGZIPF_ATTRIBUTE_UNUSED,
     off64_t data_range_offset,
     size64_t data_range_size,
     uint32_t data_range_flags LIBGZIPF_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBGZIPF_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libgzipf_member_header_t *member_header = NULL;
	static char *function                   = "libgzipf_members_list_read_element_data";

	LIBGZIPF_UNREFERENCED_PARAMETER( data_handle )
	LIBGZIPF_UNREFERENCED_PARAMETER( data_range_file_index )
	LIBGZIPF_UNREFERENCED_PARAMETER( data_range_flags )
	LIBGZIPF_UNREFERENCED_PARAMETER( read_flags )

	if( libgzipf_member_header_initialize(
	     &member_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create member header.",
		 function );

		goto on_error;
	}
	if( libgzipf_member_header_read_file_io_handle(
	     member_header,
	     file_io_handle,
	     data_range_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read member header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 data_range_offset,
		 data_range_offset );

		goto on_error;
	}
/* TODO
	if( libfdata_list_element_set_element_value(
	     element,
	     (intptr_t *) file_io_handle,
	     cache,
	     (intptr_t *) hive_bin,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libgzipf_hive_bin_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set hive bin as element value.",
		 function );

		goto on_error;
	}
*/
	if( libgzipf_member_header_free(
	     &member_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free member header.",
		 function );

		return( -1 );
	}
	return( 1 );

on_error:
	if( member_header != NULL )
	{
		libgzipf_member_header_free(
		 &member_header,
		 NULL );
	}
	return( -1 );
}


