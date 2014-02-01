/**
 *  @file Project.hpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
 *
 *      This file is part of the Natural GM IDE.
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
#ifndef NGM__RESOURCE_PROJECT__HPP
#define NGM__RESOURCE_PROJECT__HPP
#include "FileDetails.hpp"
#include <QString>
#include <QIcon>

namespace NGM
{
	namespace Resource
	{
		struct Serializer;
		struct Type;

		/**************************************************//*!
		*	@brief	Metadata for project types.
		******************************************************/
		struct Project
		{
			/**************************************************//*!
			*	@brief	Defines the types of projects. A
			*			GroupType is a project type that can
			*			contain groups of files, while a FileType
			*			is a type that only stores itself as a
			*			single file.
			******************************************************/
			enum ProjectType : char
			{
				GroupType	=	0x1,
				FileType	=	0x2
			};

			/**************************************************//*!
			*	@brief	Initializes all member variables.
			*	@param	category You may add a '-' to denote that
			*			a subgroup. For example "General-Other"
			*			would have "Other" as a subgroup of
			*			"General".
			*	@param	type The resource type, or nullptr. If
			*			this is nullptr, then a basic group icon
			*			is displayed. Otherwise, the type icon
			*			is displayed and if the type provides a
			*			factory, it can also be opened in an
			*			editor.
			******************************************************/
			Project(const QString name, const QString category,
					const QString description, const FileDetails extensions,
					const Serializer *const serializer,
					const Type * const type = nullptr,
					const ProjectType projectType = GroupType);

			/**************************************************//*!
			*	@brief	The name of this project type.
			******************************************************/
			const QString name;

			/**************************************************//*!
			*	@brief	The category of which the project
			* 			belongs to.
			******************************************************/
			const QString category;

			/**************************************************//*!
			*	@brief	Contains a short description but
			*			detailed description of the project type.
			******************************************************/
			const QString description;

			/**************************************************//*!
			*	@brief	Contains a list of extensions used in
			*			the project type.
			******************************************************/
			const FileDetails extensions;

			/**************************************************//*!
			*	@brief	Loads and saves the resources used in
			*			this project type.
			******************************************************/
			const Serializer * const serializer;

			/**************************************************//*!
			*	@brief	Stores icons and factories.
			******************************************************/
			const Type * const type;

			/**************************************************//*!
			*	@brief	Contains a large project display icon.
			*			This is managed by the icon manager, so
			*			changing this yourself will have
			*			undesirable consequences.
			******************************************************/
			QIcon icon;

			/**************************************************//*!
			*	@brief	Decides whether or not this project type
			*			creates groups or not. This is only a
			*			hint, it does not need to be true.
			******************************************************/
			const ProjectType projectType;
		};
	}
}

#endif // NGM__RESOURCE_PROJECT__HPP
