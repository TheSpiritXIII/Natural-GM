/**
 *  @file Global.hpp
 *  @brief Defines macros.
 *
 *  @section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
 *
 *      This file is a part of the Natural GM IDE.
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#pragma once
#ifndef _NGM_GLOBAL__HPP
#define _NGM_GLOBAL__HPP
#ifdef NGM_DEBUG
#include <QDebug>
#endif
#include <stdint.h>

namespace NGM
{
	const uint8_t MAJOR = 0;
	const uint8_t MINOR = 1;
	const uint16_t BUILD = 1;
}

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

// Enable threading if GCC 4.8 or higher is detected.
#ifdef __GNUC__
	#if __GNUC__ < 5
		#if __GNUC__ == 4
			#if __GNUC_MINOR__ > 7
				#define NGM_THREADS
			#endif
		#endif
	#else
		#define NGM_THREADS
	#endif
#endif

// Ensure localization.
//#define QT_NO_CAST_TO_ASCII
//#define QT_NO_CAST_FROM_ASCII

#endif // _NGM_GLOBAL__HPP
