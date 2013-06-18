/**
 *  @file BasicModel.cpp
 *  @brief Defines a basic model class that only stores basic items.
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
#include "BasicModel.hpp"
#include "BasicItem.hpp"

namespace NGM
{
	namespace Model
	{
		BasicModel::BasicModel(const QString &data, QObject *parent) :
			QAbstractItemModel(parent) {_root = new BasicItem(data); _root->_model = this; _root->_parent = NULL;}

		BasicModel::~BasicModel()
		{
			delete _root;
		}

		int BasicModel::columnCount(const QModelIndex &parent) const
		{
			Q_UNUSED(parent)
			return 1;
		}

		QVariant BasicModel::data(const QModelIndex &index, int role) const
		{
			if (!index.isValid())
			{
				return QVariant();
			}

			if (role == Qt::DisplayRole)
			{
				return static_cast<BasicItem*>(index.internalPointer())->data();
			}

			return QVariant();
		}

		Qt::ItemFlags BasicModel::flags(const QModelIndex &index) const
		{
			if (index.isValid())
			{
				return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
			}
			return Qt::ItemIsEnabled;
		}

		QVariant BasicModel::headerData(Qt::Orientation orientation, int role) const
		{
			if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			{
				return _root->data();
			}

			return QVariant();
		}

		QModelIndex BasicModel::index(int row, int column, const QModelIndex &parent) const
		{
			Q_UNUSED(column)
			if (!hasIndex(row, 0, parent))
			{
				return QModelIndex();
			}

			BasicItem *_parent;

			if (!parent.isValid())
			{
				_parent = _root;
			}
			else
			{
				_parent = static_cast<BasicItem*>(parent.internalPointer());
			}

			BasicItem *_child = _parent->child(row);
			if (_child)
			{
				return createIndex(row, 0, _child);
			}
			return QModelIndex();
		}

		QModelIndex BasicModel::parent(const QModelIndex &index) const
		{
			if (!index.isValid())
			{
				return QModelIndex();
			}

			BasicItem *_child = static_cast<BasicItem*>(index.internalPointer());
			BasicItem *_parent = _child->parent();

			if (_parent == _root)
			{
				return QModelIndex();
			}

			return createIndex(_parent->row(), 0, _parent);
		}

		int BasicModel::rowCount(const QModelIndex &parent) const
		{
			BasicItem *_parent;

			if (!parent.isValid())
			{
				_parent = _root;
			}
			else
			{
				_parent = static_cast<BasicItem*>(parent.internalPointer());
			}

			return _parent->count();
		}

		bool BasicModel::removeRows(int row, int count, const QModelIndex &parent)
		{
			if (count < 1 || row < 0 || (row + count) > rowCount(parent))
			{
				return false;
			}
			beginRemoveRows(parent, row, row+count-1);
			BasicItem* item = static_cast<BasicItem*>(parent.internalPointer());
			item->remove(row, count);
			endRemoveRows();
			return true;
		}

		bool BasicModel::insertRows(int row, int count, const QModelIndex &parent)
		{
			if (count < 1 || row < 0 || row > rowCount(parent))
			{
				return false;
			}
			beginInsertRows(parent, row, row+count-1);
			BasicItem* item = static_cast<BasicItem*>(parent.internalPointer());
			std::vector<BasicItem*> insert;
			for(int i = 0; i < count; ++i)
			{
				insert.push_back(new BasicItem(""));
			}
			item->insert(insert, row);
			endInsertRows();
			return true;
		}

		bool BasicModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
		{

			if (count < 1 || sourceRow < 0 || (sourceRow + count) > rowCount(sourceParent) ||
				destinationChild < 0 || destinationChild > rowCount(destinationParent))
			{
				return false;
			}
			beginMoveRows(sourceParent, sourceRow, sourceRow+count-1, destinationParent, destinationChild);
			BasicItem* source = static_cast<BasicItem*>(sourceParent.internalPointer());
			BasicItem* destination = static_cast<BasicItem*>(destinationParent.internalPointer());
			destination->insert(source->take(sourceRow, count), destinationChild);
			endMoveRows();
			return true;
		}

		void BasicModel::append(BasicItem *item)
		{
			_root->append(item);
		}

		void BasicModel::append(std::vector<BasicItem*> &items)
		{
			_root->append(items);
		}

		void BasicModel::pop(int count)
		{
			_root->pop(count);
		}

		void BasicModel::insert(BasicItem *item, int row)
		{
			_root->insert(item, row);
		}

		void BasicModel::beginInsert(QModelIndex parent, int first, int last)
		{
			beginInsertRows(parent, first, last);
		}

		void BasicModel::endInsert()
		{
			endInsertRows();
		}

		void BasicModel::beginRemove(QModelIndex parent, int first, int last)
		{
			beginRemoveRows(parent, first, last);
		}

		void BasicModel::endRemove()
		{
			endRemoveRows();
		}
	}
}
