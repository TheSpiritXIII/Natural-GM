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
		typedef uint8_t ResourceStatus;

		/**************************************************//*!
		*	@brief	Contains resource data.
		******************************************************/
		struct Resource
		{

			/**************************************************//*!
			*	@brief	Flags that describe the resources's status.
			*
			*	IsFilename is probably the most important flag.
			*	If set, resources can be opened by general
			*	editors (hex/text editors). The file is also
			*	added to the file watcher when being opened.
			******************************************************/
			enum Status
			{
				// Decides whether the resource's location is a true path.
				IsFilename	=	0x01
			};

			/**************************************************//*!
			*	@brief	Contains the status of the resource.
			* 	@see	StatusFlags
			******************************************************/
			ResourceStatus status;

			/**************************************************//*!
			*	@brief	The type identifier of the resource.
			******************************************************/
			const Type * const type;

			/**************************************************//*!
			*	@brief	Holds all resource data.
			******************************************************/
			SerialObject *serialData;

			/**************************************************//*!
			*	@brief	Stores the file location of the
			*			resource. The status should have an
			* 			IsModified flag set if the location
			*			is set.
			******************************************************/
			QString location;
			
			QIcon icon;

			/**************************************************//*!
			*	@brief	Initializes the resource.
			******************************************************/
			Resource(const Type * const type, QString location,
				const ResourceStatus status = 0);

		};
	}
}

#endif // _NGM_RESOURCE_RESOURCE__HPP
