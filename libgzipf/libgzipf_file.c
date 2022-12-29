/*
 * File functions
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
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_ZLIB ) || defined( ZLIB_DLL )
#include <zlib.h>
#endif

#include "libgzipf_bit_stream.h"
#include "libgzipf_checksum.h"
#include "libgzipf_compressed_segment.h"
#include "libgzipf_debug.h"
#include "libgzipf_definitions.h"
#include "libgzipf_deflate.h"
#include "libgzipf_file.h"
#include "libgzipf_huffman_tree.h"
#include "libgzipf_io_handle.h"
#include "libgzipf_libbfio.h"
#include "libgzipf_libcdata.h"
#include "libgzipf_libcerror.h"
#include "libgzipf_libcnotify.h"
#include "libgzipf_libcthreads.h"
#include "libgzipf_libfcache.h"
#include "libgzipf_libfdata.h"
#include "libgzipf_member.h"
#include "libgzipf_member_descriptor.h"
#include "libgzipf_member_footer.h"
#include "libgzipf_member_header.h"
#include "libgzipf_segment_descriptor.h"
#include "libgzipf_types.h"

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_initialize(
     libgzipf_file_t **file,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_initialize";

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
	if( *file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file value already set.",
		 function );

		return( -1 );
	}
	internal_file = memory_allocate_structure(
	                 libgzipf_internal_file_t );

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_file,
	     0,
	     sizeof( libgzipf_internal_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	if( libgzipf_io_handle_initialize(
	     &( internal_file->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_file->member_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create member descriptors array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_file->segment_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create segment descriptors array.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_file->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	*file = (libgzipf_file_t *) internal_file;

	return( 1 );

on_error:
	if( internal_file != NULL )
	{
		if( internal_file->member_descriptors_array != NULL )
		{
			libcdata_array_free(
			 &( internal_file->member_descriptors_array ),
			 NULL,
			 NULL );
		}
		memory_free(
		 internal_file );
	}
	return( -1 );
}

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_free(
     libgzipf_file_t **file,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_free";
	int result                              = 1;

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
	if( *file != NULL )
	{
		internal_file = (libgzipf_internal_file_t *) *file;

		if( internal_file->file_io_handle != NULL )
		{
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
		}
		*file = NULL;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_file->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		if( libcdata_array_free(
		     &( internal_file->segment_descriptors_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libgzipf_segment_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the segment descriptors array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_file->member_descriptors_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libgzipf_segment_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the member descriptors array.",
			 function );

			result = -1;
		}
		if( libgzipf_io_handle_free(
		     &( internal_file->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_file );
	}
	return( result );
}

/* Signals the file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_signal_abort(
     libgzipf_file_t *file,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_signal_abort";

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_file->io_handle->abort = 1;

	return( 1 );
}

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_open(
     libgzipf_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle        = NULL;
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_open";
	size_t filename_length                  = 0;

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBGZIPF_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBGZIPF_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported accesss flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBGZIPF_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( libgzipf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

                goto on_error;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		goto on_error;
	}
#endif
	internal_file->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		internal_file->file_io_handle_created_in_library = 0;

		goto on_error;
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_open_wide(
     libgzipf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle        = NULL;
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_open_wide";
	size_t filename_length                  = 0;

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBGZIPF_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBGZIPF_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBGZIPF_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libgzipf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		goto on_error;
	}
#endif
	internal_file->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		internal_file->file_io_handle_created_in_library = 0;

		goto on_error;
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_open_file_io_handle(
     libgzipf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_open_file_io_handle";
	int bfio_access_flags                   = 0;
	int file_io_handle_is_open              = 0;
	int file_io_handle_opened_in_library    = 0;

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( internal_file->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - file IO handle already set.",
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
	if( ( ( access_flags & LIBGZIPF_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBGZIPF_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBGZIPF_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBGZIPF_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libgzipf_internal_file_open_read(
	     internal_file,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		goto on_error;
	}
#endif
	internal_file->file_io_handle                   = file_io_handle;
	internal_file->file_io_handle_opened_in_library = file_io_handle_opened_in_library;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		internal_file->file_io_handle                   = NULL;
		internal_file->file_io_handle_opened_in_library = 0;

		goto on_error;
	}
#endif
	return( 1 );

on_error:
	if( ( file_io_handle_is_open == 0 )
	 && ( file_io_handle_opened_in_library != 0 ) )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
int libgzipf_file_close(
     libgzipf_file_t *file,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_close";
	int result                              = 0;

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_file->file_io_handle_created_in_library != 0 )
		{
			if( libgzipf_debug_print_read_offsets(
			     internal_file->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_file->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_file->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_opened_in_library = 0;
	}
	if( internal_file->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_file->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_created_in_library = 0;
	}
	internal_file->file_io_handle = NULL;
	internal_file->current_offset = 0;

	if( libgzipf_io_handle_clear(
	     internal_file->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_file->member_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libgzipf_member_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty the member descriptors array.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_file->segment_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libgzipf_segment_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty the segment descriptors array.",
		 function );

		result = -1;
	}
	if( internal_file->compressed_segments_list != NULL )
	{
		if( libfdata_list_free(
		     &( internal_file->compressed_segments_list ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free compressed segments list.",
			 function );

			result = -1;
		}
	}
	if( internal_file->compressed_segments_cache != NULL )
	{
		if( libfcache_cache_free(
		     &( internal_file->compressed_segments_cache ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free compressed segments cache.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Opens a file for reading
 * Returns 1 if successful or -1 on error
 */
int libgzipf_internal_file_open_read(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libgzipf_member_descriptor_t *member_descriptor      = NULL;
	libgzipf_member_descriptor_t *safe_member_descriptor = NULL;
	libgzipf_member_footer_t *member_footer              = NULL;
	libgzipf_member_header_t *member_header              = NULL;
	static char *function                                = "libgzipf_internal_file_open_read";
	size64_t compressed_stream_size                      = 0;
	size64_t file_size                                   = 0;
	size64_t uncompressed_stream_size                    = 0;
	off64_t file_offset                                  = 0;
	uint32_t calculated_checksum                         = 0;
	int entry_index                                      = 0;
	int member_descriptor_index                          = 0;

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->compressed_segments_list != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - compressed segments list value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->compressed_segments_cache != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - compressed segments cache value already set.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		goto on_error;
	}
	if( libfdata_list_initialize(
	     &( internal_file->compressed_segments_list ),
	     (intptr_t *) internal_file->segment_descriptors_array,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_list_element_t *, libfdata_cache_t *, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libgzipf_compressed_segment_read_element_data,
	     NULL,
	     LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create compressed segments list.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading member header(s):\n" );
	}
#endif
	while( (size64_t) file_offset < file_size )
	{
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
		     file_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read member header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
#endif
			libcerror_error_free(
			 error );

			libgzipf_member_header_free(
			 &member_header,
			 NULL );

			internal_file->flags |= LIBGZIPF_FILE_FLAG_IS_CORRUPTED;

			break;
		}
		if( libbfio_handle_get_offset(
		     file_io_handle,
		     &file_offset,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to determine offset.",
			 function );

			goto on_error;
		}
		if( libgzipf_member_descriptor_initialize(
		     &safe_member_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create member descriptor.",
			 function );

			goto on_error;
		}
		safe_member_descriptor->flags                  = member_header->flags;
		safe_member_descriptor->modification_time      = member_header->modification_time;
		safe_member_descriptor->name                   = member_header->name;
		safe_member_descriptor->name_size              = member_header->name_size;
		safe_member_descriptor->comments               = member_header->comments;
		safe_member_descriptor->comments_size          = member_header->comments_size;
		safe_member_descriptor->operating_system       = member_header->operating_system;
		safe_member_descriptor->compressed_data_offset = file_offset;

		member_header->name          = NULL;
		member_header->name_size     = 0;
		member_header->comments      = NULL;
		member_header->comments_size = 0;

		if( libcdata_array_append_entry(
		     internal_file->member_descriptors_array,
		     &entry_index,
		     (intptr_t *) safe_member_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append member descriptor: %d.",
			 function,
			 member_descriptor_index );

			goto on_error;
		}
		member_descriptor      = safe_member_descriptor;
		safe_member_descriptor = NULL;

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

			goto on_error;
		}
		if( libgzipf_internal_file_read_deflate_compressed_stream(
		     internal_file,
		     file_io_handle,
		     file_offset,
		     &compressed_stream_size,
		     &uncompressed_stream_size,
		     &calculated_checksum,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read DEFLATE compressed stream at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
#endif
			libcerror_error_free(
			 error );

			internal_file->flags |= LIBGZIPF_FILE_FLAG_IS_CORRUPTED;

			break;
		}
		file_offset += compressed_stream_size;

		if( libgzipf_member_footer_initialize(
		     &member_footer,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create member footer.",
			 function );

			goto on_error;
		}
		if( libgzipf_member_footer_read_file_io_handle(
		     member_footer,
		     file_io_handle,
		     file_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read member footer at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		file_offset += 8;

		member_descriptor->uncompressed_data_size     = member_footer->uncompressed_data_size;
		member_descriptor->uncompressed_data_checksum = member_footer->checksum;

		if( libgzipf_member_footer_free(
		     &member_footer,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free member footer.",
			 function );

			goto on_error;
		}
		if( member_descriptor->uncompressed_data_size != uncompressed_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_INPUT,
			 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
			 "%s: mismatch in uncompressed stream size ( 0x%08" PRIx32 " != 0x%08" PRIx32 " ).",
			 function,
			 member_descriptor->uncompressed_data_size,
			 uncompressed_stream_size );

			goto on_error;
		}
		if( member_descriptor->uncompressed_data_checksum != calculated_checksum )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_INPUT,
			 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
			 "%s: mismatch in stream CRC-32 checksum ( 0x%08" PRIx32 " != 0x%08" PRIx32 " ).",
			 function,
			 member_descriptor->uncompressed_data_checksum,
			 calculated_checksum );

			goto on_error;
		}
		member_descriptor_index++;
	}
	if( libfdata_list_get_size(
	     internal_file->compressed_segments_list,
	     &( internal_file->uncompressed_data_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of compressed segments list.",
		 function );

		goto on_error;
	}
	if( libfcache_cache_initialize(
	     &( internal_file->compressed_segments_cache ),
	     LIBGZIPF_MAXIMUM_CACHE_ENTRIES_COMPRESSED_BLOCKS,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create compressed segments cache.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( member_footer != NULL )
	{
		libgzipf_member_footer_free(
		 &member_footer,
		 NULL );
	}
	if( member_header != NULL )
	{
		libgzipf_member_header_free(
		 &member_header,
		 NULL );
	}
	if( safe_member_descriptor != NULL )
	{
		libgzipf_member_descriptor_free(
		 &safe_member_descriptor,
		 NULL );
	}
	if( internal_file->compressed_segments_list != NULL )
	{
		libfdata_list_free(
		 &( internal_file->compressed_segments_list ),
		 NULL );
	}
	libcdata_array_free(
	 &( internal_file->segment_descriptors_array ),
	 (int (*)(intptr_t **, libcerror_error_t **)) &libgzipf_segment_descriptor_free,
	 NULL );

	libcdata_array_free(
	 &( internal_file->member_descriptors_array ),
	 (int (*)(intptr_t **, libcerror_error_t **)) &libgzipf_member_descriptor_free,
	 NULL );

	return( -1 );
}

/* Reads a DEFLATE compressed stream
 * Returns 1 if successful or -1 on error
 */
int libgzipf_internal_file_read_deflate_compressed_stream(
     libgzipf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     size64_t *compressed_stream_size,
     size64_t *uncompressed_stream_size,
     uint32_t *calculated_checksum,
     libcerror_error_t **error )
{
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
	z_stream zlib_stream;

	uInt safe_distance_data_size                          = 0;
	size_t last_compressed_block_size                     = 0;
	uint8_t end_of_block                                  = 0;
	int result                                            = 0;
#else
	libgzipf_bit_stream_t *bit_stream                     = NULL;
	libgzipf_huffman_tree_t *fixed_huffman_distances_tree = NULL;
	libgzipf_huffman_tree_t *fixed_huffman_literals_tree  = NULL;
	size_t copy_size                                      = 0;
	uint8_t block_type                                    = 0;
	uint8_t last_block_flag                               = 0;
#endif

	libgzipf_segment_descriptor_t *segment_descriptor     = NULL;
	uint8_t *compressed_data                              = NULL;
	uint8_t *uncompressed_data                            = NULL;
	static char *function                                 = "libgzipf_internal_file_read_deflate_compressed_stream";
	size64_t safe_compressed_stream_size                  = 0;
	size64_t safe_uncompressed_data_size                  = 0;
	size_t compressed_block_size                          = 0;
	size_t uncompressed_block_offset                      = 0;
	size_t uncompressed_block_size                        = 0;
	ssize_t read_count                                    = 0;
	off64_t compressed_block_offset                       = 0;
	off64_t uncompressed_data_offset                      = 0;
	uint32_t safe_calculated_checksum                     = 0;
	uint8_t decompression_error                           = 0;
	uint8_t is_last_block                                 = 0;
	uint8_t number_of_compressed_stream_bits              = 0;
	int element_index                                     = 0;
	int entry_index                                       = 0;
	int segment_descriptor_index                          = 0;

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( compressed_stream_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed stream size.",
		 function );

		return( -1 );
	}
	if( uncompressed_stream_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid uncompressed stream size.",
		 function );

		return( -1 );
	}
	if( calculated_checksum == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid calculated checksum.",
		 function );

		return( -1 );
	}
	compressed_data = (uint8_t *) memory_allocate(
	                               sizeof( uint8_t ) * LIBGZIPF_MAXIMUM_DEFLATE_BLOCK_SIZE );

	if( compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed data.",
		 function );

		goto on_error;
	}
	uncompressed_data = (uint8_t *) memory_allocate(
	                                 sizeof( uint8_t ) * LIBGZIPF_UNCOMPRESSED_BLOCK_SIZE );

	if( uncompressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create uncompressed data.",
		 function );

		goto on_error;
	}
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
	if( memory_set(
	     &zlib_stream,
	     0,
	     sizeof( z_stream ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear zlib stream.",
		 function );

		goto on_error;
	}
#if defined( HAVE_ZLIB_INFLATE_INIT2 ) || defined( ZLIB_DLL )
	result = inflateInit2(
	          &zlib_stream,
	          -15 );
#else
	result = _inflateInit2(
	          &zlib_stream,
	          -15 );
#endif
	if( result != Z_OK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize zlib stream.",
		 function );

		goto on_error;
	}
#else
	if( libgzipf_bit_stream_initialize(
	     &bit_stream,
	     compressed_data,
	     LIBGZIPF_MAXIMUM_DEFLATE_BLOCK_SIZE,
	     0,
	     LIBGZIPF_BIT_STREAM_STORAGE_TYPE_BYTE_BACK_TO_FRONT,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create bit stream.",
		 function );

		goto on_error;
	}
#endif /* ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL ) */

	compressed_block_offset = file_offset;

	while( is_last_block == 0 )
	{
		read_count = libbfio_handle_read_buffer_at_offset(
		              file_io_handle,
		              compressed_data,
		              LIBGZIPF_MAXIMUM_DEFLATE_BLOCK_SIZE,
		              file_offset,
		              error );

		if( read_count < 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read compressed data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		file_offset += read_count;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compressed block offset\t: 0x%08" PRIx32 "\n",
			 function,
			 compressed_block_offset );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( segment_descriptor == NULL )
		{
			if( libgzipf_segment_descriptor_initialize(
			     &segment_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create segment descriptor.",
				 function );

				goto on_error;
			}
			segment_descriptor->compressed_data_offset = compressed_block_offset;

			segment_descriptor->number_of_bits = number_of_compressed_stream_bits;

#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
			safe_distance_data_size = (uInt) LIBGZIPF_MAXIMUM_DEFLATE_DISTANCE;

			result = inflateGetDictionary(
			          &zlib_stream,
			          segment_descriptor->distance_data,
			          &safe_distance_data_size );

			if( result != Z_OK )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve dictionary from zlib stream.",
				 function );

				goto on_error;
			}
			segment_descriptor->distance_data_size = (size_t) safe_distance_data_size;
#else
			if( uncompressed_data_offset > 0 )
			{
				if( uncompressed_block_size < LIBGZIPF_MAXIMUM_DEFLATE_DISTANCE )
				{
					copy_size = uncompressed_block_size;
				}
				else
				{
					copy_size = LIBGZIPF_MAXIMUM_DEFLATE_DISTANCE;
				}
				uncompressed_block_offset = uncompressed_block_size - copy_size;

				if( memory_copy(
				     segment_descriptor->distance_data,
				     &( uncompressed_data[ uncompressed_block_offset ] ),
				     copy_size ) == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
					 "%s: unable to copy uncompressed data to distance data.",
					 function );

					goto on_error;
				}
			}
#endif /* ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL ) */
		}
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
		zlib_stream.next_in   = (Bytef *) compressed_data;
		zlib_stream.avail_in  = (uInt) read_count;
		zlib_stream.next_out  = (Bytef *) uncompressed_data;
		zlib_stream.avail_out = (uInt) LIBGZIPF_UNCOMPRESSED_BLOCK_SIZE;

		compressed_block_size     = 0;
		uncompressed_block_offset = 0;
		uncompressed_block_size   = 0;
		end_of_block              = 0;

		while( ( end_of_block == 0 )
		    && ( is_last_block == 0 )
		    && ( decompression_error == 0 ) )
		{
			last_compressed_block_size = compressed_block_size;

			compressed_block_size   += (size_t) zlib_stream.avail_in;
			uncompressed_block_size += (size_t) zlib_stream.avail_out;

			result = inflate(
				  &zlib_stream,
				  Z_BLOCK );

			compressed_block_size   -= (size_t) zlib_stream.avail_in;
			uncompressed_block_size -= (size_t) zlib_stream.avail_out;

			if( ( result == Z_OK )
			 || ( result == Z_STREAM_END ) )
			{
				number_of_compressed_stream_bits = (uint8_t) ( zlib_stream.data_type & 0x07 );
				end_of_block                     = ( ( zlib_stream.data_type & 0x80 ) != 0 );
				is_last_block                    = ( result == Z_STREAM_END );
			}
			else if( result == Z_DATA_ERROR )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: unable to read compressed data: data error.\n",
					 function );
				}
#endif
				goto on_error;
			}
			else if( result == Z_BUF_ERROR )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					"%s: unable to read compressed data: no progress possible.\n",
					 function );
				}
#endif
				if( compressed_block_size == last_compressed_block_size )
				{
					decompression_error = 1;
				}
				else
				{
					goto on_error;
				}
			}
			else if( result == Z_MEM_ERROR )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to read compressed data: insufficient memory.",
				 function );

				goto on_error;
			}
			else
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
				 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
				 "%s: zlib returned undefined error: %d.",
				 function,
				 result );

				goto on_error;
			}
		}
#else
		if( uncompressed_block_size > 0 )
		{
			if( uncompressed_block_size < LIBGZIPF_MAXIMUM_DEFLATE_DISTANCE )
			{
				copy_size = uncompressed_block_size;
			}
			else
			{
				copy_size = LIBGZIPF_MAXIMUM_DEFLATE_DISTANCE;
			}
			uncompressed_block_offset = uncompressed_block_size - copy_size;

			if( memory_copy(
			     uncompressed_data,
			     &( uncompressed_data[ uncompressed_block_offset ] ),
			     LIBGZIPF_MAXIMUM_DEFLATE_DISTANCE ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy uncompressed data to beginning of buffer.",
				 function );

				goto on_error;
			}
			uncompressed_block_offset = copy_size;
		}
		/* Do not flush the bit buffer */

		bit_stream->byte_stream_size   = (size_t) read_count;
		bit_stream->byte_stream_offset = 0;

		if( libgzipf_deflate_read_block_header(
		     bit_stream,
		     &block_type,
		     &last_block_flag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read compressed data block header.",
			 function );

			goto on_error;
		}
		if( block_type == LIBGZIPF_DEFLATE_BLOCK_TYPE_HUFFMAN_FIXED )
		{
			if( ( fixed_huffman_literals_tree == NULL )
			 && ( fixed_huffman_distances_tree == NULL ) )
			{
				if( libgzipf_huffman_tree_initialize(
				     &fixed_huffman_literals_tree,
				     288,
				     15,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to build fixed literals Huffman tree.",
					 function );

					goto on_error;
				}
				if( libgzipf_huffman_tree_initialize(
				     &fixed_huffman_distances_tree,
				     30,
				     15,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to build fixed distances Huffman tree.",
					 function );

					goto on_error;
				}
				if( libgzipf_deflate_build_fixed_huffman_trees(
				     fixed_huffman_literals_tree,
				     fixed_huffman_distances_tree,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to build fixed Huffman trees.",
					 function );

					goto on_error;
				}
			}
		}
		if( libgzipf_deflate_read_block(
		     bit_stream,
		     block_type,
		     fixed_huffman_literals_tree,
		     fixed_huffman_distances_tree,
		     uncompressed_data,
		     LIBGZIPF_UNCOMPRESSED_BLOCK_SIZE,
		     &uncompressed_block_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block of compressed data.",
			 function );

#if defined( HAVE_DEBUG_OUTPUT )
			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
#endif
			libcerror_error_free(
			 error );

			decompression_error = 1;
		}
		while( bit_stream->bit_buffer_size >= 8 )
		{
			bit_stream->byte_stream_offset -= 1;
			bit_stream->bit_buffer_size    -= 8;
		}
		compressed_block_size      = bit_stream->byte_stream_offset;
		uncompressed_block_size    = uncompressed_block_offset - uncompressed_block_size;
		uncompressed_block_offset -= uncompressed_block_size;

		is_last_block = ( last_block_flag != 0 );

#endif /* ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL ) */

		if( libgzipf_checksum_calculate_crc32(
		     &safe_calculated_checksum,
		     &( uncompressed_data[ uncompressed_block_offset ] ),
		     uncompressed_block_size,
		     safe_calculated_checksum,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ENCRYPTION,
			 LIBCERROR_ENCRYPTION_ERROR_GENERIC,
			 "%s: unable to calculate checksum.",
			 function );

			goto on_error;
		}
		uncompressed_block_offset += uncompressed_block_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compressed block size\t: %" PRIzd "\n",
			 function,
			 compressed_block_size );

			libcnotify_printf(
			 "%s: uncompressed block size\t: %" PRIzd "\n",
			 function,
			 uncompressed_block_size );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		compressed_block_offset     += compressed_block_size;
		safe_compressed_stream_size += compressed_block_size;
		safe_uncompressed_data_size += uncompressed_block_size;

		segment_descriptor->compressed_data_size   += compressed_block_size;
		segment_descriptor->uncompressed_data_size += uncompressed_block_size;

		file_offset = compressed_block_offset;

		if( ( segment_descriptor->compressed_data_size >= LIBGZIPF_COMPRESSED_SEGMENT_SIZE )
		 || ( is_last_block != 0 )
		 || ( decompression_error != 0 ) )
		{
			if( segment_descriptor->number_of_bits > 0 )
			{
				segment_descriptor->compressed_data_offset -= 1;
				segment_descriptor->compressed_data_size   += 1;
			}
			if( libfdata_list_append_element_with_mapped_size(
			     internal_file->compressed_segments_list,
			     &element_index,
			     segment_descriptor_index,
			     segment_descriptor->compressed_data_offset,
			     segment_descriptor->compressed_data_size,
			     0,
			     segment_descriptor->uncompressed_data_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append element to compressed segments list.",
				 function );

				goto on_error;
			}
			if( libcdata_array_append_entry(
			     internal_file->segment_descriptors_array,
			     &entry_index,
			     (intptr_t *) segment_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append segment descriptor.",
				 function );

				goto on_error;
			}
			uncompressed_data_offset += segment_descriptor->uncompressed_data_size;

			segment_descriptor = NULL;

			segment_descriptor_index++;
		}
		if( ( is_last_block != 0 )
		 || ( decompression_error != 0 ) )
		{
			break;
		}
	}
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( inflateEnd(
	     &zlib_stream ) != Z_OK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to finalize zlib stream.",
		 function );

		goto on_error;
	}
#else
	if( fixed_huffman_distances_tree != NULL )
	{
		if( libgzipf_huffman_tree_free(
		     &fixed_huffman_distances_tree,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free fixed distances Huffman tree.",
			 function );

			goto on_error;
		}
	}
	if( fixed_huffman_literals_tree != NULL )
	{
		if( libgzipf_huffman_tree_free(
		     &fixed_huffman_literals_tree,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free fixed literals Huffman tree.",
			 function );

			goto on_error;
		}
	}
	if( libgzipf_bit_stream_free(
	     &bit_stream,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free bit stream.",
		 function );

		goto on_error;
	}
#endif /* ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL ) */

	memory_free(
	 uncompressed_data );

	uncompressed_data = NULL;

	memory_free(
	 compressed_data );

	compressed_data = NULL;

	if( segment_descriptor != NULL )
	{
		if( libfdata_list_append_element_with_mapped_size(
		     internal_file->compressed_segments_list,
		     &element_index,
		     0,
		     segment_descriptor->compressed_data_offset,
		     segment_descriptor->compressed_data_size,
		     0,
		     segment_descriptor->uncompressed_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append element to compressed segments list.",
			 function );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     internal_file->segment_descriptors_array,
		     &entry_index,
		     (intptr_t *) segment_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append segment descriptor.",
			 function );

			goto on_error;
		}
		segment_descriptor = NULL;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compressed stream size\t: %" PRIu64 "\n",
		 function,
		 safe_compressed_stream_size );

		libcnotify_printf(
		 "%s: uncompressed stream size\t: %" PRIu32 "\n",
		 function,
		 safe_uncompressed_data_size );

		libcnotify_printf(
		 "%s: calculated checksum\t: 0x%08" PRIx32 "\n",
		 function,
		 safe_calculated_checksum );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	*compressed_stream_size   = safe_compressed_stream_size;
	*uncompressed_stream_size = safe_uncompressed_data_size;
	*calculated_checksum      = safe_calculated_checksum;

	if( decompression_error != 0 )
	{
		return( -1 );
	}
	return( 1 );

on_error:
	if( segment_descriptor != NULL )
	{
		libgzipf_segment_descriptor_free(
		 &segment_descriptor,
		 NULL );
	}
#if ( defined( HAVE_ZLIB ) && defined( HAVE_ZLIB_INFLATE ) ) || defined( ZLIB_DLL )
	inflateEnd(
	 &zlib_stream );
#else
	if( bit_stream != NULL )
	{
		libgzipf_bit_stream_free(
		 &bit_stream,
		 NULL );
	}
#endif
	if( uncompressed_data != NULL )
	{
		memory_free(
		 uncompressed_data );
	}
	if( compressed_data != NULL )
	{
		memory_free(
		 compressed_data );
	}
	return( -1 );
}

/* Reads uncompressed data from the current offset into a buffer using a Basic File IO (bfio) handle
 * This function is not multi-thread safe acquire write lock before call
 * Returns the number of bytes read or -1 on error
 */
ssize_t libgzipf_internal_file_read_buffer_from_file_io_handle(
         libgzipf_internal_file_t *internal_file,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libgzipf_compressed_segment_t *compressed_segment = NULL;
	static char *function                             = "libgzipf_internal_file_read_buffer_from_file_io_handle";
	size_t buffer_offset                              = 0;
	size_t read_size                                  = 0;
	off64_t element_data_offset                       = 0;
	int element_index                                 = 0;

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( internal_file->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid file - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( (size64_t) internal_file->current_offset >= internal_file->uncompressed_data_size )
	{
		return( 0 );
	}
	while( buffer_offset < buffer_size )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: current offset\t: 0x%08" PRIx64 "\n",
			 function,
			 internal_file->current_offset );
		}
#endif
		if( libfdata_list_get_element_value_at_offset(
		     internal_file->compressed_segments_list,
		     (intptr_t *) file_io_handle,
		     (libfdata_cache_t *) internal_file->compressed_segments_cache,
		     internal_file->current_offset,
		     &element_index,
		     &element_data_offset,
		     (intptr_t **) &compressed_segment,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve compressed segment for offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 internal_file->current_offset,
			 internal_file->current_offset );

			return( -1 );
		}
		if( compressed_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing compressed segment.",
			 function );

			return( -1 );
		}
		if( (size64_t) element_data_offset > compressed_segment->uncompressed_data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid element data offset value out of bounds.",
			 function );

			return( -1 );
		}
		read_size = compressed_segment->uncompressed_data_size - element_data_offset;

		if( read_size > ( buffer_size - buffer_offset ) )
		{
			read_size = buffer_size - buffer_offset;
		}
		if( memory_copy(
		     &( ( (uint8_t *) buffer )[ buffer_offset ] ),
		     &( compressed_segment->uncompressed_data[ element_data_offset ] ),
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy compressed segment data to buffer.",
			 function );

			return( -1 );
		}
		internal_file->current_offset += read_size;
		buffer_offset                 += read_size;

		if( (size64_t) internal_file->current_offset >= internal_file->uncompressed_data_size )
		{
			break;
		}
	}
	return( (ssize_t) buffer_offset );
}

/* Reads uncompressed data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libgzipf_file_read_buffer(
         libgzipf_file_t *file,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_read_buffer";
	ssize_t read_count                      = 0;

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
		      internal_file,
		      internal_file->file_io_handle,
		      buffer,
		      buffer_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		read_count = -1;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Reads uncompressed data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libgzipf_file_read_buffer_at_offset(
         libgzipf_file_t *file,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_read_buffer_at_offset";
	ssize_t read_count                      = 0;

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libgzipf_internal_file_seek_offset(
	     internal_file,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		read_count = -1;
	}
	else
	{
		read_count = libgzipf_internal_file_read_buffer_from_file_io_handle(
			      internal_file,
			      internal_file->file_io_handle,
			      buffer,
			      buffer_size,
			      error );

		if( read_count == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read buffer.",
			 function );

			read_count = -1;
		}
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Seeks a certain offset of the uncompressed data
 * This function is not multi-thread safe acquire write lock before call
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libgzipf_internal_file_seek_offset(
         libgzipf_internal_file_t *internal_file,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	static char *function = "libgzipf_internal_file_seek_offset";

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_file->current_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) internal_file->uncompressed_data_size;
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	internal_file->current_offset = offset;

	return( offset );
}

/* Seeks a certain offset of the uncompressed data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libgzipf_file_seek_offset(
         libgzipf_file_t *file,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_seek_offset";

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	offset = libgzipf_internal_file_seek_offset(
	          internal_file,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		offset = -1;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( offset );
}

/* Retrieves the current offset of the uncompressed data
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_get_offset(
     libgzipf_file_t *file,
     off64_t *offset,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_get_offset";

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*offset = internal_file->current_offset;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Determine if the file corrupted
 * Returns 1 if corrupted, 0 if not or -1 on error
 */
int libgzipf_file_is_corrupted(
     libgzipf_file_t *file,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                  = "libgzipf_file_is_corrupted";
	int result                             = 0;

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
	internal_file = (libgzipf_internal_file_t *) file;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( ( internal_file->flags & LIBGZIPF_FILE_FLAG_IS_CORRUPTED ) != 0 )
	{
		result = 1;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the uncompressed data size
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_get_uncompressed_data_size(
     libgzipf_file_t *file,
     size64_t *uncompressed_data_size,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_get_uncompressed_data_size";

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
	internal_file = (libgzipf_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( uncompressed_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid uncompressed data size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*uncompressed_data_size = internal_file->uncompressed_data_size;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the number of members
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_get_number_of_members(
     libgzipf_file_t *file,
     int *number_of_members,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file = NULL;
	static char *function                   = "libgzipf_file_get_number_of_members";
	int result                              = 1;

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
	internal_file = (libgzipf_internal_file_t *) file;

#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libcdata_array_get_number_of_entries(
	     internal_file->member_descriptors_array,
	     number_of_members,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from member descriptors array.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves a specific member
 * Returns 1 if successful or -1 on error
 */
int libgzipf_file_get_member_by_index(
     libgzipf_file_t *file,
     int member_index,
     libgzipf_member_t **member,
     libcerror_error_t **error )
{
	libgzipf_internal_file_t *internal_file         = NULL;
	libgzipf_member_descriptor_t *member_descriptor = NULL;
	static char *function                           = "libgzipf_file_get_member_by_index";
	int result                                      = 1;

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
	internal_file = (libgzipf_internal_file_t *) file;

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
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libcdata_array_get_entry_by_index(
	     internal_file->member_descriptors_array,
	     member_index,
	     (intptr_t **) &member_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve member descriptor: %d.",
		 function,
		 member_index );

		result = -1;
	}
	else if( libgzipf_member_initialize(
	          member,
	          internal_file->io_handle,
	          internal_file->file_io_handle,
	          member_descriptor,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create member.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBGZIPF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

