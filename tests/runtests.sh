#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libgzipf/.libs/libgzipf.1.dylib && test -f ./pygzipf/.libs/pygzipf.so
then
	install_name_tool -change /usr/local/lib/libgzipf.1.dylib ${PWD}/libgzipf/.libs/libgzipf.1.dylib ./pygzipf/.libs/pygzipf.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

