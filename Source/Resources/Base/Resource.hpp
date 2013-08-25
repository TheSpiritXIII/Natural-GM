/**
 *  @file Resource.hpp
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
#ifndef _NGM_RESOURCE__HPP
#define _NGM_RESOURCE__HPP
#include "../Global.hpp"
#include "SerialData.hpp"
#include <QByteArray>
#include "Type.hpp"
#include <QString>
#include <string>
#include <map>

namespace NGM
{
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	Contains resource data.
		******************************************************/
		struct Resource
		{

			/**************************************************//*!
			*	@brief	Flags that describe the resources's status.
			******************************************************/
			enum StatusBits
			{
				Loaded      =   0x01,
				Cached		=	0x02,
				HasError	=	0x04,
				IsFilename	=	0x08
			};

			/**************************************************//*!
			*	@brief	Contains the status of the resource.
			******************************************************/
			uint8_t status;

			/**************************************************//*!
			*	@brief	The type identifier of the resource.
			******************************************************/
			const Type * const type;

			/**************************************************//*!
			*	@brief	Holds all resource data.
			******************************************************/
			SerialObject *serialData;

			/**************************************************//*!
			*	@brief	Stores the file location of the resource.
			******************************************************/
			QString location;

			/**************************************************//*!
			*	@brief	Returns the icon for this resource type.
			******************************************************/
			virtual QIcon getIcon() { return type->icon; }

			/**************************************************//*!
			*	@brief	Initializes the resource.
			******************************************************/
			Resource(const Type * const type, QString location, uint8_t status = 0);
		};
	}
}

#endif // _NGM_RESOURCE__HPP
