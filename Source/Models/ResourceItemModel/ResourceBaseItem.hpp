/**
 *  @file ResourceBaseItem.hpp
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
#ifndef _NGM_RESOURCEBASEITEM__HPP
#define _NGM_RESOURCEBASEITEM__HPP
#include <QString>
#include <QVariant>

namespace NGM
{
	namespace Model
	{
		class ResourceItemModel;
		class ResourceGroupItem;
		class ResourceProjectItem;
		class ResourceContentItem;

		/**************************************************//*!
		*	@brief	An item that stores only its parent. This
		*			class can only be used with ResourceItemModel.
		******************************************************/
		class ResourceBaseItem
		{
		public:

			/**************************************************//*!
			*	@brief Creates an item with the indicated name.
			******************************************************/
			ResourceBaseItem(const QString &name);

			/**************************************************//*!
			*	@return The string name of this item.
			******************************************************/
			QVariant data() const;

			/**************************************************//*!
			*	@return The model index of the item.
			******************************************************/
			const QModelIndex index();

			/**************************************************//*!
			*	@return	The row this item is inside its parent, or
			*			-1 if the item does not have a parent yet.
			*			NOTE: This is very slow.
			******************************************************/
			int row() const;

			/**************************************************//*!
			*	@return The item that holds this as a child, or NULL.
			******************************************************/
			ResourceBaseItem *parent();

			/**************************************************//*!
			*	@return A safe cast to a ResourceContentItem.
			******************************************************/
			virtual ResourceContentItem *toResourceContentItem();

			/**************************************************//*!
			*	@brief A safe cast to a project item.
			******************************************************/
			virtual ResourceProjectItem *toResourceProjectItem();

			/**************************************************//*!
			*	@brief A safe cast to a group item.
			******************************************************/
			virtual ResourceGroupItem *toResourceGroupItem();

			/**************************************************//*!
			*	@brief Returns the root project item.
			******************************************************/
			ResourceProjectItem *root();

		protected:

			friend class ResourceItemModel;
			friend class ResourceGroupItem;

			/**************************************************//*!
			*	@return	The root project item. This is defined by
			*			itself when appended.
			******************************************************/
			ResourceProjectItem *_root;

			/**************************************************//*!
			*	@brief	Stores the parent. This is defined by
			*			itself when appended.
			******************************************************/
			ResourceBaseItem *_parent;

			/**************************************************//*!
			*	@brief	Stores the model. This is necessary for
			*			obtaining the index.
			******************************************************/
			ResourceItemModel *_model;

			/**************************************************//*!
			*	@brief	Stores the string name of this item.
			******************************************************/
			QVariant _data;
		};
	}
}

#endif // _NGM_RESOURCEBASEITEM__HPP
