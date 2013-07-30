/**
 *  @file Serializer.hpp
 *  @brief Declares a virtual serializer class which handles the loading of data.
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
#ifndef _NGM_SERIALIZER__HPP
#define _NGM_SERIALIZER__HPP
#include <QString>
#include "ResourceContentItem.hpp"

namespace NGM
{
	namespace Model
	{
		class ResourceItem;
	}

	namespace Resource
	{
		class Widget;
		struct Serializer
		{
			/*! Bits that determine how a file was changed. */
			enum Changed : unsigned char
			{
				Renamed			=	0b00000001,
				Moved			=	0b00000010,
				Deleted			=	0b00000100
			};

			/*! Setting bits that aid project loading and saving. */
			enum Settings : unsigned char
			{
				ResaveAll		=	0b00000001,
				CanPreload		=	0b00000010,
				ForcePreload	=	0b00000100,
				CanRearrange	=	0b00001000,
				CanMoveRoots	=	0b00010000,
				CanRenameRoots	=	0b00100000,
				PathResources	=	0b01000000,
				CanBeTemporary	=	0b10000000
			};

			/*! Reads a resource and inputs the data onto a widget. */
			virtual void read(Widget *widget, Resource *resource) = 0;

			/*! Writes a resource based on widget data. */
			//void write(Widget *widget, Resource *resource);

			/*! Loads a file and stores it into a tree item. */
			//virtual Model::ResourceItem* loadFile(Model::ResourceItem *item, QString location, Manager::ProjectManager *manager, bool preload) = 0;

			/*! Saves a file from a tree item. */
			//virtual void saveFile(QString location, Model::ResourceItem) {}

			/*! Requests the serializer to updates the given file. */
			//virtual void update(Changed changed, QString previous, QString current = "") {}

			virtual char settings() { return _settings; }

		private:

			/*! Contains settings bits. */
			const char _settings = 0;
		};
	}
}

#endif // _NGM_SERIALIZER__HPP
