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
	/bin/rm -f libgzipf.h
	/bin/rm -f libgzipf/definitions.h
	/bin/rm -f libgzipf/features.h
	/bin/rm -f libgzipf/types.h
	/bin/rm -f Makefile

