/*
 * Python object wrapper of libgzipf_member_t
 *
 * Copyright (C) 2019-2020, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pygzipf_error.h"
#include "pygzipf_libcerror.h"
#include "pygzipf_libgzipf.h"
#include "pygzipf_member.h"
#include "pygzipf_python.h"
#include "pygzipf_unused.h"

PyMethodDef pygzipf_member_object_methods[] = {

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pygzipf_member_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pygzipf_member_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pygzipf.member",
	/* tp_basicsize */
	sizeof( pygzipf_member_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pygzipf_member_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pygzipf member object (wraps libgzipf_member_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pygzipf_member_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pygzipf_member_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pygzipf_member_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new member object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pygzipf_member_new(
           libgzipf_member_t *member,
           PyObject *parent_object )
{
	pygzipf_member_t *pygzipf_member = NULL;
	static char *function            = "pygzipf_member_new";

	if( member == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid member.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pygzipf_member = PyObject_New(
	                  struct pygzipf_member,
	                  &pygzipf_member_type_object );

	if( pygzipf_member == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize member.",
		 function );

		goto on_error;
	}
	pygzipf_member->member        = member;
	pygzipf_member->parent_object = parent_object;

	if( pygzipf_member->parent_object != NULL )
	{
		Py_IncRef(
		 pygzipf_member->parent_object );
	}
	return( (PyObject *) pygzipf_member );

on_error:
	if( pygzipf_member != NULL )
	{
		Py_DecRef(
		 (PyObject *) pygzipf_member );
	}
	return( NULL );
}

/* Intializes a member object
 * Returns 0 if successful or -1 on error
 */
int pygzipf_member_init(
     pygzipf_member_t *pygzipf_member )
{
	static char *function = "pygzipf_member_init";

	if( pygzipf_member == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid member.",
		 function );

		return( -1 );
	}
	/* Make sure libgzipf member is set to NULL
	 */
	pygzipf_member->member = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of member not supported.",
	 function );

	return( -1 );
}

/* Frees a member object
 */
void pygzipf_member_free(
      pygzipf_member_t *pygzipf_member )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pygzipf_member_free";
	int result                  = 0;

	if( pygzipf_member == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid member.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pygzipf_member );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pygzipf_member->member != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libgzipf_member_free(
		          &( pygzipf_member->member ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pygzipf_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libgzipf member.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pygzipf_member->parent_object != NULL )
	{
		Py_DecRef(
		 pygzipf_member->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pygzipf_member );
}

