/*
 * Member header of a GZIP file
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

#if !defined( _GZIPF_MEMBER_HEADER_H )
#define _GZIPF_MEMBER_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct gzipf_member_header gzipf_member_header_t;

struct gzipf_member_header
{
	/* Signature
	 * Consists of 2 bytes
	 */
	uint8_t signature[ 2 ];

	/* Compression method
	 * Consists of 1 byte
	 */
	uint8_t compression_method;

	/* Flags
	 * Consists of 1 byte
	 */
	uint8_t flags;

	/* Modification time
	 * Consists of 4 bytes
	 */
	uint8_t modification_time[ 4 ];

	/* Compression flags
	 * Consists of 1 byte
	 */
	uint8_t compression_flags;

	/* Operating system
	 * Consists of 1 byte
	 */
	uint8_t operating_system;
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _GZIPF_MEMBER_HEADER_H ) */

