/**
 *  @file HierarchyDockWidget.hpp
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
#ifndef NGM__HIERARCHYDOCKWIDGET__HPP
#define NGM__HIERARCHYDOCKWIDGET__HPP
#include "DockWidget.hpp"
#include "SortRootProxyModel.hpp"

class QLineEdit;
/*
Plugins also need to do (related):
- Close project.
- Open project.
- Rename file/project.
- Add item.
*/

namespace NGM
{
	namespace Manager
	{
		class AppManager;
	}
	namespace Widget
	{
		/**************************************************//*!
		*	@brief	A dock widget that displays resources in
		*			a proxy model. Also includes a filter
		*			edit.
		******************************************************/
		class HierarchyDockWidget : public DockWidget
		{
		public:

			/**************************************************//*!
			*	@brief	Creates a dock widget with a manager, a
			*			title, a parent and flags.
			******************************************************/
			HierarchyDockWidget(Manager::AppManager *manager, const
				QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);

			/**************************************************//*!
			*	@brief	Expands the indicated root row and all of
			*			its children.
			******************************************************/
			void expandRoot(const int &row);

			/**************************************************//*!
			*	@brief	Collapses the indicated root row and all
			*			of its children.
			******************************************************/
			void collapseRoot(const int &row);

			/**************************************************//*!
			*	@brief	Expands the indicated root row.
			******************************************************/
			inline void expandRow(const int &row)
			{
				model->sourceView()->expand(model->index(row, 0));
			}

			/**************************************************//*!
			*	@brief	Collapses the indicated root row.
			******************************************************/
			inline void collapseRow(const int &row)
			{
				model->sourceView()->collapse(model->index(row, 0));
			}

		private:

			/**************************************************//*!
			*	@brief	Stores the search index.
			******************************************************/
			QLineEdit *_filterEdit;

			/**************************************************//*!
			*	@brief	Stores the display model->
			******************************************************/
			Model::SortRootProxyModel *model;
		};
	}
}

#endif // NGM__HIERARCHYDOCKWIDGET__HPP
