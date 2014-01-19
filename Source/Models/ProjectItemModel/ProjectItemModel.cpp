/**
 *  @file ProjectItemModel.cpp
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
#include "ProjectItemModel.hpp"
#include "Project.hpp"
using NGM::Resource::Project;

namespace NGM
{
	Model::ProjectItemModel::ProjectItemModel(QObject *parent) :
		QAbstractListModel(parent) {}

	int Model::ProjectItemModel::rowCount(const QModelIndex &) const
	{
		return _projects.size();
	}

	QModelIndex Model::ProjectItemModel::index(int row, int,
										const QModelIndex &parent) const
	{
		if (!hasIndex(row, 0, parent))
		{
			return QModelIndex();
		}

		if (row < _projects.size())
		{
			return createIndex(row, 0, _projects.at(row));
		}

		return QModelIndex();
	}

	QVariant Model::ProjectItemModel::data(const QModelIndex &index,
										   int role) const
	{
		if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
		{
			return static_cast<Project*>(index.internalPointer())->name;
		}
		if (role == Qt::DecorationRole)
		{
			return static_cast<Project*>(index.internalPointer())->icon;
		}
		return QVariant();
	}

	void Model::ProjectItemModel::clearAll()
	{
		beginResetModel();
		_projects.clear();
		endResetModel();
	}

	void Model::ProjectItemModel::appendProjects
		(QVector<Resource::Project *> projects)
	{
		beginInsertRows(QModelIndex(), _projects.size(),
						_projects.size() + projects.size() - 1);
		_projects += projects;
		endInsertRows();
	}
}
