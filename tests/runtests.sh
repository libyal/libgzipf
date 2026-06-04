#!/bin/sh
# Script to run tests
#
# Version: 20260602

if test -f ${PWD}/libgzipf/.libs/libgzipf.1.dylib && test -f ./pygzipf/.libs/pygzipf.so
then
	install_name_tool -change /usr/local/lib/libgzipf.1.dylib ${PWD}/libgzipf/.libs/libgzipf.1.dylib ./pygzipf/.libs/pygzipf.so
fi

make check $@
RESULT=$?

if test ${RESULT} -ne 0 && test -f tests/test-suite.log
then
	cat tests/test-suite.log
fi
exit ${RESULT}

