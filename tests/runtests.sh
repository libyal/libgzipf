#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libgzipf/.libs/libgzipf.1.dylib" ] && [ -f ./pygzipf/.libs/pygzipf.so ]
then
    install_name_tool -change /usr/local/lib/libgzipf.1.dylib "${PWD}/libgzipf/.libs/libgzipf.1.dylib" ./pygzipf/.libs/pygzipf.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

