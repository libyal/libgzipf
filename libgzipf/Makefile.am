AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBGZIPF_DLL_EXPORT@

lib_LTLIBRARIES = libgzipf.la

libgzipf_la_SOURCES = \
	gzipf_member_header.h \
	gzipf_member_footer.h \
	libgzipf.c \
	libgzipf_codepage.h \
	libgzipf_debug.c libgzipf_debug.h \
	libgzipf_definitions.h \
	libgzipf_error.c libgzipf_error.h \
	libgzipf_extern.h \
	libgzipf_file.c libgzipf_file.h \
	libgzipf_io_handle.c libgzipf_io_handle.h \
	libgzipf_libbfio.h \
	libgzipf_libcerror.h \
	libgzipf_libclocale.h \
	libgzipf_libcnotify.h \
	libgzipf_libcthreads.h \
	libgzipf_libfdatetime.h \
	libgzipf_libuna.h \
	libgzipf_member_header.c libgzipf_member_header.h \
	libgzipf_member_footer.c libgzipf_member_footer.h \
	libgzipf_notify.c libgzipf_notify.h \
	libgzipf_support.c libgzipf_support.h \
	libgzipf_types.h \
	libgzipf_unused.h

libgzipf_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@PTHREAD_LIBADD@

libgzipf_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libgzipf_definitions.h.in \
	libgzipf.rc \
	libgzipf.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libgzipf_definitions.h
	/bin/rm -f libgzipf.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libgzipf ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libgzipf_la_SOURCES)
