/*
 * Codepage definitions for libgzipf
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

#if !defined( _LIBGZIPF_CODEPAGE_H )
#define _LIBGZIPF_CODEPAGE_H

#include <libgzipf/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBGZIPF_CODEPAGES
{
	LIBGZIPF_CODEPAGE_ASCII				= 20127,

	LIBGZIPF_CODEPAGE_ISO_8859_1			= 28591,
	LIBGZIPF_CODEPAGE_ISO_8859_2			= 28592,
	LIBGZIPF_CODEPAGE_ISO_8859_3			= 28593,
	LIBGZIPF_CODEPAGE_ISO_8859_4			= 28594,
	LIBGZIPF_CODEPAGE_ISO_8859_5			= 28595,
	LIBGZIPF_CODEPAGE_ISO_8859_6			= 28596,
	LIBGZIPF_CODEPAGE_ISO_8859_7			= 28597,
	LIBGZIPF_CODEPAGE_ISO_8859_8			= 28598,
	LIBGZIPF_CODEPAGE_ISO_8859_9			= 28599,
	LIBGZIPF_CODEPAGE_ISO_8859_10			= 28600,
	LIBGZIPF_CODEPAGE_ISO_8859_11			= 28601,
	LIBGZIPF_CODEPAGE_ISO_8859_13			= 28603,
	LIBGZIPF_CODEPAGE_ISO_8859_14			= 28604,
	LIBGZIPF_CODEPAGE_ISO_8859_15			= 28605,
	LIBGZIPF_CODEPAGE_ISO_8859_16			= 28606,

	LIBGZIPF_CODEPAGE_KOI8_R				= 20866,
	LIBGZIPF_CODEPAGE_KOI8_U				= 21866,

	LIBGZIPF_CODEPAGE_WINDOWS_874			= 874,
	LIBGZIPF_CODEPAGE_WINDOWS_932			= 932,
	LIBGZIPF_CODEPAGE_WINDOWS_936			= 936,
	LIBGZIPF_CODEPAGE_WINDOWS_949			= 949,
	LIBGZIPF_CODEPAGE_WINDOWS_950			= 950,
	LIBGZIPF_CODEPAGE_WINDOWS_1250			= 1250,
	LIBGZIPF_CODEPAGE_WINDOWS_1251			= 1251,
	LIBGZIPF_CODEPAGE_WINDOWS_1252			= 1252,
	LIBGZIPF_CODEPAGE_WINDOWS_1253			= 1253,
	LIBGZIPF_CODEPAGE_WINDOWS_1254			= 1254,
	LIBGZIPF_CODEPAGE_WINDOWS_1255			= 1255,
	LIBGZIPF_CODEPAGE_WINDOWS_1256			= 1256,
	LIBGZIPF_CODEPAGE_WINDOWS_1257			= 1257,
	LIBGZIPF_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBGZIPF_CODEPAGE_US_ASCII			LIBGZIPF_CODEPAGE_ASCII

#define LIBGZIPF_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBGZIPF_CODEPAGE_ISO_8859_1
#define LIBGZIPF_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBGZIPF_CODEPAGE_ISO_8859_2
#define LIBGZIPF_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBGZIPF_CODEPAGE_ISO_8859_3
#define LIBGZIPF_CODEPAGE_ISO_NORTH_EUROPEAN		LIBGZIPF_CODEPAGE_ISO_8859_4
#define LIBGZIPF_CODEPAGE_ISO_CYRILLIC			LIBGZIPF_CODEPAGE_ISO_8859_5
#define LIBGZIPF_CODEPAGE_ISO_ARABIC			LIBGZIPF_CODEPAGE_ISO_8859_6
#define LIBGZIPF_CODEPAGE_ISO_GREEK			LIBGZIPF_CODEPAGE_ISO_8859_7
#define LIBGZIPF_CODEPAGE_ISO_HEBREW			LIBGZIPF_CODEPAGE_ISO_8859_8
#define LIBGZIPF_CODEPAGE_ISO_TURKISH			LIBGZIPF_CODEPAGE_ISO_8859_9
#define LIBGZIPF_CODEPAGE_ISO_NORDIC			LIBGZIPF_CODEPAGE_ISO_8859_10
#define LIBGZIPF_CODEPAGE_ISO_THAI			LIBGZIPF_CODEPAGE_ISO_8859_11
#define LIBGZIPF_CODEPAGE_ISO_BALTIC			LIBGZIPF_CODEPAGE_ISO_8859_13
#define LIBGZIPF_CODEPAGE_ISO_CELTIC			LIBGZIPF_CODEPAGE_ISO_8859_14

#define LIBGZIPF_CODEPAGE_ISO_LATIN_1			LIBGZIPF_CODEPAGE_ISO_8859_1
#define LIBGZIPF_CODEPAGE_ISO_LATIN_2			LIBGZIPF_CODEPAGE_ISO_8859_2
#define LIBGZIPF_CODEPAGE_ISO_LATIN_3			LIBGZIPF_CODEPAGE_ISO_8859_3
#define LIBGZIPF_CODEPAGE_ISO_LATIN_4			LIBGZIPF_CODEPAGE_ISO_8859_4
#define LIBGZIPF_CODEPAGE_ISO_LATIN_5			LIBGZIPF_CODEPAGE_ISO_8859_9
#define LIBGZIPF_CODEPAGE_ISO_LATIN_6			LIBGZIPF_CODEPAGE_ISO_8859_10
#define LIBGZIPF_CODEPAGE_ISO_LATIN_7			LIBGZIPF_CODEPAGE_ISO_8859_13
#define LIBGZIPF_CODEPAGE_ISO_LATIN_8			LIBGZIPF_CODEPAGE_ISO_8859_14
#define LIBGZIPF_CODEPAGE_ISO_LATIN_9			LIBGZIPF_CODEPAGE_ISO_8859_15
#define LIBGZIPF_CODEPAGE_ISO_LATIN_10			LIBGZIPF_CODEPAGE_ISO_8859_16

#define LIBGZIPF_CODEPAGE_KOI8_RUSSIAN			LIBGZIPF_CODEPAGE_KOI8_R
#define LIBGZIPF_CODEPAGE_KOI8_UKRAINIAN			LIBGZIPF_CODEPAGE_KOI8_U

#define LIBGZIPF_CODEPAGE_WINDOWS_THAI			LIBGZIPF_CODEPAGE_WINDOWS_874
#define LIBGZIPF_CODEPAGE_WINDOWS_JAPANESE		LIBGZIPF_CODEPAGE_WINDOWS_932
#define LIBGZIPF_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBGZIPF_CODEPAGE_WINDOWS_936
#define LIBGZIPF_CODEPAGE_WINDOWS_KOREAN			LIBGZIPF_CODEPAGE_WINDOWS_949
#define LIBGZIPF_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBGZIPF_CODEPAGE_WINDOWS_950
#define LIBGZIPF_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBGZIPF_CODEPAGE_WINDOWS_1250
#define LIBGZIPF_CODEPAGE_WINDOWS_CYRILLIC		LIBGZIPF_CODEPAGE_WINDOWS_1251
#define LIBGZIPF_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBGZIPF_CODEPAGE_WINDOWS_1252
#define LIBGZIPF_CODEPAGE_WINDOWS_GREEK			LIBGZIPF_CODEPAGE_WINDOWS_1253
#define LIBGZIPF_CODEPAGE_WINDOWS_TURKISH			LIBGZIPF_CODEPAGE_WINDOWS_1254
#define LIBGZIPF_CODEPAGE_WINDOWS_HEBREW			LIBGZIPF_CODEPAGE_WINDOWS_1255
#define LIBGZIPF_CODEPAGE_WINDOWS_ARABIC			LIBGZIPF_CODEPAGE_WINDOWS_1256
#define LIBGZIPF_CODEPAGE_WINDOWS_BALTIC			LIBGZIPF_CODEPAGE_WINDOWS_1257
#define LIBGZIPF_CODEPAGE_WINDOWS_VIETNAMESE		LIBGZIPF_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBGZIPF_CODEPAGE_H ) */

