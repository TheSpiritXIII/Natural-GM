/**
 *  @file ResourceItemModel.cpp
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
#include "ResourceItemModel.hpp"
#include "ResourceProjectItem.hpp"
#include "ResourceGroupItem.hpp"
#include "ActionManager.hpp"
#include "Project.hpp"
#include "Type.hpp"
#include <QDebug>

namespace NGM
{
	namespace Model
	{
		ResourceItemModel::ResourceItemModel(const Manager::ActionManager *actionManager,
			QObject *parent) : QAbstractItemModel(parent), actionManager(actionManager)
		{
			_root = new ResourceGroupItem(QString());
			_root->_model = this;
		}

		ResourceItemModel::~ResourceItemModel()
		{
			delete _root;
		}

		int ResourceItemModel::columnCount(const QModelIndex &parent) const
		{
			Q_UNUSED(parent)
			return 1;
		}

		QVariant ResourceItemModel::data(const QModelIndex &index, int role) const
		{
			if (!index.isValid())
			{
				return QVariant();
			}

			if (role == Qt::DisplayRole)
			{
				return static_cast<ResourceBaseItem*>(index.internalPointer())->text();
			}
			if (role == Qt::DecorationRole)
			{
				qDebug() << "Reload bro.";
				ResourceBaseItem *item = static_cast<ResourceBaseItem*>(index.internalPointer());
				if (item->toProjectItem() != nullptr)
				{
					if (item->toProjectItem()->project->type)
					{
						return item->toProjectItem()->project->type->getIcon(item->toProjectItem()->resource->serialData);
					}
				}
				else if (item->toContentItem() != nullptr)
				{
					if (item->toContentItem()->resource->type)
					{
						qDebug() << item->toContentItem()->resource->icon.isNull();

						//qDebug() << item->toContentItem()->resource->type;
						//return item->toContentItem()->resource->type->getIcon(item->toContentItem()->resource->serialData);
					}
					return item->toContentItem()->resource->icon;
				}
				return (actionManager->icons[Manager::ActionManager::IconFolder]);
			}

			return QVariant();
		}

		Qt::ItemFlags ResourceItemModel::flags(const QModelIndex &index) const
		{
			if (index.isValid())
			{
				return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
			}
			return Qt::ItemIsEnabled;
		}

		QVariant ResourceItemModel::headerData(Qt::Orientation, int) const
		{
			return QVariant();
		}

		QModelIndex ResourceItemModel::index(int row, int column, const QModelIndex &parent) const
		{
			Q_UNUSED(column)
			if (!hasIndex(row, 0, parent))
			{
				return QModelIndex();
			}

			ResourceBaseItem *_parent;

			if (!parent.isValid())
			{
				_parent = _root;
			}
			else
			{
				_parent = static_cast<ResourceBaseItem*>(parent.internalPointer());
			}

			ResourceBaseItem *_child = _parent->toGroupItem()->child(row);
			if (_child)
			{
				return createIndex(row, 0, _child);
			}
			return QModelIndex();
		}

		QModelIndex ResourceItemModel::parent(const QModelIndex &index) const
		{
			if (!index.isValid())
			{
				return QModelIndex();
			}

			ResourceBaseItem *_child = static_cast<ResourceBaseItem*>(index.internalPointer());
			ResourceBaseItem *_parent = _child->parent();

			if (_parent->toGroupItem() == _root)
			{
				return QModelIndex();
			}

			return createIndex(_parent->row(), 0, _parent);
		}

		int ResourceItemModel::rowCount(const QModelIndex &parent) const
		{
			ResourceBaseItem *_parent;
			if (!parent.isValid())
			{
				_parent = _root;
			}
			else
			{
				_parent = static_cast<ResourceBaseItem*>(parent.internalPointer());
			}

			if (_parent->toGroupItem() == nullptr)
			{
				return 0;
			}
			return _parent->toGroupItem()->count();
		}

		bool ResourceItemModel::removeRows(int row, int count, const QModelIndex &parent)
		{
			if (count < 1 || row < 0 || (row + count) > rowCount(parent))
			{
				return false;
			}
			beginRemoveRows(parent, row, row+count-1);
			ResourceGroupItem* item = static_cast<ResourceGroupItem*>(parent.internalPointer());
			item->remove(row, count);
			endRemoveRows();
			return true;
		}

		bool ResourceItemModel::insertRows(int row, int count, const QModelIndex &parent)
		{
			if (count < 1 || row < 0 || row > rowCount(parent))
			{
				return false;
			}
			beginInsertRows(parent, row, row+count-1);
			ResourceGroupItem* item = static_cast<ResourceGroupItem*>(parent.internalPointer());
			std::vector<ResourceBaseItem*> insert;
			for(int i = 0; i < count; ++i)
			{
				insert.push_back(new ResourceBaseItem(""));
			}
			item->insert(insert, row);
			endInsertRows();
			return true;
		}

		bool ResourceItemModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
		{

			if (count < 1 || sourceRow < 0 || (sourceRow + count) > rowCount(sourceParent) ||
				destinationChild < 0 || destinationChild > rowCount(destinationParent))
			{
				return false;
			}
			beginMoveRows(sourceParent, sourceRow, sourceRow+count-1, destinationParent, destinationChild);
			ResourceGroupItem* source = static_cast<ResourceGroupItem*>(sourceParent.internalPointer());
			ResourceGroupItem* destination = static_cast<ResourceGroupItem*>(destinationParent.internalPointer());
			destination->insert(source->take(sourceRow, count), destinationChild);
			endMoveRows();
			return true;
		}

		void ResourceItemModel::append(ResourceProjectItem *item)
		{
			_root->append(item);
			item->_root = item;
		}

		void ResourceItemModel::pop(int count)
		{
			_root->pop(count);
		}

		void ResourceItemModel::insert(ResourceProjectItem *item, int row)
		{
			_root->insert(item, row);
		}

		void ResourceItemModel::remove(int row, int count)
		{
			_root->remove(row, count);
		}

		void ResourceItemModel::beginInsert(QModelIndex parent, int first, int last)
		{
			beginInsertRows(parent, first, last);
		}

		void ResourceItemModel::endInsert()
		{
			endInsertRows();
		}

		void ResourceItemModel::beginRemove(QModelIndex parent, int first, int last)
		{
			beginRemoveRows(parent, first, last);
		}

		void ResourceItemModel::endRemove()
		{
			endRemoveRows();
		}
	}
}
