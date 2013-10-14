/**
 *  @file Project.hpp
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
#ifndef _NGM_RESOURCE_PROJECT__HPP
#define _NGM_RESOURCE_PROJECT__HPP
#include "Type.hpp"
#include <QString>
#include <QIcon>

namespace NGM
{
	namespace Resource
	{
		struct Serializer;

		/**************************************************//*!
		*	@brief	Metadata for project types.
		******************************************************/
		struct Project
		{

			/**************************************************//*!
			*	@brief	The serializer is what loads and saves
			*			the resources used in this project type.
			******************************************************/
			const Serializer * const serializer;

			/**************************************************//*!
			*	@brief	The resource item type. Stores icons
			* 			and other useful metadata.
			******************************************************/
			const Type * const type;

			/**************************************************//*!
			*	@brief	The category of which the project
			* 			belongs to.
			******************************************************/
			const QString category;

			/**************************************************//*!
			*	@brief	Contains a short description but
			*			detailed of the project type.
			*
			*	A description can use basic formatting tags
			*	provided by Qt's QLabel rendering engine.
			******************************************************/
			const QString description;

			/**************************************************//*!
			*	@brief	Contains a list of extensions used in
			*			the project type.
			*
			*	Only very basic regex support is provided. You
			*	may add only an asterix in the beginning or
			*	end of the extension name, to indicated that
			*	a name is variable or extension is variable
			*	respectively.
			******************************************************/
			const QStringList extensions;

			/**************************************************//*!
			*	@brief	Initializes all member variables.
			******************************************************/
			Project(const Serializer * const serializer, const Type * const type,
					const QString category, const QString description, const QStringList extensions);

		};
	}
}

#endif // _NGM_RESOURCE_PROJECT__HPP
