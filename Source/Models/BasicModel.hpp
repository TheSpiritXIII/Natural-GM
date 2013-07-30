/**
 *  @file BasicModel.hpp
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
#include "BasicItem.hpp"

namespace NGM
{
	namespace Model
	{
		class BasicModel : public QAbstractItemModel
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			 *	@brief Initializers the model with a root item.
			******************************************************/
			explicit BasicModel(const QString &data = 0, QObject *parent = 0);

			/**************************************************//*!
			 *	@brief Destroys the root item and its children.
			******************************************************/
			virtual ~BasicModel();

			/**************************************************//*!
			 *	@return The item data. (Required)
			******************************************************/
			virtual QVariant data(const QModelIndex &index, int role) const;

			/**************************************************//*!
			 *	@return The item flags. (Required)
			******************************************************/
			virtual Qt::ItemFlags flags(const QModelIndex &index) const;

			/**************************************************//*!
			 *	@return The header data. (Required)
			******************************************************/
			virtual QVariant headerData(Qt::Orientation orientation, int role = Qt::DisplayRole) const;

			/**************************************************//*!
			 *	@return The item index of the indicated row and
			 *		column. (Required)
			******************************************************/
			virtual QModelIndex index(int row,int column, const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			 *	@return The parent of the indicated index. (Required)
			******************************************************/
			virtual QModelIndex parent(const QModelIndex &index) const;

			/**************************************************//*!
			 *	@return The row count of the indicated index.
			******************************************************/
			virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			 *	@return Always 1. (Required)
			******************************************************/
			virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			 *	@brief Moves the indicated rows.
			******************************************************/
			virtual bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);

			/**************************************************//*!
			 *	@brief Removes the indicated rows.
			******************************************************/
			virtual bool removeRows( int row, int count, const QModelIndex & parent = QModelIndex());

			/**************************************************//*!
			 *	@brief Inserts into the indicated rows.
			******************************************************/
			virtual bool insertRows(int row, int count, const QModelIndex &parent);

			/**************************************************//*!
			 *	@brief Appends an item into the root.
			******************************************************/
			virtual void append(BasicItem *item);

			/**************************************************//*!
			 *	@brief Appends multiple items into the root.
			******************************************************/
			virtual void append(std::vector<BasicItem*> &items);

			/**************************************************//*!
			 *	@brief Removes the indicated count of items from
			 *		the back of the root.
			******************************************************/
			virtual void pop(int count  = 1);

			/**************************************************//*!
			 *	@brief Removes the indicated rows from the root.
			******************************************************/
			virtual void remove(int row, int count = 1);

			/**************************************************//*!
			 *	@brief Inserts an item into the indicated row.
			******************************************************/
			virtual void insert(BasicItem *item, int row);

			/**************************************************//*!
			 *	@brief Inserts multiple items into the indicated row.
			******************************************************/
			virtual void insert(std::vector<BasicItem*> &items, int row);

			/**************************************************//*!
			 *	@brief Updates the view. Items must use this when inserting.
			******************************************************/
			void beginInsert(QModelIndex parent, int first, int last);

			/**************************************************//*!
			 *	@brief Updates the view. Items must use this when inserting.
			******************************************************/
			void endInsert();

			/**************************************************//*!
			 *	@brief Updates the view. Items must use this when removing.
			******************************************************/
			void beginRemove(QModelIndex parent, int first, int last);

			/**************************************************//*!
			 *	@brief Updates the view. Items must use this when removing.
			******************************************************/
			void endRemove();

		private:

			/**************************************************//*!
			 *	@brief The internal root item.
			******************************************************/
			BasicItem *_root;

		};
	}
}

#endif // _NGM_BASICMODEL__HPP
