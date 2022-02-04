/*
 * Member footer of a GZIP file
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

#if !defined( _GZIPF_MEMBER_FOOTER_H )
#define _GZIPF_MEMBER_FOOTER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct gzipf_member_footer gzipf_member_footer_t;

struct gzipf_member_footer
{
	/* Checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* Uncompressed data size
	 * Consists of 4 bytes
	 */
	uint8_t uncompressed_data_size[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _GZIPF_MEMBER_FOOTER_H ) */

