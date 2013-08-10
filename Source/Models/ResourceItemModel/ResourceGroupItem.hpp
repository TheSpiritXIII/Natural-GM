/**
 *  @file ResourceGroupItem.hpp
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
#ifndef _NGM_RESOURCEGROUPITEM__HPP
#define _NGM_RESOURCEGROUPITEM__HPP
#include "ResourceBaseItem.hpp"
#include <vector>

namespace NGM
{
	namespace Model
	{
		/**************************************************//*!
		*	@brief An item that store children. This class can
		*		   only be used with ResourceItemModel.
		******************************************************/
		class ResourceGroupItem : public ResourceBaseItem
		{
		public:

			/**************************************************//*!
			*	@brief Creates an item with the indicated name.
			******************************************************/
			ResourceGroupItem(const QString &name) : ResourceBaseItem(name) {}

			/**************************************************//*!
			*	@return The number of children this item contains.
			******************************************************/
			int count() const;

			/**************************************************//*!
			*	@return The child at the indicated row.
			******************************************************/
			ResourceBaseItem *child(int row);

			std::vector<ResourceBaseItem*> take(int row, int count);

			/**************************************************//*!
			*	@return Appends an item to this item as a child. This is fast.
			******************************************************/
			void append(ResourceBaseItem *item);

			/**************************************************//*!
			*	@return Appends multiple children at once. This is fast.
			******************************************************/
			void append(std::vector<ResourceBaseItem*> items);

			/**************************************************//*!
			*	@return Removes the indicated number of children from the back.
			******************************************************/
			void pop(int count  = 1);

			/**************************************************//*!
			*	@return Removes the children at the indicated rows.
			******************************************************/
			void remove(int row, int count = 1);

			/**************************************************//*!
			*	@return Removes and returns the children at the indicated rows.
			******************************************************/
			//std::vector<ResourceBaseItem*> take(int row, int count = 1);

			/**************************************************//*!
			*	@return Inserts a children at the indicated row.
			******************************************************/
			void insert(ResourceBaseItem *item, int row);

			/**************************************************//*!
			*	@return Inserts multiple children to the indicated row.
			******************************************************/
			void insert(std::vector<ResourceBaseItem*> items, int row);

			/**************************************************//*!
			*	@return A safe case to a ResourceGroupItem. Returns this.
			******************************************************/
			ResourceGroupItem *toResourceGroupItem();

		protected:

			friend class ResourceBaseItem;

			/**************************************************//*!
			*	@brief Contains all of its children.
			******************************************************/
			std::vector<ResourceBaseItem*> _children;
		};
	}
}

#endif // _NGM_RESOURCEGROUPITEM__HPP
