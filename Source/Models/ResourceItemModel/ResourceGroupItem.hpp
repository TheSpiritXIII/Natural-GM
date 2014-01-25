/**
 *  @file ResourceGroupItem.hpp
 *  @section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#ifndef NGM__RESOURCEGROUPITEM__HPP
#define NGM__RESOURCEGROUPITEM__HPP
#include "ResourceBaseItem.hpp"
#include <QList>

// REMOVE
#include <vector>
#include <QVector>

namespace NGM
{
	namespace Model
	{
		typedef QList<NGM::Model::ResourceBaseItem*>::iterator
			ResourceItemIterator;

		/**************************************************//*!
		*	@brief	An item that store children. Children
		*			should either be content items or group
		*			items.
		*
		* This item is dependent on the model. If the model
		* has sorting enabled, then the behavior of several
		* functions change.
		******************************************************/
		class ResourceGroupItem : public ResourceBaseItem
		{
		public:

			/**************************************************//*!
			*	@brief Creates an item with the indicated name.
			******************************************************/
			ResourceGroupItem(const QString &name = QString());

			/**************************************************//*!
			*	@brief	Deallocates and removes all children.
			******************************************************/
			~ResourceGroupItem();

			/**************************************************//*!
			*	@brief	Sorts all child items alphebatically
			*			recursively.
			******************************************************/
			void sort();

			/**************************************************//*!
			*	@brief	Returns the number of children this item
			*			contains.
			******************************************************/
			inline int count() const
			{
				return _children.size();
			}

			/**************************************************//*!
			*	@brief	Returns the child at the indicated
			*			position.
			******************************************************/
			inline ResourceBaseItem *child(int position) const
			{
				return _children[position];
			}

			/**************************************************//*!
			*	@brief	Returns the position that the child is
			*			located. If the model is sorted, then
			*			this is an O(logn) find. Returns -1 if
			*			the child could not be found.
			******************************************************/
			int childPosition(const ResourceBaseItem *find) const;

			/**************************************************//*!
			*	@beif	Inserts a child. If sorting is enabled,
			*			the item is placed alphabetically. If
			*			sorting is not enabled, this item is
			*			placed at the end.
			******************************************************/
			void insert(ResourceBaseItem *item);

			/**************************************************//*!
			*	@beif	Inserts a child into the indicated
			*			position, provided sorting is not
			*			enabled.
			******************************************************/
			void insert(ResourceBaseItem *item, int position);

			/**************************************************//*!
			*	@brief	Removes the item at the indicated
			*			position and moves it to the indicated
			*			group. If sorting is enabled, then the
			*			item is automatically sorted. If sorting
			*			is not enabled, then the item is added
			*			to the end of the group.
			******************************************************/
			void move(int from, ResourceGroupItem *group);

			/**************************************************//*!
			*	@brief	Removes the item at the indicated
			*			position, and moves it to the indicated
			*			position inside the indicated group.
			******************************************************/
			void move(int from, ResourceGroupItem *group, int to);

			/**************************************************//*!
			*	@brief	Removes the item at the indicated
			*			position, but does not delete it.
			******************************************************/
			void remove(int position, int countOld = 1);

			/**************************************************//*!
			*	@brief	Returns a safe cast to this.
			******************************************************/
			ResourceGroupItem *toGroupItem();

		private:

			/**************************************************//*!
			*	@brief	Contains all of children.
			******************************************************/
			QList<ResourceBaseItem*> _children;

			/**************************************************//*!
			*	@brief	Recursively sets the model and project
			*			on the indicated item. If the item is a
			*			group item, all its children and their
			*			children are set too.
			******************************************************/
			void setData(ResourceBaseItem *item, ResourceItemModel *model,
						  ResourceProjectItem *project) const;
		};
	}
}

#endif // NGM__RESOURCEGROUPITEM__HPP
