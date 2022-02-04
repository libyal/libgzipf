/*
 * Library to access the GZIP file format
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

#if !defined( _LIBGZIPF_H )
#define _LIBGZIPF_H

#include <libgzipf/codepage.h>
#include <libgzipf/definitions.h>
#include <libgzipf/error.h>
#include <libgzipf/extern.h>
#include <libgzipf/features.h>
#include <libgzipf/types.h>

#include <stdio.h>

#if defined( LIBGZIPF_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBGZIPF_EXTERN \
const char *libgzipf_get_version(
             void );

/* Returns the access flags for reading
 */
LIBGZIPF_EXTERN \
int libgzipf_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_get_codepage(
     int *codepage,
     libgzipf_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_set_codepage(
     int codepage,
     libgzipf_error_t **error );

/* Determines if a file contains a GZIP file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_check_file_signature(
     const char *filename,
     libgzipf_error_t **error );

#if defined( LIBGZIPF_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a GZIP file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_check_file_signature_wide(
     const wchar_t *filename,
     libgzipf_error_t **error );

#endif /* defined( LIBGZIPF_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBGZIPF_HAVE_BFIO )

/* Determines if a file contains a GZIP file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libgzipf_error_t **error );

#endif /* defined( LIBGZIPF_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBGZIPF_EXTERN \
void libgzipf_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_notify_set_stream(
     FILE *stream,
     libgzipf_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_notify_stream_open(
     const char *filename,
     libgzipf_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_notify_stream_close(
     libgzipf_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBGZIPF_EXTERN \
void libgzipf_error_free(
      libgzipf_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_error_fprint(
     libgzipf_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_error_sprint(
     libgzipf_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_error_backtrace_fprint(
     libgzipf_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_error_backtrace_sprint(
     libgzipf_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * File functions
 * ------------------------------------------------------------------------- */

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_initialize(
     libgzipf_file_t **file,
     libgzipf_error_t **error );

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_free(
     libgzipf_file_t **file,
     libgzipf_error_t **error );

/* Signals the file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_signal_abort(
     libgzipf_file_t *file,
     libgzipf_error_t **error );

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_open(
     libgzipf_file_t *file,
     const char *filename,
     int access_flags,
     libgzipf_error_t **error );

#if defined( LIBGZIPF_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_open_wide(
     libgzipf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libgzipf_error_t **error );

#endif /* defined( LIBGZIPF_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBGZIPF_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_open_file_io_handle(
     libgzipf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libgzipf_error_t **error );

#endif /* defined( LIBGZIPF_HAVE_BFIO ) */

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_close(
     libgzipf_file_t *file,
     libgzipf_error_t **error );

/* Reads uncompressed data at the current offset
 * Returns the number of bytes read or -1 on error
 */
LIBGZIPF_EXTERN \
ssize_t libgzipf_file_read_buffer(
         libgzipf_file_t *file,
         void *buffer,
         size_t buffer_size,
         libgzipf_error_t **error );

/* Reads uncompressed data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBGZIPF_EXTERN \
ssize_t libgzipf_file_read_buffer_at_offset(
         libgzipf_file_t *file,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libgzipf_error_t **error );

/* Seeks a certain offset of the uncompressed data
 * Returns the offset if seek is successful or -1 on error
 */
LIBGZIPF_EXTERN \
off64_t libgzipf_file_seek_offset(
         libgzipf_file_t *file,
         off64_t offset,
         int whence,
         libgzipf_error_t **error );

/* Retrieves the current offset of the uncompressed data
 * Returns the offset if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_get_offset(
     libgzipf_file_t *file,
     off64_t *offset,
     libgzipf_error_t **error );

/* Determine if the file is corrupted
 * Returns 1 if corrupted, 0 if not or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_is_corrupted(
     libgzipf_file_t *file,
     libgzipf_error_t **error );

/* Retrieves the uncompressed data size
 * Returns the 1 if succesful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_get_uncompressed_data_size(
     libgzipf_file_t *file,
     size64_t *uncompressed_data_size,
     libgzipf_error_t **error );

/* Retrieves the number of members
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_get_number_of_members(
     libgzipf_file_t *file,
     int *number_of_members,
     libgzipf_error_t **error );

/* Retrieves a specific member
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_file_get_member_by_index(
     libgzipf_file_t *file,
     int member_index,
     libgzipf_member_t **member,
     libgzipf_error_t **error );

/* -------------------------------------------------------------------------
 * Member functions
 * ------------------------------------------------------------------------- */

/* Frees a member
 */
LIBGZIPF_EXTERN \
int libgzipf_member_free(
     libgzipf_member_t **member,
     libgzipf_error_t **error );

/* Retrieves the modification time
 * The timestamp is a signed 32-bit POSIX date and time value in number of seconds
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_modification_time(
     libgzipf_member_t *member,
     uint32_t *posix_time,
     libgzipf_error_t **error );

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_utf8_name_size(
     libgzipf_member_t *member,
     size_t *utf8_string_size,
     libgzipf_error_t **error );

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_utf8_name(
     libgzipf_member_t *member,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libgzipf_error_t **error );

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_utf16_name_size(
     libgzipf_member_t *member,
     size_t *utf16_string_size,
     libgzipf_error_t **error );

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_utf16_name(
     libgzipf_member_t *member,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libgzipf_error_t **error );

/* Retrieves the size of the UTF-8 encoded comments
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_utf8_comments_size(
     libgzipf_member_t *member,
     size_t *utf8_string_size,
     libgzipf_error_t **error );

/* Retrieves the UTF-8 encoded comments
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_utf8_comments(
     libgzipf_member_t *member,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libgzipf_error_t **error );

/* Retrieves the size of the UTF-16 encoded comments
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_utf16_comments_size(
     libgzipf_member_t *member,
     size_t *utf16_string_size,
     libgzipf_error_t **error );

/* Retrieves the UTF-16 encoded comments
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_utf16_comments(
     libgzipf_member_t *member,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libgzipf_error_t **error );

/* Retrieves the operating system
 * Returns 1 if successful or -1 on error
 */
LIBGZIPF_EXTERN \
int libgzipf_member_get_operating_system(
     libgzipf_member_t *member,
     uint8_t *operating_system,
     libgzipf_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_H ) */

