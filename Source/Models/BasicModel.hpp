/**
 *  @file BasicModel.hpp
 *  @brief Declares a basic model class that only stores basic items.
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
#ifndef _NGM_BASICMODEL__HPP
#define _NGM_BASICMODEL__HPP
#include <QAbstractItemModel>
#include <vector>

namespace NGM
{
	namespace Model
	{
		class BasicItem;

		class BasicModel : public QAbstractItemModel
		{
			Q_OBJECT

		public:

			/*! The constructor is required to set the name of the root object. */
			explicit BasicModel(const QString &data = 0, QObject *parent = 0);

			/*! You must delete the root object (which deletes everything else). */
			virtual ~BasicModel();

			/*! Required to access data. The role is ignored, however. */
			QVariant data(const QModelIndex &index, int role) const;

			/*! Required to edit and other stuff on tree view items. */
			Qt::ItemFlags flags(const QModelIndex &index) const;

			/*! Required to get the name of a section. This is always the same (no sections). */
			QVariant headerData(Qt::Orientation orientation, int role = Qt::DisplayRole) const;

			/*! Required to get the index of an item. Columns are not used. */
			QModelIndex index(int row,int column, const QModelIndex &parent = QModelIndex()) const;

			/*! Required. Get the parent of an item in the tree view. */
			QModelIndex parent(const QModelIndex &index) const;

			/*! Required to view items in the tree view. */
			int rowCount(const QModelIndex &parent = QModelIndex()) const;

			/*! Required to view the main column. The count is always 1. */
			int columnCount(const QModelIndex &parent = QModelIndex()) const;

			/*! A QAbstractItemModel inherited function to support moving items.*/
			bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);

			/*! A QAbstractItemModel inherited function to support removing items. */
			bool removeRows( int row, int count, const QModelIndex & parent = QModelIndex());

			/*! A QAbstractItemModel inherited function to support inserting items. */
			bool insertRows(int row, int count, const QModelIndex &parent);

			/*! Appends an item to the root as a child. This is fast. */
			void append(BasicItem *item);

			/*! Appends multiple children at once to the root. This is fast. */
			void append(std::vector<BasicItem*> &items);

			/*! Removes the indicated number of children from the back of the root. */
			void pop(int count  = 1);

			/*! Removes the children at the indicated rows from the root. */
			void remove(int row, int count = 1);

			/*! Inserts a children at the indicated row of the root. */
			void insert(BasicItem *item, int row);

			/*! Inserts multiple children to the indicated row of the root. */
			void insert(std::vector<BasicItem*> &items, int row);

			/*! Items need to call this before inserting to update the view. */
			void beginInsert(QModelIndex parent, int first, int last);

			/*! Items need to call this after inserting to update the view. */
			void endInsert();

			/*! Items need to call this before removing to update the view. */
			void beginRemove(QModelIndex parent, int first, int last);

			/*! Items need to call this after removing to update the view. */
			void endRemove();


		private:

			/*! The internal root item. */
			BasicItem *_root;

		};
	}
}

#endif // _NGM_BASICMODEL__HPP
