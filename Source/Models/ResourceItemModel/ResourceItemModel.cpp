/**
 *  @file ResourceItemModel.cpp
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
#include "ResourceItemModel.hpp"
// #include "ActionManager"
#include <QMimeData>

#include <sstream>

// TODO: Find way to transfer pointers without string stream.
// TODO: Add flag checking.

// REMOVE
#include <QDebug>

// INCOMPLETE
#include "ActionManager.hpp"
#include "Project.hpp"
#include "Type.hpp"

#include "Serializer.hpp"

QMimeData *NGM::Model::ResourceItemModel::internalMime = nullptr;

NGM::Model::ResourceItemModel::ResourceItemModel(
	const Manager::ActionManager *actionManager, QObject *parent,
		QString headerText) : QAbstractItemModel(parent),
	actionManager(actionManager), _sort(false)
{
	_root = new ResourceGroupItem(headerText);
	_root->_model = this;
}

/*NGM::Model::ResourceItemModel::ResourceItemModel(
	const Manager::IconManager *actionManager, QString headerText,
	QObject *parent, ) : QAbstractItemModel(parent),
	iconManager(actionManager), _sort(false)
{
	_root = new ResourceGroupItem(headerText);
	_root->_model = this;
}*/

NGM::Model::ResourceItemModel::~ResourceItemModel()
{
	delete _root;
}

void NGM::Model::ResourceItemModel::setSort(bool yes)
{
	if (yes && _sort != yes)
	{
		_root->sort();
	}
	_sort = yes;
}

QVariant NGM::Model::ResourceItemModel::data(const QModelIndex &index,
											 int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		return static_cast<ResourceBaseItem*>(index.internalPointer())->text();
	}
	if (role == Qt::DecorationRole)
	{
		ResourceBaseItem *item = static_cast<ResourceBaseItem*>(index.internalPointer());
		if (item->toProjectItem() != nullptr)
		{
			if (item->toProjectItem()->project()->type)
			{
				//return item->toProjectItem()->project->type->getIcon(item->toProjectItem()->resource->serialData);
			}
		}
		else if (item->toContentItem() != nullptr)
		{
			/*if (item->toContentItem()->resource->type)
			{
				qDebug() << item->toContentItem()->resource->icon.isNull();

				//qDebug() << item->toContentItem()->resource->type;
				//return item->toContentItem()->resource->type->getIcon(item->toContentItem()->resource->serialData);
			}
			return item->toContentItem()->resource->icon;*/
		}
		//return (actionManager->icons[Manager::ActionManager::IconFolder]);
	}

	return QVariant();
}

Qt::ItemFlags NGM::Model::ResourceItemModel::flags(
		const QModelIndex &index) const
{
	if (index.isValid())
	{
		ResourceBaseItem *item = static_cast<ResourceBaseItem*>(
					index.internalPointer());
		ResourceContentItem *content = item->toContentItem();
		if (content)
		{
			return Qt::ItemIsEnabled | Qt::ItemIsSelectable |
					Qt::ItemIsDragEnabled;
		}
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable |
			   Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled |
			   Qt::ItemIsEditable;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
}

QVariant NGM::Model::ResourceItemModel::headerData(Qt::Orientation,
												   int role) const
{
	if (role == Qt::DisplayRole)
	{
		return _root->text();
	}
	return QVariant();
}

QModelIndex NGM::Model::ResourceItemModel::index(int row, int,
		const QModelIndex &parent) const
{
	if (!hasIndex(row, 0, parent))
	{
		return QModelIndex();
	}

	ResourceGroupItem *_parent;

	if (!parent.isValid())
	{
		_parent = _root;
	}
	else
	{
		_parent = static_cast<ResourceGroupItem*>(parent.internalPointer());
	}

	ResourceBaseItem *_child = _parent->child(row);
	if (_child)
	{
		return createIndex(row, 0, _child);
	}
	return QModelIndex();
}

QModelIndex NGM::Model::ResourceItemModel::parent(
		const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return QModelIndex();
	}

	ResourceGroupItem *_parent = static_cast<ResourceBaseItem*>
			(index.internalPointer())->parent();

	if (_parent == _root)
	{
		return QModelIndex();
	}

	return createIndex(_parent->childNumber(), 0, _parent);
}

int NGM::Model::ResourceItemModel::rowCount(const QModelIndex &parent) const
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

int NGM::Model::ResourceItemModel::columnCount(const QModelIndex &) const
{
	return 1;
}

Qt::DropActions NGM::Model::ResourceItemModel::supportedDragActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

Qt::DropActions NGM::Model::ResourceItemModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

QStringList NGM::Model::ResourceItemModel::mimeTypes() const
{
	return QStringList("Natural-GM/Model-Drag");
}
QMimeData *NGM::Model::ResourceItemModel::mimeData(
		const QModelIndexList &indexes) const
{
	qDebug() << "Mr. Mime";
	QMimeData *mimeData = new QMimeData();

	std::stringstream ss;
	QByteArray array;
	for (QModelIndexList::const_iterator i = indexes.begin();
		 i != indexes.end(); ++i)
	{
		ss << i->internalPointer() << std::endl;
		qDebug() << i->internalPointer();
	}
	std::string str = ss.str();
	array.append(str.c_str(), str.size());
	mimeData->setData(QStringLiteral("Natural-GM/Model-Drag"), array);
	internalMime = mimeData;
	return mimeData;
}

bool NGM::Model::ResourceItemModel::dropMimeData(const QMimeData *data,
	Qt::DropAction action, int row, int, const QModelIndex &parent)
{
	// TODO: Optimize by decreasing inputs (process groups at once).
	qDebug() << "Drop mime";
	qDebug() << "MIME" << data;
	if (data->hasFormat(QStringLiteral("Natural-GM/Model-Drag")) &&
			internalMime == data)
	{
		ResourceGroupItem *group = static_cast<ResourceGroupItem*>(
					parent.internalPointer());

		std::stringstream ss;
		ss << data->data("Natural-GM/Model-Drag").data();
		void *ptr = 0;
		ResourceBaseItem *item;
		if (row == -1)
		{
			row = 0;
		}
		qDebug() << group;
		while (ss >> ptr)
		{
			item = static_cast<ResourceBaseItem*>(ptr);
			qDebug() << ResourceBaseItem::IsStatic;
			qDebug() << item->text() << item->flags();
			if (item->flags() & ResourceBaseItem::NotMovable)
			{
				continue;
			}
			//qDebug() << "Can contain?" << group->canContain(item);
			if (item->parent() == _root && group == nullptr)
			{
				qDebug() << "Yes hi.";
				if (!_sort)
				{
					int number = item->childNumber();
					if (row == number)
					{
						continue;
					}
					_root->move(number, _root, row);
					++row;
				}
				else if (group != item->parent())
				{
					item->parent()->move(item->childNumber(), group);
				}
			}
			else if (item->parent() != _root && group != nullptr &&
					 item->projectItem() == group->projectItem())
			{
				//qDebug() << "Not contain"
				if (!group->canContain(item))
				{
					continue;
				}
				qDebug() << "Yes casual.";
				qDebug() << item->projectItem();
				qDebug() << group->projectItem();
				if (!_sort)
				{
					int number = item->childNumber();
					if (item->parent() == group && row == number)
					{
						continue;
					}
					item->parent()->move(number, group, row);
					++row;
				}
				else if (group != item->parent())
				{
					item->parent()->move(item->childNumber(), group);
				}
			}
		}
		qDebug() << (action == Qt::MoveAction);
	}
	return false;
}
