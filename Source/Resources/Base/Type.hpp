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
#include "Deque.hpp"
#include "String.hpp"

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
		class Factory;
		class SerialObject;

		/**************************************************//*!
		*	@brief	Metadata for resource types. Manages the
		*			creation for editors.
		******************************************************/
		class Type
		{
		public:

			/**************************************************//*!
			*	@brief	Creates a type with the specified name.
			*			The factory is placed into the queue.
			*	@see	factories
			******************************************************/
			Type(const QString &name, const Factory *factory) : name(name)
			{
				factories.push_back(factory);
			}

			/**************************************************//*!
			*	@brief	Deallocates all factories.
			******************************************************/
			~Type();

			/**************************************************//*!
			*	@brief	Creates a type with the specified name.
			*			You must add factories manually before
			*			you can use this class properly.
			******************************************************/
			Type(const QString &name) : name(name) {}

			/**************************************************//*!
			*	@brief	A visual representation of the type.
			*	@see	ActionManager
			*
			*	The icon is loaded from the
			*	icons/[theme]/projects folder. The filepath is
			*	set as the type name.
			******************************************************/
			QIcon icon;

			/**************************************************//*!
			*	@brief	The Qt based action for this creating
			*			a resource of this type.
			*	@see	ActionManager
			*
			*	This is stored here for simplicity. No class
			*	should really have a need to access this.
			******************************************************/
			QAction *action;

			/**************************************************//*!
			*	@brief	Returns a widget for editing this type.
			******************************************************/
			Editor *create(const Model::ResourceProjectItem * const item,
						   Widget::ResourceTab * const tab) const;

			/**************************************************//*!
			*	@brief	Returns an icon representative of the
			*			type. If data has a child named icon,
			*			then it simply returns that if and only
			*			if it is a Variant of an Icon type.
			*	@see	Variant
			******************************************************/
			const QIcon &getIcon(SerialObject *data) const;

			/**************************************************//*!
			*	@brief	Returns the queue of factories. This is
			*			useful for the iterating over editors.
			******************************************************/
			inline const Deque<const Factory*> &queue() const
			{
				return factories;
			}

			/**************************************************//*!
			*	@brief	Adds a new factory. It does not check if
			*			the factory already exists.
			*	@see	queue();
			******************************************************/
			void addFactory(Factory *factory)
			{
				factories.push_back(factory);
			}

			/**************************************************//*!
			*	@brief	Stores the type name.
			******************************************************/
			const QString name;

			/**************************************************//*!
			*	@brief	Sorting is done by name.
			******************************************************/
			inline bool operator< (const Type &right) const
			{
				return this->name < right.name;
			}

			/**************************************************//*!
			*	@brief	For finding strings faster in sets.
			******************************************************/
			inline bool operator< (const QString &right) const
			{
				return this->name < right;
			}

		private:

			/**************************************************//*!
			*	@brief	Factories to create editors of this
			*			resource type.
			******************************************************/
			Deque<const Factory*> factories;

		};
	}
}

#endif // _NGM_RESOURCE_Type__HPP
