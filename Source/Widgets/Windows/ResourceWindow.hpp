/**
 *  @file ResourceWindow.hpp
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
#ifndef NGM__RESOURCEWINDOW__HPP
#define NGM__RESOURCEWINDOW__HPP
#include <QMainWindow>

namespace NGM
{
	namespace Manager
	{
		class AppManager;
	}
	namespace Widget
	{
		class HierarchyDockWidget;

		/**************************************************//*!
		*	@brief	The main window that displays resources.
		******************************************************/
		class ResourceWindow : public QMainWindow
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates a window with all dock widgets.
			******************************************************/
			ResourceWindow(Manager::AppManager *manager, QWidget *parent = 0);

			/**************************************************//*!
			*	@brief	Returns the hierarchy dock, which is what
			*			display all projects.
			******************************************************/
			inline HierarchyDockWidget *hierarchyDock() const
			{
				return _hierarchyDock;
			}

		protected:

			/**************************************************//*!
			*	@brief	Tells the application manager to process
			*			key events.
			******************************************************/
			void keyPressEvent(QKeyEvent *);

			/**************************************************//*!
			*	@brief	Sets the application manager's active
			*			window.
			******************************************************/
			void focusInEvent(QFocusEvent *);

		private:

			/**************************************************//*!
			*	@brief	Stores the applicaqtion manager.
			******************************************************/
			Manager::AppManager *_manager;

			/**************************************************//*!
			*	@brief	Stores the hierarchy dock, which displays
			*			a list of resources.
			******************************************************/
			HierarchyDockWidget *_hierarchyDock;
		};
	}
}

#endif // NGM__RESOURCEWINDOW__HPP
