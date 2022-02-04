/*
 * Mounts GZIP files.
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
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "gzipftools_getopt.h"
#include "gzipftools_i18n.h"
#include "gzipftools_libgzipf.h"
#include "gzipftools_libcerror.h"
#include "gzipftools_libclocale.h"
#include "gzipftools_libcnotify.h"
#include "gzipftools_output.h"
#include "gzipftools_signal.h"
#include "gzipftools_unused.h"
#include "mount_dokan.h"
#include "mount_fuse.h"
#include "mount_handle.h"

mount_handle_t *gzipfmount_mount_handle = NULL;
int gzipfmount_abort                    = 0;

/* Prints usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use gzipfmount to mount a GZIP file\n\n" );

	fprintf( stream, "Usage: gzipfmount [ -X extended_options ] [ -hvV ]\n"
	                 "                  descriptor_file mount_point\n\n" );

	fprintf( stream, "\tdescriptor_file:  GZIP file\n\n" );
	fprintf( stream, "\tmount_point:      the directory to serve as mount point\n\n" );

	fprintf( stream, "\t-h:               shows this help\n" );
	fprintf( stream, "\t-v:               verbose output to stderr, while gzipfmount will remain running\n"
	                 "\t                  in the foreground\n" );
	fprintf( stream, "\t-V:               print version\n" );
	fprintf( stream, "\t-X:               extended options to pass to sub system\n" );
}

/* Signal handler for gzipfmount
 */
void gzipfmount_signal_handler(
      gzipftools_signal_t signal GZIPFTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "gzipfmount_signal_handler";

	GZIPFTOOLS_UNREFERENCED_PARAMETER( signal )

	gzipfmount_abort = 1;

	if( gzipfmount_mount_handle != NULL )
	{
		if( mount_handle_signal_abort(
		     gzipfmount_mount_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal mount handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libgzipf_error_t *error                     = NULL;
	system_character_t *mount_point             = NULL;
	system_character_t *option_extended_options = NULL;
	const system_character_t *path_prefix       = NULL;
	system_character_t *source                  = NULL;
	char *program                               = "gzipfmount";
	system_integer_t option                     = 0;
	size_t path_prefix_size                     = 0;
	int result                                  = 0;
	int verbose                                 = 0;

#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	struct fuse_operations gzipfmount_fuse_operations;

	struct fuse_args gzipfmount_fuse_arguments  = FUSE_ARGS_INIT(0, NULL);
	struct fuse_chan *gzipfmount_fuse_channel   = NULL;
	struct fuse *gzipfmount_fuse_handle         = NULL;

#elif defined( HAVE_LIBDOKAN )
	DOKAN_OPERATIONS gzipfmount_dokan_operations;
	DOKAN_OPTIONS gzipfmount_dokan_options;
#endif

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
	     "gzipftools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( gzipftools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	gzipftools_output_version_fprint(
	 stdout,
	 program );

	while( ( option = gzipftools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "hvVX:" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				gzipftools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'X':
				option_extended_options = optarg;

				break;
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source descriptor file.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind++ ];

	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing mount point.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	mount_point = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libgzipf_notify_set_stream(
	 stderr,
	 NULL );
	libgzipf_notify_set_verbose(
	 verbose );

	if( mount_handle_initialize(
	     &gzipfmount_mount_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize mount handle.\n" );

		goto on_error;
	}
#if defined( WINAPI )
	path_prefix = _SYSTEM_STRING( "\\GZIPF" );
#else
	path_prefix = _SYSTEM_STRING( "/gzipf" );
#endif
	path_prefix_size = 1 + system_string_length(
	                        path_prefix );

	if( mount_handle_set_path_prefix(
	     gzipfmount_mount_handle,
	     path_prefix,
	     path_prefix_size,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to set path prefix.\n" );

		goto on_error;
	}
	if( mount_handle_open(
	     gzipfmount_mount_handle,
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open source descriptor file\n" );

		goto on_error;
	}
#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	if( option_extended_options != NULL )
	{
		/* This argument is required but ignored
		 */
		if( fuse_opt_add_arg(
		     &gzipfmount_fuse_arguments,
		     "" ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
		if( fuse_opt_add_arg(
		     &gzipfmount_fuse_arguments,
		     "-o" ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
		if( fuse_opt_add_arg(
		     &gzipfmount_fuse_arguments,
		     option_extended_options ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
	}
	if( memory_set(
	     &gzipfmount_fuse_operations,
	     0,
	     sizeof( struct fuse_operations ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear fuse operations.\n" );

		goto on_error;
	}
	gzipfmount_fuse_operations.open       = &mount_fuse_open;
	gzipfmount_fuse_operations.read       = &mount_fuse_read;
	gzipfmount_fuse_operations.release    = &mount_fuse_release;
	gzipfmount_fuse_operations.opendir    = &mount_fuse_opendir;
	gzipfmount_fuse_operations.readdir    = &mount_fuse_readdir;
	gzipfmount_fuse_operations.releasedir = &mount_fuse_releasedir;
	gzipfmount_fuse_operations.getattr    = &mount_fuse_getattr;
	gzipfmount_fuse_operations.destroy    = &mount_fuse_destroy;

	gzipfmount_fuse_channel = fuse_mount(
	                           mount_point,
	                           &gzipfmount_fuse_arguments );

	if( gzipfmount_fuse_channel == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to create fuse channel.\n" );

		goto on_error;
	}
	gzipfmount_fuse_handle = fuse_new(
	                          gzipfmount_fuse_channel,
	                          &gzipfmount_fuse_arguments,
	                          &gzipfmount_fuse_operations,
	                          sizeof( struct fuse_operations ),
	                          gzipfmount_mount_handle );

	if( gzipfmount_fuse_handle == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to create fuse handle.\n" );

		goto on_error;
	}
	if( verbose == 0 )
	{
		if( fuse_daemonize(
		     0 ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable to daemonize fuse.\n" );

			goto on_error;
		}
	}
	result = fuse_loop(
	          gzipfmount_fuse_handle );

	if( result != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to run fuse loop.\n" );

		goto on_error;
	}
	fuse_destroy(
	 gzipfmount_fuse_handle );

	fuse_opt_free_args(
	 &gzipfmount_fuse_arguments );

	return( EXIT_SUCCESS );

#elif defined( HAVE_LIBDOKAN )
	if( memory_set(
	     &gzipfmount_dokan_operations,
	     0,
	     sizeof( DOKAN_OPERATIONS ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear dokan operations.\n" );

		goto on_error;
	}
	if( memory_set(
	     &gzipfmount_dokan_options,
	     0,
	     sizeof( DOKAN_OPTIONS ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear dokan options.\n" );

		goto on_error;
	}
	gzipfmount_dokan_options.Version     = DOKAN_VERSION;
	gzipfmount_dokan_options.ThreadCount = 0;
	gzipfmount_dokan_options.MountPoint  = mount_point;

	if( verbose != 0 )
	{
		gzipfmount_dokan_options.Options |= DOKAN_OPTION_STDERR;
#if defined( HAVE_DEBUG_OUTPUT )
		gzipfmount_dokan_options.Options |= DOKAN_OPTION_DEBUG;
#endif
	}
/* This will only affect the drive properties
	gzipfmount_dokan_options.Options |= DOKAN_OPTION_REMOVABLE;
*/

#if ( DOKAN_VERSION >= 600 ) && ( DOKAN_VERSION < 800 )
	gzipfmount_dokan_options.Options |= DOKAN_OPTION_KEEP_ALIVE;

	gzipfmount_dokan_operations.CreateFile           = &mount_dokan_CreateFile;
	gzipfmount_dokan_operations.OpenDirectory        = &mount_dokan_OpenDirectory;
	gzipfmount_dokan_operations.CreateDirectory      = NULL;
	gzipfmount_dokan_operations.Cleanup              = NULL;
	gzipfmount_dokan_operations.CloseFile            = &mount_dokan_CloseFile;
	gzipfmount_dokan_operations.ReadFile             = &mount_dokan_ReadFile;
	gzipfmount_dokan_operations.WriteFile            = NULL;
	gzipfmount_dokan_operations.FlushFileBuffers     = NULL;
	gzipfmount_dokan_operations.GetFileInformation   = &mount_dokan_GetFileInformation;
	gzipfmount_dokan_operations.FindFiles            = &mount_dokan_FindFiles;
	gzipfmount_dokan_operations.FindFilesWithPattern = NULL;
	gzipfmount_dokan_operations.SetFileAttributes    = NULL;
	gzipfmount_dokan_operations.SetFileTime          = NULL;
	gzipfmount_dokan_operations.DeleteFile           = NULL;
	gzipfmount_dokan_operations.DeleteDirectory      = NULL;
	gzipfmount_dokan_operations.MoveFile             = NULL;
	gzipfmount_dokan_operations.SetEndOfFile         = NULL;
	gzipfmount_dokan_operations.SetAllocationSize    = NULL;
	gzipfmount_dokan_operations.LockFile             = NULL;
	gzipfmount_dokan_operations.UnlockFile           = NULL;
	gzipfmount_dokan_operations.GetFileSecurity      = NULL;
	gzipfmount_dokan_operations.SetFileSecurity      = NULL;
	gzipfmount_dokan_operations.GetDiskFreeSpace     = NULL;
	gzipfmount_dokan_operations.GetVolumeInformation = &mount_dokan_GetVolumeInformation;
	gzipfmount_dokan_operations.Unmount              = &mount_dokan_Unmount;

#else
	gzipfmount_dokan_operations.ZwCreateFile         = &mount_dokan_ZwCreateFile;
	gzipfmount_dokan_operations.Cleanup              = NULL;
	gzipfmount_dokan_operations.CloseFile            = &mount_dokan_CloseFile;
	gzipfmount_dokan_operations.ReadFile             = &mount_dokan_ReadFile;
	gzipfmount_dokan_operations.WriteFile            = NULL;
	gzipfmount_dokan_operations.FlushFileBuffers     = NULL;
	gzipfmount_dokan_operations.GetFileInformation   = &mount_dokan_GetFileInformation;
	gzipfmount_dokan_operations.FindFiles            = &mount_dokan_FindFiles;
	gzipfmount_dokan_operations.FindFilesWithPattern = NULL;
	gzipfmount_dokan_operations.SetFileAttributes    = NULL;
	gzipfmount_dokan_operations.SetFileTime          = NULL;
	gzipfmount_dokan_operations.DeleteFile           = NULL;
	gzipfmount_dokan_operations.DeleteDirectory      = NULL;
	gzipfmount_dokan_operations.MoveFile             = NULL;
	gzipfmount_dokan_operations.SetEndOfFile         = NULL;
	gzipfmount_dokan_operations.SetAllocationSize    = NULL;
	gzipfmount_dokan_operations.LockFile             = NULL;
	gzipfmount_dokan_operations.UnlockFile           = NULL;
	gzipfmount_dokan_operations.GetFileSecurity      = NULL;
	gzipfmount_dokan_operations.SetFileSecurity      = NULL;
	gzipfmount_dokan_operations.GetDiskFreeSpace     = NULL;
	gzipfmount_dokan_operations.GetVolumeInformation = &mount_dokan_GetVolumeInformation;
	gzipfmount_dokan_operations.Unmounted            = NULL;
	gzipfmount_dokan_operations.FindStreams          = NULL;
	gzipfmount_dokan_operations.Mounted              = NULL;

#endif /* ( DOKAN_VERSION >= 600 ) && ( DOKAN_VERSION < 800 ) */

	result = DokanMain(
	          &gzipfmount_dokan_options,
	          &gzipfmount_dokan_operations );

	switch( result )
	{
		case DOKAN_SUCCESS:
			break;

		case DOKAN_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: generic error\n" );
			break;

		case DOKAN_DRIVE_LETTER_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: bad drive letter\n" );
			break;

		case DOKAN_DRIVER_INSTALL_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unable to load driver\n" );
			break;

		case DOKAN_START_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: driver error\n" );
			break;

		case DOKAN_MOUNT_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unable to assign drive letter\n" );
			break;

		case DOKAN_MOUNT_POINT_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: mount point error\n" );
			break;

		default:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unknown error: %d\n",
			 result );
			break;
	}
	return( EXIT_SUCCESS );

#else
	fprintf(
	 stderr,
	 "No sub system to mount GZIPF format.\n" );

	return( EXIT_FAILURE );

#endif /* defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE ) */

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	if( gzipfmount_fuse_handle != NULL )
	{
		fuse_destroy(
		 gzipfmount_fuse_handle );
	}
	fuse_opt_free_args(
	 &gzipfmount_fuse_arguments );
#endif
	if( gzipfmount_mount_handle != NULL )
	{
		mount_handle_free(
		 &gzipfmount_mount_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

