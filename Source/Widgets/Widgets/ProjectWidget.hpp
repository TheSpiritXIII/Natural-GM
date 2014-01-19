/**
 *  @file ProjectWidget.hpp
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
#ifndef NGM__PROJECTWIDGET__HPP
#define NGM__PROJECTWIDGET__HPP
#include "ProjectSetItemModel.hpp"
#include <QWidget>
#include <QSet>

class QListView;
class QTreeView;
class QLineEdit;
class QSortFilterProxyModel;

namespace NGM
{
	namespace Manager
	{
		class AppManager;
	}
	namespace Model
	{
		class ProjectFilterProxyModel;
	}
	namespace Widget
	{
		/**************************************************//*!
		*	@brief	Displays all project and file types in
		*			two item views, a tree view displaying
		*			categories and an item view displaying
		*			the projects of the selected category.
		*
		* Stylesheets are supported in this class via ids.
		* The category tree view is named
		* "ProjectCategoryView", the item view is named
		* "ProjectTypeView" and the filter line edit is
		* named "ProjectCategoryFilter".
		******************************************************/
		class ProjectWidget : public QWidget
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates a project display widget.
			*	@param	categoryList A list of premitted
			*			categories. An empty list means all types
			*			of categories are permitted.
			******************************************************/
			ProjectWidget(const Manager::AppManager *manager,
				QWidget *parent = 0, const QStringList categoryList =
					QStringList());

			/**************************************************//*!
			*	@brief	Returns the current selected project.
			******************************************************/
			const Resource::Project *currentProject() const;

		signals:

			/**************************************************//*!
			*	@brief	Emited when a user changes the current
			*			selected type. It is also changed when
			*			a different type is clicked or a new
			*			category is selected.
			******************************************************/
			void projectChanged(const Resource::Project *type);

		public slots:

			/**************************************************//*!
			*	@brief	Searches for items. If the search text is
			*			an empty string, all items are displayed.
			*			This changes the category list.
			******************************************************/
			void setSearch(const QString &search);

			/**************************************************//*!
			*	@brief	Sets the current project display type.
			******************************************************/
			void setDisplay(Model::Display display);

			/**************************************************//*!
			*	@brief	Sets whether or not icon mode is on.
			******************************************************/
			void setIconMode(bool iconMode);

			/**************************************************//*!
			*	@brief	Sets the order of the projects to
			*			descending if true, or ascendng if false.
			******************************************************/
			void setDescending(bool set);

		private slots:

			/**************************************************//*!
			*	@brief	Refreshes the project view.
			******************************************************/
			void categoryClicked(const QModelIndex &index, const QModelIndex&);

			/**************************************************//*!
			*	@brief	Emits a projectChanged signal.
			******************************************************/
			void projectClicked(const QModelIndex &index, const QModelIndex&);

		private:

			/**************************************************//*!
			*	@brief	Displays categories. By default, this has
			*			a header.
			******************************************************/
			QTreeView *_categoryView;

			/**************************************************//*!
			*	@brief	Displays items that match the current
			*			category.
			******************************************************/
			QListView *_projectView;

			/**************************************************//*!
			*	@brief	Stored in _projectFilter.
			******************************************************/
			Model::ProjectItemModel *_projectModel;

			/**************************************************//*!
			*	@brief	Stored in _projectView.
			******************************************************/
			QSortFilterProxyModel *_projectFilter;

			/**************************************************//*!
			*	@brief	Stored in _projectFilter.
			******************************************************/
			Model::ProjectSetItemModel *_projectSetModel;

			/**************************************************//*!
			*	@brief	Stored in _categoryView.
			******************************************************/
			Model::ProjectFilterProxyModel *_projectSetFilter;
		};
	}
}

#endif // NGM__PROJECTWIDGET__HPP
