/**
 *  @file Serializer.hpp
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
#ifndef _NGM_SERIALIZER__HPP
#define _NGM_SERIALIZER__HPP
#include "ResourceProjectItem.hpp"
#include <QString>

namespace NGM
{
	namespace Model
	{
		class ResourceItem;
	}

	namespace Resource
	{
		class Widget;

		/**************************************************//*!
		*	@brief	Loads and creates project structures.
		******************************************************/
		struct Serializer
		{
			/**************************************************//*!
			*	@brief	Determines how a file was changed.
			******************************************************/
			enum Changed : unsigned char
			{
				Renamed			=	0x01,//0b00000001,
				Moved			=	0x02,//0b00000010,
				Deleted			=	0x04//0b00000100
			};

			/**************************************************//*!
			*	@brief	Settings bits.
			******************************************************/
			enum Settings : unsigned char
			{
				ResaveAll		=	0x01,//0b00000001,
				CanPreload		=	0x02,//0b00000010,
				ForcePreload	=	0x04,//0b00000100,
				CanRearrange	=	0x08,//0b00001000,
				CanMoveRoots	=	0x10,//0b00010000,
				CanRenameRoots	=	0x20,//0b00100000,
				PathResources	=	0x40,//0b01000000,
				CanBeTemporary	=	0x80//0b10000000
			};

			/**************************************************//*!
			*	@brief	Reads a resource and inputs data into a widget.
			******************************************************/
			virtual void read(Widget *widget, Resource *resource) = 0;

			/**************************************************//*!
			*	@brief	Writes a resource based on widget data.
			******************************************************/
			virtual void write(Widget *widget, Resource *resource) = 0;

			/**************************************************//*!
			*	@brief	Creates the project tree structure.
			******************************************************/
			virtual void structure(Model::ResourceProjectItem *item) = 0;

			/**************************************************//*!
			*	@brief	Restructures changed files.
			******************************************************/
			virtual void restructure(const QString &file, Changed changed) = 0;

			/**************************************************//*!
			*	@brief	Determines how the project is structured.
			******************************************************/
			virtual char settings() { return 0; }
		};
	}
}

#endif // _NGM_SERIALIZER__HPP
