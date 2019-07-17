AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBGZIPF_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	gzipfinfo

gzipfinfo_SOURCES = \
	gzipfinfo.c \
	gzipftools_getopt.c gzipftools_getopt.h \
	gzipftools_i18n.h \
	gzipftools_libbfio.h \
	gzipftools_libcerror.h \
	gzipftools_libclocale.h \
	gzipftools_libcnotify.h \
	gzipftools_libfdatetime.h \
	gzipftools_libuna.h \
	gzipftools_output.c gzipftools_output.h \
	gzipftools_signal.c gzipftools_signal.h \
	gzipftools_unused.h \
	info_handle.c info_handle.h

gzipfinfo_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libgzipf/libgzipf.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on gzipfinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(gzipfinfo_SOURCES)
