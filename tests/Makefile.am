AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBGZIPF_DLL_IMPORT@

check_PYTHONdir = $(abs_top_builddir)

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_PYTHON_SCRIPTS = \
	pygzipf_test_file.py \
	pygzipf_test_member.py \
	pygzipf_test_support.py

check_PROGRAMS = \
	gzipf_test_bit_stream \
	gzipf_test_checksum \
	gzipf_test_compressed_segment \
	gzipf_test_deflate \
	gzipf_test_error \
	gzipf_test_file \
	gzipf_test_huffman_tree \
	gzipf_test_io_handle \
	gzipf_test_member \
	gzipf_test_member_descriptor \
	gzipf_test_member_footer \
	gzipf_test_member_header \
	gzipf_test_notify \
	gzipf_test_support \
	gzipf_test_tools_info_handle \
	gzipf_test_tools_output \
	gzipf_test_tools_signal

gzipf_test_bit_stream_SOURCES = \
	gzipf_test_bit_stream.c \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_bit_stream_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_checksum_SOURCES = \
	gzipf_test_checksum.c \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_checksum_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_compressed_segment_SOURCES = \
	gzipf_test_compressed_segment.c \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_compressed_segment_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_deflate_SOURCES = \
	gzipf_test_deflate.c \
	gzipf_test_libcerror.h \
	gzipf_test_libcnotify.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_unused.h

gzipf_test_deflate_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

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

gzipf_test_huffman_tree_SOURCES = \
	gzipf_test_huffman_tree.c \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_huffman_tree_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

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

gzipf_test_member_SOURCES = \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_member.c \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_member_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_member_descriptor_SOURCES = \
	gzipf_test_libcerror.h \
	gzipf_test_libgzipf.h \
	gzipf_test_macros.h \
	gzipf_test_member_descriptor.c \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_unused.h

gzipf_test_member_descriptor_LDADD = \
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

gzipf_test_tools_info_handle_SOURCES = \
	../gzipftools/info_handle.c ../gzipftools/info_handle.h \
	gzipf_test_libcerror.h \
	gzipf_test_macros.h \
	gzipf_test_memory.c gzipf_test_memory.h \
	gzipf_test_tools_info_handle.c \
	gzipf_test_unused.h

gzipf_test_tools_info_handle_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

gzipf_test_tools_output_SOURCES = \
	../gzipftools/gzipftools_output.c ../gzipftools/gzipftools_output.h \
	gzipf_test_libcerror.h \
	gzipf_test_macros.h \
	gzipf_test_tools_output.c \
	gzipf_test_unused.h

gzipf_test_tools_output_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

gzipf_test_tools_signal_SOURCES = \
	../gzipftools/gzipftools_signal.c ../gzipftools/gzipftools_signal.h \
	gzipf_test_libcerror.h \
	gzipf_test_macros.h \
	gzipf_test_tools_signal.c \
	gzipf_test_unused.h

gzipf_test_tools_signal_LDADD = \
	../libgzipf/libgzipf.la \
	@LIBCERROR_LIBADD@

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libgzipf.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libgzipf

test_inputs_pygzipf.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pygzipf

test_inputs_gzipfinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) gzipfinfo

test_library: \
	package.m4 \
	test_inputs_libgzipf.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pygzipf.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_gzipfinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_PYTHON_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

