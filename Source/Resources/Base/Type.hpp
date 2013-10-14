/**
 *  @file Type.hpp
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
#ifndef _NGM_RESOURCE_TYPE__HPP
#define _NGM_RESOURCE_TYPE__HPP
#include <QString>
#include <QAction>
#include "Map.hpp"
#include "String.hpp"
#include "Vector.hpp"

namespace NGM
{
	namespace Widget
	{
		class ResourceTab;
	}
	namespace Model
	{
		class ResourceProjectItem;
	}
	namespace Resource
	{
		class Editor;
		class SerialObject;

		typedef Editor *(*EditorPointer)(const Model::ResourceProjectItem * const,
									 Widget::ResourceTab * const);

		/**************************************************//*!
		*	@brief	Metadata for resource types.
		******************************************************/
		class Type
		{
		public:

			/**************************************************//*!
			*	@brief	The editor type name.
			******************************************************/
			const QString name;

			/**************************************************//*!
			*	@brief	The plural name. This is used in tabs
			*			and groups.
			******************************************************/
			const QString plural;

			/**************************************************//*!
			*	@brief	A visual representation of the type.
			*	@see	name
			*
			*	The icon is loaded from the icons/[theme]/types
			*	folder. The filepath is set as the human
			*	readable name.
			******************************************************/
			QIcon icon;

			/**************************************************//*!
			*	@brief	The Qt based action for this creating
			*			a resource of this type.
			*
			*	This is stored here for simplicity. No class
			*	should really have a need to use this.
			******************************************************/
			QAction *action;

			/**************************************************//*!
			*	@brief	Returns a widget for editing this type.
			******************************************************/
			virtual Editor *widget(const Model::ResourceProjectItem * const item,
								   Widget::ResourceTab * const tab) const = 0;

			/**************************************************//*!
			*	@brief	Returns an icon representative of the
			*			type. Types should specify which part
			*			of the data is searched for the icon.
			******************************************************/
			virtual const QIcon &getIcon(SerialObject *data) const;

			/**************************************************//*!
			*	@brief	Function pointers to create editors of
			*			this resource type.
			******************************************************/
			Vector<Pair<String, EditorPointer>> editors;

			/**************************************************//*!
			*	@brief	Sets up constant metadata.
			******************************************************/
			Type(const QString &name, const QString &plural);

		};
	}
}

#endif // _NGM_RESOURCE_Type__HPP
