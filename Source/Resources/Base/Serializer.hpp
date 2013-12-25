/**
 *  @file Serializer.hpp
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
#ifndef _NGM_SERIALIZER__HPP
#define _NGM_SERIALIZER__HPP
#include "ResourceProjectItem.hpp"
#include "Variant.hpp"
#include <QProgressBar>
#include <QString>
#include <cstdint>

namespace NGM
{
	namespace Manager
	{
		class ProjectManager;
	}
	namespace Resource
	{
		class Editor;

		typedef uint8_t SerializerOptions;
		typedef uint8_t SerializerSettings;

		/**************************************************//*!
		*	@brief	Loads and creates project structures.
		******************************************************/
		struct Serializer
		{

			/**************************************************//*!
			*	@brief	Flags for serializer settings.
			******************************************************/
			enum Settings
			{
				// Requests the serializer to call save after write.
				ResaveAll	=	0x01,
				// Allows the user to move and rename root structures.
				CanModifyRoots	=	0x02,
				// Sorts items except roots automatically. They cannot be moved.
				AutoSortItems	=	0x04,
				// Does not let the user move items, even if not sorted.
				NonMovableItems	=	0x08,
				// Requests the serializer to set the working directory before read.
				SetWorkingDir	=	0x10
			};

			/**************************************************//*!
			*	@brief	Options for reading and writing data.
			******************************************************/
			enum Options
			{
				DynamicIcons	=	0x01
			};

			/**************************************************//*!
			*	@brief	Sets the indicated settings.
			******************************************************/
			Serializer(const SerializerSettings &settings = 0);

			/**************************************************//*!
			*	@brief	Inputs resource data to editor data.
			******************************************************/
			virtual void read(Editor *editor, Resource *resource, const SerializerOptions &options = 0) const = 0;

			/**************************************************//*!
			*	@brief	Outputs editor data to resource data.
			******************************************************/
			virtual void write(Editor *editor, Resource *resource, const SerializerOptions &options = 0) const = 0;

			/**************************************************//*!
			*	@brief	Creates the project tree structure.
			******************************************************/
			virtual bool structure(Model::ResourceProjectItem *item,
				const Manager::ProjectManager *projectManager,
				QProgressBar *progressBar) const = 0;

			/**************************************************//*!
			*	@brief	Requests a restructure of the indicated item.
			******************************************************/
			virtual void restructure(Model::ResourceProjectItem *item) const = 0;

			/**************************************************//*!
			*	@brief	Determines how the project is structured.
			*	@see	Settings
			******************************************************/
			const SerializerSettings settings;

		};
	}
}

#endif // _NGM_SERIALIZER__HPP
