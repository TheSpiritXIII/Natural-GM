/**
 *  @file ResourceWindow.cpp
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
#include "ResourceWindow.hpp"
#include "HierarchyDockWidget.hpp"
#include "AppManager.hpp"
#include <QFocusEvent>

#include "ProjectWidget.hpp"

#include <QDebug>

namespace NGM
{
	namespace Widget
	{
		ResourceWindow::ResourceWindow(Manager::AppManager *manager, QWidget *parent) :
			QMainWindow(parent), _manager(manager)
		{
			setAttribute(Qt::WA_DeleteOnClose);
			_hierarchyDock = new HierarchyDockWidget(manager, "Hierarchy", this);
			addDockWidget(Qt::LeftDockWidgetArea, _hierarchyDock);

			setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
			setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
			setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
			setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

			setCentralWidget(new Widget::ProjectWidget(manager, this));

			setMinimumSize(640, 480);

			setFocusPolicy(Qt::StrongFocus);
		}

		void ResourceWindow::keyPressEvent(QKeyEvent *event)
		{
			_manager->processKeyPress(event);
		}

		void ResourceWindow::focusInEvent(QFocusEvent *event)
		{
			_manager->activeResourceWindow = this;
			event->accept();
		}
	}
}
