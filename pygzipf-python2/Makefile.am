# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
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

am_pygzipf_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
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

pyexec_LTLIBRARIES = pygzipf.la

nodist_pygzipf_la_SOURCES = $(BUILT_SOURCES)

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

pygzipf_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pygzipf_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pygzipf/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pygzipf*.[ch]

distclean: clean
	/bin/rm -f Makefile

