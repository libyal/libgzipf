/*
 * Python object wrapper of libgzipf_file_t
 *
 * Copyright (C) 2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _PYGZIPF_FILE_H )
#define _PYGZIPF_FILE_H

#include <common.h>
#include <types.h>

#include "pygzipf_libbfio.h"
#include "pygzipf_libgzipf.h"
#include "pygzipf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pygzipf_file pygzipf_file_t;

struct pygzipf_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libgzipf file
	 */
	libgzipf_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pygzipf_file_object_methods[];
extern PyTypeObject pygzipf_file_type_object;

int pygzipf_file_init(
     pygzipf_file_t *pygzipf_file );

void pygzipf_file_free(
      pygzipf_file_t *pygzipf_file );

PyObject *pygzipf_file_signal_abort(
           pygzipf_file_t *pygzipf_file,
           PyObject *arguments );

PyObject *pygzipf_file_open(
           pygzipf_file_t *pygzipf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pygzipf_file_open_file_object(
           pygzipf_file_t *pygzipf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pygzipf_file_close(
           pygzipf_file_t *pygzipf_file,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYGZIPF_FILE_H ) */
