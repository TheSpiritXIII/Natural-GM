/**
 *  @file Resource.hpp
 *	@section License
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
#ifndef _NGM_RESOURCE_RESOURCE__HPP
#define _NGM_RESOURCE_RESOURCE__HPP
#include "../Global.hpp"
#include "SerialData.hpp"
#include <QByteArray>
#include "Type.hpp"
#include <QString>
#include <string>
#include <map>
#include "Queue.hpp"

namespace NGM
{
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	Holds status flags for resources.
		*	@see	Resource::Status
		******************************************************/
		typedef uint8_t ResourceSettings;

		/**************************************************//*!
		*	@brief	Contains resource content data.
		*
		* The file path is optional because there may not be
		* a file path or the file path is not a system path.
		* A system path might be helpful to a serializer. For
		* example, a zip path can be stored that way (because
		* zip files are not exactly system paths). For this
		* reason, a boolean exists to test whether or not
		* the file path was meant to be a system path.
		******************************************************/
		struct Content
		{
			/**************************************************//*!
			*	@brief	Hints for how the user interacts with
			*			this item.
			******************************************************/
			enum Setting
			{
				IsSystemPath	=	0x1,	/*!< Hints that the file path
												should be a real path. */
				NoExtension		=	0x2		/*!< Omits the extension when
												displaying the file name. */
			};

			/**************************************************//*!
			*	@brief	Initializes the resource.
			******************************************************/
			Content(const Type *const type, QString filepath = QString(),
				ResourceSettings settings = 0);

			/**************************************************//*!
			*	@brief	The type identifier of the resource.
			******************************************************/
			const Type * const type;

			/**************************************************//*!
			*	@brief	Holds all resource data.
			******************************************************/
			SerialObject *serialData;

			/**************************************************//*!
			*	@brief	Stores a filepath.
			******************************************************/
			QString filepath;

			/**************************************************//*!
			*	@brief	Resource display hints.
			******************************************************/
			ResourceSettings settings;

			/**************************************************//*!
			*	@brief	The resource display icon.
			******************************************************/
			QIcon icon;
		};
	}
}

#endif // _NGM_RESOURCE_RESOURCE__HPP
