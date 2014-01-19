/**
 *  @file DockWidget.hpp
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
#ifndef NGM__DOCKWIDGET__HPP
#define NGM__DOCKWIDGET__HPP
#include <QDockWidget>

namespace NGM
{
	namespace Widget
	{
		/**************************************************//*!
		*	@brief	A Qt based dock widget that sets a
		*			"focused" property as true when focused,
		*			useful for stylesheets.
		*
		*	Changing the focus policy may have unwanted
		*	consequences, as this widget relies on having
		*	focus in the first place.
		******************************************************/
		class DockWidget : public QDockWidget
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Constructs a dock widget with a parent
			*			and flags. The dock widget will be placed
			*			in the left dock widget area.
			******************************************************/
			DockWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);

			/**************************************************//*!
			*	@brief	Constructs a dock widget with parent
			*			parent and window flags flags. The dock
			*			widget will be placed in the left dock
			*			widget area.
			*
			*	The window's caption is set to title. This
			*	caption is used when the QDockWidget is docked
			*	and undocked. It is also used in the context menu
			*	provided by QMainWindow.
			******************************************************/
			DockWidget(const QString &title, QWidget *parent = 0,
						Qt::WindowFlags flags = 0);

		protected:

			/**************************************************//*!
			*	@brief	Sets the "focused" property as true.
			******************************************************/
			virtual void focusInEvent(QFocusEvent *);

			/**************************************************//*!
			*	@brief	Sets the "focused" property as false.
			******************************************************/
			virtual void focusOutEvent(QFocusEvent *);

			/**************************************************//*!
			*	@brief	Checks when children are added or
			*			removed.
			******************************************************/
			virtual void childEvent(QChildEvent *);

			/**************************************************//*!
			*	@brief	Listens to children for focus events.
			*			Always allows events to filter out.
			******************************************************/
			bool eventFilter(QObject *, QEvent *);

			/**************************************************//*!
			*	@brief	Installs an event filter on the indicated
			*			widget and all of its children.
			******************************************************/
			void addChildren(QObject *object);

			/**************************************************//*!
			*	@brief	Removes the event filter on the indicated
			*			object and all of its children.
			******************************************************/
			void removeChildren(QObject *object);

		};
	}
}

#endif // NGM__DOCKWIDGET__HPP
