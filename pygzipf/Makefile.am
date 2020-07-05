if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBGZIPF_DLL_IMPORT@

pyexec_LTLIBRARIES = pygzipf.la

pygzipf_la_SOURCES = \
	pygzipf.c pygzipf.h \
	pygzipf_codepage.c pygzipf_codepage.h \
	pygzipf_datetime.c pygzipf_datetime.h \
	pygzipf_error.c pygzipf_error.h \
	pygzipf_file.c pygzipf_file.h \
	pygzipf_file_object_io_handle.c pygzipf_file_object_io_handle.h \
	pygzipf_integer.c pygzipf_integer.h \
	pygzipf_libbfio.h \
	pygzipf_libcerror.h \
	pygzipf_libclocale.h \
	pygzipf_libgzipf.h \
	pygzipf_member.c pygzipf_member.h \
	pygzipf_members.c pygzipf_members.h \
	pygzipf_python.h \
	pygzipf_unused.h

pygzipf_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libgzipf/libgzipf.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pygzipf_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pygzipf_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

