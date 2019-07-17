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
	@LIBGZIPF_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYGZIPF = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_gzipfinfo.sh \
	$(TESTS_PYGZIPF)

check_SCRIPTS = \
	pygzipf_test_file.py \
	pygzipf_test_support.py \
	test_gzipfinfo.sh \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	gzipf_test_error \
	gzipf_test_file \
	gzipf_test_io_handle \
	gzipf_test_member_footer \
	gzipf_test_member_header \
	gzipf_test_notify \
	gzipf_test_support

gzipf_test_error_SOURCES = \
	gzipf_test_error.c \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_unused.h

gzipf_test_error_LDADD = \
	../libgzipf/libgzipf.la

gzipf_test_file_SOURCES = \
	gzipf_test_file.c \
	gzipf_test_functions.c gzipf_test_functions.h \
	gzipf_test_getopt.c gzipf_test_getopt.h \
	gzipf_test_libbfio.h \
	gzipf_test_libcerror.h \
	gzipf_test_libclocale.h \
	gzipf_test_libcnotify.h \
	gzipf_test_libgzipf.h \
	gzipf_test_libuna.h \
	gzipf_test_macros.h \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libgzipf/libgzipf.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

gzipf_test_io_handle_SOURCES = \
	gzipf_test_io_handle.c \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_io_handle_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_member_footer_SOURCES = \
	gzipf_test_functions.c gzipf_test_functions.h \
	gzipf_test_libbfio.h \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_member_footer.c \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_member_footer_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_member_header_SOURCES = \
	gzipf_test_functions.c gzipf_test_functions.h \
	gzipf_test_libbfio.h \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_member_header.c \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_member_header_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_notify_SOURCES = \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_notify.c \
	gzipf_test_unused.h

gzipf_test_notify_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_support_SOURCES = \
	gzipf_test_functions.c gzipf_test_functions.h \
	gzipf_test_getopt.c gzipf_test_getopt.h \
	gzipf_test_libbfio.h \
	gzipf_test_libcerror.h \
	gzipf_test_libclocale.h \
	gzipf_test_libcnotify.h \
	gzipf_test_libgzipf.h \
	gzipf_test_libuna.h \
	gzipf_test_macros.h \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_support.c \
	gzipf_test_unused.h

gzipf_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile
