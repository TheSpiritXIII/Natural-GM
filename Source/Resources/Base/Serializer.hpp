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
				ResaveAll	=	0x01,
				CanPreload		=	0x02,
				CanMoveRoots	=	0x04,
				CanRenameRoots	=	0x08,
				PathResources	=	0x10,
				CanBeTemporary	=	0x20
			};

			/**************************************************//*!
			*	@brief	Options for reading and writing data.
			******************************************************/
			enum Options
			{
				IsPreloaded		=	0x01,
				DynamicIcons	=	0x02
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
			virtual bool structure(Model::ResourceProjectItem *item, QProgressBar *progressBar) const = 0;

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
