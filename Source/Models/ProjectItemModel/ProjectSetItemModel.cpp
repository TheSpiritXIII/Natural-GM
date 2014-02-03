/**
 *  @file ProjectSetItemModel.cpp
 *	@section License
 *
 *      Copyright (C) 2014 Daniel Hrabovcak
 *
 *      This file is part of the Natural GM IDE.
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
#include "ProjectSetItemModel.hpp"
#include "ProjectSetModelItem.hpp"
#include "ProjectItemModel.hpp"
#include <QFont>
using NGM::Model::ProjectSetModelItem;

// REMOVE
#include <QDebug>

namespace NGM
{
	Model::ProjectSetItemModel::ProjectSetItemModel(QObject *parent,
		QVector<Resource::Project*> recent) : QAbstractItemModel(parent)
	{
		_root = new ProjectSetModelItem();
		_recent = new ProjectSetModelItem(tr("Recent"), recent);
	}

	Model::ProjectSetItemModel::~ProjectSetItemModel()
	{
		delete _root;
		delete _recent;
	}

	QModelIndex Model::ProjectSetItemModel::index(int row, int,
		const QModelIndex &parent) const
	{
		if (!hasIndex(row, 0, parent))
		{
			return QModelIndex();
		}

		ProjectSetModelItem *item;
		if (parent.isValid())
		{
			item = getItem(parent);
		}
		else
		{
			if (isAllItemRow(row))
			{
				return createIndex(row, 0, nullptr);
			}
			else if (isRecentItemRow(row))
			{
				return createIndex(row, 0, _recent);
			}
			item = _root;
		}

		if (row < item->childCount()) // Checks item exists.
		{
			return createIndex(row, 0, item->child(row));
		}
		return QModelIndex();
	}

	QModelIndex Model::ProjectSetItemModel::parent
		(const QModelIndex &index) const
	{
		if (!index.isValid())
		{
			return QModelIndex();
		}

		ProjectSetModelItem *parent = getItem(index);
		if (parent == nullptr)
		{
			return QModelIndex();
		}
		parent = parent->parent();
		if (parent == _root)
		{
			return QModelIndex();
		}
		return createIndex(parent->childNumber(), 0, parent);
	}

	int Model::ProjectSetItemModel::rowCount(const QModelIndex &parent) const
	{
		if (parent.isValid())
		{
			if (!parent.parent().isValid() &&
			   (isAllItemRow(parent.row()) || isRecentItemRow(parent.row())))
			{
				return 0;
			}
			return getItem(parent)->childCount();
		}
		return _root->childCount() + (_recent->childCount() == 0 ? 1 : 2);
	}

	int Model::ProjectSetItemModel::columnCount(const QModelIndex &) const
	{
		return 1;
	}

	QVariant Model::ProjectSetItemModel::data(const QModelIndex &index, int role) const
	{
		if (!index.isValid())
		{
			return QVariant();
		}
		if (role == Qt::DisplayRole)
		{
			if (index.parent() == QModelIndex())
			{
				if (isAllItemRow(index.row()))
				{
					return tr("All");
				}
				if (isRecentItemRow(index.row()))
				{
					return _recent->text();
				}
			}
			return getItem(index)->text();
		}
		if (role == Qt::FontRole && index.parent() == QModelIndex() &&
		   (isAllItemRow(index.row()) || isRecentItemRow(index.row())))
		{
			QFont font;
			font.setBold(true);
			return font;
		}
		return QVariant();
	}

	QVariant Model::ProjectSetItemModel::headerData(int, Qt::Orientation,
													int role) const
	{
		if (role == Qt::DisplayRole)
		{
			return tr("Categories");
		}
		return QVariant();
	}

	Qt::ItemFlags Model::ProjectSetItemModel::flags
		(const QModelIndex &index) const
	{
		if (index.isValid())
		{
			return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
		}
		return Qt::ItemIsEnabled;
	}

	bool Model::ProjectSetItemModel::hasChildren(const QModelIndex &parent) const
	{
		if (parent.isValid())
		{
			if (parent.row() == childCount() || isAllItemRow(parent.row()) ||
				isRecentItemRow(parent.row()))
			{
				return false;
			}
			return getItem(parent)->childCount() != 0;
		}
		return _root->childCount() != 0;
	}

	bool Model::ProjectSetItemModel::isRecentItem(const QModelIndex &index) const
	{
		return getItem(index) == _recent;
	}

	bool Model::ProjectSetItemModel::isAllItem(const QModelIndex &index) const
	{
		if (!index.parent().isValid())
		{
			if (isAllItemRow(index.row()))
			{
				return true;
			}
		}
		return false;
	}

	void Model::ProjectSetItemModel::setDisplay(Display display) const
	{
		for (int i = 0; i != _root->childCount(); ++i)
		{
			_root->child(i)->setDisplay(display);
		}
	}

	void Model::ProjectSetItemModel::setSearch(const QString &search)
	{
		for (int i = 0; i != _root->childCount(); ++i)
		{
			_root->child(i)->setSearch(search);
		}
	}

	bool Model::ProjectSetItemModel::hasSearch(int row) const
	{
		if (isAllItemRow(row))
		{
			for (int i = 0; i != _root->childCount(); ++i)
			{
				if (_root->child(i)->hasSearch())
				{
					return true;
				}
			}
			return false;
		}
		if (isRecentItemRow(row))
		{
			return false;
		}
		return _root->child(row)->hasSearch();
	}

	void Model::ProjectSetItemModel::setItemModel(const QModelIndex &index,
												  ProjectItemModel *model) const
	{
		model->clearAll();
		QVector<Resource::Project*> list;
		if (!index.parent().isValid())
		{
			if (isAllItemRow(index.row()))
			{
				for (int i = 0; i != _root->childCount(); ++i)
				{
					if (_root->child(i)->hasSearch())
					{
						_root->child(i)->searchItems(&list);
					}
				}
				model->appendProjects(list);
				return;
			}
			if (isRecentItemRow(index.row()))
			{
				return;
			}
		}
		getItem(index)->searchItems(&list);
		model->appendProjects(list);
	}
}
