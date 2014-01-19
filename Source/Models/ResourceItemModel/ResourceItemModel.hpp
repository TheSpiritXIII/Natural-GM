/**
 *  @file ResourceItemModel.hpp
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
#ifndef NGM__RESOURCEITEMMODEL__HPP
#define NGM__RESOURCEITEMMODEL__HPP
#include <QAbstractItemModel>
#include <vector>

namespace NGM
{
	namespace Manager
	{
		class ActionManager;
	}
	namespace Model
	{
		class ResourceGroupItem;
		class ResourceProjectItem;

		/**************************************************//*!
		*	@brief	A Qt based model that stores resources.
		******************************************************/
		class ResourceItemModel : public QAbstractItemModel
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Initializers the model with a root item.
			******************************************************/
			ResourceItemModel(const Manager::ActionManager *actionManager, QObject *parent = 0);

			/**************************************************//*!
			*	@brief	Destroys the root item and its children.
			******************************************************/
			~ResourceItemModel();

			/**************************************************//*!
			*	@return	The item data. (Required)
			******************************************************/
			QVariant data(const QModelIndex &index, int role) const;

			/**************************************************//*!
			*	@return	The item flags. (Required)
			******************************************************/
			Qt::ItemFlags flags(const QModelIndex &index) const;

			/**************************************************//*!
			*	@return	The header data. Always empty. (Required)
			******************************************************/
			QVariant headerData(Qt::Orientation, int = Qt::DisplayRole) const;

			/**************************************************//*!
			*	@return	The item index of the indicated row and
			*			column. (Required)
			******************************************************/
			QModelIndex index(int row,int column, const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			*	@return	The parent of the indicated index. (Required)
			******************************************************/
			QModelIndex parent(const QModelIndex &index) const;

			/**************************************************//*!
			*	@return	The row count of the indicated index.
			******************************************************/
			int rowCount(const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			*	@return	Always 1. (Required)
			******************************************************/
			int columnCount(const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Moves the indicated rows.
			******************************************************/
			bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);

			/**************************************************//*!
			*	@brief	Removes the indicated rows.
			******************************************************/
			bool removeRows( int row, int count, const QModelIndex & parent = QModelIndex());

			/**************************************************//*!
			*	@brief	Inserts into the indicated rows.
			******************************************************/
			bool insertRows(int row, int count, const QModelIndex &parent);

			/**************************************************//*!
			*	@brief	Appends an item into the root.
			******************************************************/
			void append(ResourceProjectItem *item);

			/**************************************************//*!
			*	@brief	Appends multiple items into the root.
			******************************************************/
			void append(std::vector<ResourceProjectItem*> &items);

			/**************************************************//*!
			*	@brief	Removes the indicated count of items from
			*			back of the root.
			******************************************************/
			void pop(int count  = 1);

			/**************************************************//*!
			*	@brief	Removes the indicated rows from the root.
			******************************************************/
			void remove(int row, int count = 1);

			/**************************************************//*!
			*	@brief	Inserts an item into the indicated row.
			******************************************************/
			void insert(ResourceProjectItem *item, int row);

			/**************************************************//*!
			*	@brief	Inserts multiple items into the indicated row.
			******************************************************/
			void insert(std::vector<ResourceProjectItem*> &items, int row);

			/**************************************************//*!
			*	@brief	Updates the view. Items must use this when inserting.
			******************************************************/
			void beginInsert(QModelIndex parent, int first, int last);

			/**************************************************//*!
			*	@brief	Updates the view. Items must use this when inserting.
			******************************************************/
			void endInsert();

			/**************************************************//*!
			*	@brief	Updates the view. Items must use this when removing.
			******************************************************/
			void beginRemove(QModelIndex parent, int first, int last);

			/**************************************************//*!
			*	@brief	Updates the view. Items must use this when removing.
			******************************************************/
			void endRemove();

		private:

			/**************************************************//*!
			*	@brief	The internal root item.
			******************************************************/
			NGM::Model::ResourceGroupItem *_root;

			/**************************************************//*!
			*	@brief	Manages generic icons.
			******************************************************/
			const Manager::ActionManager *actionManager;

		};
	}
}


#endif // NGM__RESOURCEITEMMODEL__HPP
