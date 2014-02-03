/**
 *  @file SortRootProxyModel.cpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#include "SortRootProxyModel.hpp"
#ifdef QT_DEBUG
#include <QDebug>
#endif

NGM::Model::SortRootProxyModel::SortRootProxyModel(QObject *parent) :
	SortGroupProxyModel(parent), _sourceView(nullptr), _priority(0) {}

void NGM::Model::SortRootProxyModel::setSourceModel(QAbstractItemModel *source)
{
	if (sourceModel())
	{
		disconnect(source, &QAbstractItemModel::rowsAboutToBeMoved,
				   this, &SortRootProxyModel::priorityRowMoved);
		disconnect(sourceModel(), &QAbstractItemModel::rowsRemoved,
				   this, &SortRootProxyModel::priorityRowRemoved);
	}
	QSortFilterProxyModel::setSourceModel(source);
	connect(source, &QAbstractItemModel::rowsAboutToBeMoved,
			this, &SortRootProxyModel::priorityRowMoved);
	connect(source, &QAbstractItemModel::rowsAboutToBeRemoved,
			this, &SortRootProxyModel::priorityRowRemoved);
}

QVariant NGM::Model::SortRootProxyModel::data(const QModelIndex &index,
											  int role) const
{
	if (role == Qt::FontRole && !index.parent().isValid() &&
			mapToSource(index).row() == _priority)
	{
		QFont font;
		font.setBold(true);
		return font;
	}
	if (role == Qt::DecorationRole && _sourceView->isExpanded(index))
	{
		return QSortFilterProxyModel::data(index, DecorationExpandRole);
	}
	return QSortFilterProxyModel::data(index, role);
}

void NGM::Model::SortRootProxyModel::setSourceView(QTreeView *sourceView)
{
	if (sourceView->model() == this)
	{
		_sourceView = sourceView;
	}
#ifdef QT_DEBUG
	else
	{
		qWarning() << "Natural::SortFolderProxyModel: Invalid view.";
	}
#endif
}

void NGM::Model::SortRootProxyModel::setPriority(int index)
{
	_priority = index;
	if (index > rowCount()  || index < 0)
	{
		_priority = 0;
	}
}

bool NGM::Model::SortRootProxyModel::filterAcceptsRow(int row,
	const QModelIndex &parent) const
{
	return SortGroupProxyModel::filterAcceptsRow(row, parent);
}

void NGM::Model::SortRootProxyModel::priorityRowRemoved(
	const QModelIndex &parent, int start, int end)
{
	if (parent == QModelIndex())
	{
		if (_priority >= start)
		{
			if (_priority < end)
			{
				_priority = start - 1;
			}
			else
			{
				--_priority;
			}
		}
	}
}

void NGM::Model::SortRootProxyModel::priorityRowMoved(const QModelIndex &parent,
	int start, int end, const QModelIndex &, int row)
{
	if (parent == QModelIndex())
	{
		if (start >= _priority && end <= _priority)
		{
			_priority = end - _priority + (row > _priority ? --row : row);
		}
		else if (_priority >= row && _priority < start)
		{
			_priority += (end - start) + 1;
		}
		else if (_priority > start && _priority < row)
		{
			_priority -= (end - start) + 1;
		}
	}
}
