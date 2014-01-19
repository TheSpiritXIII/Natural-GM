/**
 *  @file ProjectFilterProxyModel.hpp
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
#include "ProjectFilterProxyModel.hpp"
#include "ProjectSetItemModel.hpp"

namespace NGM
{
	Model::ProjectFilterProxyModel::ProjectFilterProxyModel(QObject *parent) :
		SortGroupProxyModel(parent) {}

	bool Model::ProjectFilterProxyModel::filterAcceptsRow(int row,
		const QModelIndex &parent) const
	{
		bool hasSearch = false;
		const Model::ProjectSetItemModel *model = getProjectSetModelSource();
		if (!parent.isValid())
		{
			hasSearch = model->hasSearch(row);
		}
		else
		{
			hasSearch = model->getItem(parent)->child(row)->hasSearch();
		}
		if (SortGroupProxyModel::filterAcceptsRow(row, parent) && hasSearch)
		{
			return true;
		}
		return false;
	}

	bool Model::ProjectFilterProxyModel::lessThan(const QModelIndex &left,
		const QModelIndex &right) const
	{
		const Model::ProjectSetItemModel *model = getProjectSetModelSource();
		if (model->isAllItem(left))
		{
			return sortOrder() == Qt::AscendingOrder;
		}
		if (model->isAllItem(right))
		{
			return sortOrder() != Qt::AscendingOrder;
		}
		if (model->isRecentItem(left))
		{
			return sortOrder() == Qt::AscendingOrder;
		}
		if (model->isRecentItem(right))
		{
			return sortOrder() != Qt::AscendingOrder;
		}
		return QSortFilterProxyModel::lessThan(left, right);
	}
}
