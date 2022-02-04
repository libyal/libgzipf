/*
 * Python object definition of the sequence and iterator object of members
 *
 * Copyright (C) 2019-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _PYGZIPF_MEMBERS_H )
#define _PYGZIPF_MEMBERS_H

#include <common.h>
#include <types.h>

#include "pygzipf_libgzipf.h"
#include "pygzipf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pygzipf_members pygzipf_members_t;

struct pygzipf_members
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pygzipf_members_type_object;

PyObject *pygzipf_members_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pygzipf_members_init(
     pygzipf_members_t *sequence_object );

void pygzipf_members_free(
      pygzipf_members_t *sequence_object );

Py_ssize_t pygzipf_members_len(
            pygzipf_members_t *sequence_object );

PyObject *pygzipf_members_getitem(
           pygzipf_members_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pygzipf_members_iter(
           pygzipf_members_t *sequence_object );

PyObject *pygzipf_members_iternext(
           pygzipf_members_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYGZIPF_MEMBERS_H ) */

