include_HEADERS = \
	libgzipf.h

pkginclude_HEADERS = \
	libgzipf/codepage.h \
	libgzipf/definitions.h \
	libgzipf/error.h \
	libgzipf/extern.h \
	libgzipf/features.h \
	libgzipf/types.h

EXTRA_DIST = \
	libgzipf.h.in \
	libgzipf/definitions.h.in \
	libgzipf/features.h.in \
	libgzipf/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libgzipf.h
	-rm -f libgzipf/definitions.h
	-rm -f libgzipf/features.h
	-rm -f libgzipf/types.h
	-rm -f Makefile

