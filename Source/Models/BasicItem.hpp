/**
 *  @file BasicItem.hpp
 *  @brief Declares a basic item class, capable of holding a single text.
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
#ifndef _NGM_BASICITEM__HPP
#define _NGM_BASICITEM__HPP
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QString>
#include <vector>

namespace NGM
{
	namespace Model
	{
		class ResourceItem;
		class BasicModel;

		class BasicItem
		{
		public:

			/*! Creates a basic item with the indicated name. */
			BasicItem(const QString &data);

			/*! Removes and deallocates all children. */
			virtual ~BasicItem();

			/*! @return The string name of this item. */
			QVariant data() const;

			/*! @return The model index of the item. */
			const QModelIndex index();

			/*! @return The child at the indicated row. */
			BasicItem *child(int row);

			/*! @return The number of children this item contains. */
			int count() const;

			/*! @return The row this item is inside its parent. */
			int row() const;

			/*! @return The item that holds this as a child, or NULL. */
			BasicItem *parent();

			/*! Appends an item to this item as a child. This is fast. */
			void append(BasicItem *item);

			/*! Appends multiple children at once. This is fast. */
			void append(std::vector<BasicItem*> items);

			/*! Removes the indicated number of children from the back. */
			void pop(int count  = 1);

			/*! Removes the children at the indicated rows. */
			void remove(int row, int count = 1);

			/*! Removes and returns the children at the indicated rows. */
			std::vector<BasicItem*> take(int row, int count = 1);

			/*! Inserts a children at the indicated row. */
			void insert(BasicItem *item, int row);

			/*! Inserts multiple children to the indicated row. */
			void insert(std::vector<BasicItem*> items, int row);

			/*! @return A safe cast to a resource item. */
			virtual ResourceItem *toResourceItem();

		private:

			/*! Stores the parent. This is defined by itself when appended. */
			BasicItem *_parent;

			/*! Stores the model. This is necessary for obtaining the index. */
			BasicModel *_model;

			/*! Stores all of this item's children. */
			std::vector<BasicItem*> _children;

			/*! Stores the string name of this item. */
			QVariant _data;

			friend class NGM::Model::BasicModel;
		};
	}
}

#endif // _NGM_BASICITEM__HPP
