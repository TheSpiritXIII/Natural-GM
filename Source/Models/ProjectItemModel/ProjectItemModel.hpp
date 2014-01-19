/**
 *  @file ProjectItemModel.hpp
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
#ifndef NGM__PROJECTITEMMODEL__HPP
#define NGM__PROJECTITEMMODEL__HPP
#include <QAbstractListModel>
#include <QVector>

namespace NGM
{
	namespace Resource
	{
		class Project;
	}
	namespace Model
	{
		/**************************************************//*!
		*	@brief	A model that displays projects.
		******************************************************/
		class ProjectItemModel : public QAbstractListModel
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Sets a parent object.
			******************************************************/
			ProjectItemModel(QObject *parent = 0);

			/**************************************************//*!
			*	@brief	Returns the item index at the indicated
			*			row and parent.
			******************************************************/
			QModelIndex index(int row, int column = 0,
							  const QModelIndex & parent = QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Returns the number of projects.
			******************************************************/
			int rowCount(const QModelIndex &) const;

			/**************************************************//*!
			*	@brief	Returns the role data at the indicated
			*			index. The icon and text of the project
			*			are displayed.
			******************************************************/
			QVariant data(const QModelIndex &index, int role) const;

			/**************************************************//*!
			*	@brief	Removes all projects from this model.
			******************************************************/
			void clearAll();

			/**************************************************//*!
			*	@brief	Adds the indicated projects to this
			*			model.
			******************************************************/
			void appendProjects(QVector<Resource::Project*> projects);

		private:

			/**************************************************//*!
			*	@brief	Contains projects. They should not be
			*			modified.
			******************************************************/
			QVector<Resource::Project*> _projects;
		};
	}
}

#endif // NGM__PROJECTITEMMODEL__HPP
