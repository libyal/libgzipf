/*
 * Python object wrapper of libgzipf_member_t
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pygzipf_datetime.h"
#include "pygzipf_error.h"
#include "pygzipf_libcerror.h"
#include "pygzipf_libgzipf.h"
#include "pygzipf_member.h"
#include "pygzipf_python.h"
#include "pygzipf_unused.h"

PyMethodDef pygzipf_member_object_methods[] = {

	{ "get_modification_time",
	  (PyCFunction) pygzipf_member_get_modification_time,
	  METH_NOARGS,
	  "get_modification_time() -> Datetime\n"
	  "\n"
	  "Retrieves the modification time." },

	{ "get_modification_time_as_integer",
	  (PyCFunction) pygzipf_member_get_modification_time_as_integer,
	  METH_NOARGS,
	  "get_modification_time_as_integer() -> Integer or None\n"
	  "\n"
	  "Retrieves the modification time as a 32-bit integer containing a POSIX timestamp value." },

	{ "get_name",
	  (PyCFunction) pygzipf_member_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name." },

	{ "get_comments",
	  (PyCFunction) pygzipf_member_get_comments,
	  METH_NOARGS,
	  "get_comments() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the comments." },

	{ "get_operating_system",
	  (PyCFunction) pygzipf_member_get_operating_system,
	  METH_NOARGS,
	  "get_operating_system() -> Integer or None\n"
	  "\n"
	  "Retrieves the operating system." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pygzipf_member_object_get_set_definitions[] = {

	{ "modification_time",
	  (getter) pygzipf_member_get_modification_time,
	  (setter) 0,
	  "The modification time.",
	  NULL },

	{ "name",
	  (getter) pygzipf_member_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	{ "comments",
	  (getter) pygzipf_member_get_comments,
	  (setter) 0,
	  "The comments.",
	  NULL },

	{ "operating_system",
	  (getter) pygzipf_member_get_operating_system,
	  (setter) 0,
	  "The operating system.",
	  NULL },

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

/* Initializes a member object
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

/* Retrieves the modification time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pygzipf_member_get_modification_time(
           pygzipf_member_t *pygzipf_member,
           PyObject *arguments PYGZIPF_ATTRIBUTE_UNUSED )
{
	PyObject *datetime_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pygzipf_member_get_modification_time";
	uint32_t posix_time       = 0;
	int result                = 0;

	PYGZIPF_UNREFERENCED_PARAMETER( arguments )

	if( pygzipf_member == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid member.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libgzipf_member_get_modification_time(
	          pygzipf_member->member,
	          &posix_time,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pygzipf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve modification time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	datetime_object = pygzipf_datetime_new_from_posix_time(
	                   posix_time );

	return( datetime_object );
}

/* Retrieves the modification time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pygzipf_member_get_modification_time_as_integer(
           pygzipf_member_t *pygzipf_member,
           PyObject *arguments PYGZIPF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pygzipf_member_get_modification_time_as_integer";
	uint32_t posix_time      = 0;
	int result               = 0;

	PYGZIPF_UNREFERENCED_PARAMETER( arguments )

	if( pygzipf_member == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid member.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libgzipf_member_get_modification_time(
	          pygzipf_member->member,
	          &posix_time,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pygzipf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve modification time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) posix_time );

	return( integer_object );
}

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pygzipf_member_get_name(
           pygzipf_member_t *pygzipf_member,
           PyObject *arguments PYGZIPF_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pygzipf_member_get_name";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYGZIPF_UNREFERENCED_PARAMETER( arguments )

	if( pygzipf_member == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid member.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libgzipf_member_get_utf8_name_size(
	          pygzipf_member->member,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pygzipf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of name as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libgzipf_member_get_utf8_name(
	          pygzipf_member->member,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pygzipf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve name as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

/* Retrieves the comments
 * Returns a Python object if successful or NULL on error
 */
PyObject *pygzipf_member_get_comments(
           pygzipf_member_t *pygzipf_member,
           PyObject *arguments PYGZIPF_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pygzipf_member_get_comments";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYGZIPF_UNREFERENCED_PARAMETER( arguments )

	if( pygzipf_member == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid member.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libgzipf_member_get_utf8_comments_size(
	          pygzipf_member->member,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pygzipf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of comments as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libgzipf_member_get_utf8_comments(
	          pygzipf_member->member,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pygzipf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve comments as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

/* Retrieves the operating system
 * Returns a Python object if successful or NULL on error
 */
PyObject *pygzipf_member_get_operating_system(
           pygzipf_member_t *pygzipf_member,
           PyObject *arguments PYGZIPF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pygzipf_member_get_operating_system";
	uint8_t operating_system = 0;
	int result               = 0;

	PYGZIPF_UNREFERENCED_PARAMETER( arguments )

	if( pygzipf_member == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid member.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libgzipf_member_get_operating_system(
	          pygzipf_member->member,
	          &operating_system,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pygzipf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve operating system.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) operating_system );

	return( integer_object );
}

