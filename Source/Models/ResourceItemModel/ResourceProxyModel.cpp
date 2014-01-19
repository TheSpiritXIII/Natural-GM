/**
 *  @file ResourceProxyModel.cpp
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
#include "ResourceProxyModel.hpp"
#include "ResourceGroupItem.hpp"
#include "ActionManager.hpp"
#include <QFont>

namespace NGM
{
	namespace Model
	{
		ResourceProxyModel::ResourceProxyModel(QTreeView *treeView) : _treeView(treeView) {}

		QModelIndex ResourceProxyModel::mapFromSource(const QModelIndex & sourceIndex) const
		{
			return sourceIndex;
		}

		QModelIndex ResourceProxyModel::mapToSource(const QModelIndex &proxyIndex) const
		{
			return proxyIndex;
		}

		QVariant ResourceProxyModel::data(const QModelIndex & proxyIndex, int role) const
		{
			if (role == Qt::DisplayRole && static_cast<ResourceGroupItem*>(
					proxyIndex.internalPointer()) != nullptr)
			{
				if (_treeView->isExpanded(proxyIndex))
				{
					return QIcon();
				}
				else
				{
					//return (actionManager->icons[Manager::ActionManager::IconFolder]);
				}
			}
			if (role == Qt::FontRole && proxyIndex.internalPointer() == _activeProjectItem)
			{
				QFont font;
				font.setBold(true);
				return font;
			}
			return sourceModel()->data(proxyIndex, role);
		}
	}
}
