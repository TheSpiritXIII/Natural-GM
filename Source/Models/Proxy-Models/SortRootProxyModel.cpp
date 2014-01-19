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

namespace NGM
{
	namespace Model
	{
		SortRootProxyModel::SortRootProxyModel(QObject *parent) :
			SortGroupProxyModel(parent), _sourceView(nullptr), _priority(0) {}

		void SortRootProxyModel::setSourceModel(QAbstractItemModel *source)
		{
			if (sourceModel())
			{
				disconnect(sourceModel(), &QAbstractItemModel::rowsRemoved,
						   this, &SortRootProxyModel::updatePriority);
			}
			QAbstractProxyModel::setSourceModel(source);
			connect(source, &QAbstractItemModel::rowsRemoved,
					this, &SortRootProxyModel::updatePriority);
		}

		QVariant SortRootProxyModel::data(const QModelIndex &index, int role) const
		{
			if (role == Qt::FontRole && !index.parent().isValid() && index.row() == _priority)
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

		void SortRootProxyModel::setSourceView(QTreeView *sourceView)
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

		QTreeView *SortRootProxyModel::sourceView() const
		{
			return _sourceView;
		}

		bool SortRootProxyModel::filterAcceptsRow(int row, const QModelIndex &parent) const
		{
			if (!parent.isValid())
			{
				return true;
			}
			return SortGroupProxyModel::filterAcceptsRow(row, parent);
		}

		void SortRootProxyModel::updatePriority(const QModelIndex &, int, int)
		{
			while (_priority < sourceModel()->rowCount())
			{
				--_priority;
			}
		}
	}
}
