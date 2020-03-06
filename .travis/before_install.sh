#!/bin/sh
# Script to run before_install step on Travis-CI
#
# Version: 20191209

# Exit on error.
set -e;

if test ${TARGET} = "docker";
then
	sudo apt-get update;
	sudo apt-mark hold mysql-server-5.7 postgresql-9.4 postgresql-client-9.4 postgresql-9.5 postgresql-client-9.5 postgresql-9.6 postgresql-client-9.6 postgresql-10 postgresql-client-10;
	sudo apt-get --fix-missing -o Dpkg::Options::="--force-confold" upgrade -y --allow-unauthenticated;

	sudo apt-get install -y qemu-user-static;

	docker run --rm --privileged multiarch/qemu-user-static --reset -p yes;

elif test ${TRAVIS_OS_NAME} = "linux";
then
	sudo apt-get update;
	sudo apt-mark hold mysql-server-5.7 postgresql-9.4 postgresql-client-9.4 postgresql-9.5 postgresql-client-9.5 postgresql-9.6 postgresql-client-9.6 postgresql-10 postgresql-client-10;
	sudo apt-get --fix-missing -o Dpkg::Options::="--force-confold" upgrade -y --allow-unauthenticated;

	sudo apt-get install -y autoconf automake autopoint build-essential git libtool pkg-config zlib1g-dev;

elif test ${TRAVIS_OS_NAME} = "osx";
then
	brew update

	brew install gettext gnu-sed;
	brew link --force gettext;

	if test ${TARGET} = "macos-gcc-python-setup-py37";
	then
		python3 -m pip install -U pip twine;
	fi
fi

