/**
 *  @file Global.hpp
 *	@section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
 *
 *      This file is a part of the Natural GM IDE. MIT License.
 *
 *      Permission is hereby granted, free of charge, to any person obtaining a copy
 *		of this software and associated documentation files (the "Software"), to deal
 *		in the Software without restriction, including without limitation the rights
 *		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *		copies of the Software, and to permit persons to whom the Software is
 *		furnished to do so, subject to the following conditions:
 *
 *		The above copyright notice and this permission notice shall be included in
 *		all copies or substantial portions of the Software.
 *
 *		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *		THE SOFTWARE.
**/
#pragma once
#ifndef _NGM_GLOBAL__HPP
#define _NGM_GLOBAL__HPP
#ifdef NGM_DEBUG
#include <QDebug>
#endif
#include <QString>
#include <cstdint>

namespace NGM
{
	const uint16_t BUILD		=	0;
#ifdef NGM_CPP_SUPPORT_GOOD
#error When C++11 support is good everywhere, optimizations must be made.
#endif
	const QString		NGM_APPLICATION_NAME		=	"Natural GM 0.1.0";
	const QString		NGM_APPLICATION_KEY			=	QStringLiteral("Natural-GM-Application");
}

// Useful function pointer macro.
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
