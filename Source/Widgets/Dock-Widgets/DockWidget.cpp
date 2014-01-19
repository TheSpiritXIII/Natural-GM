/**
 *  @file DockWidget.cpp
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
#include "DockWidget.hpp"
#include <QVariant>
#include <QEvent>
#include <QStyle>
#include <QQueue>

namespace NGM
{
	namespace Widget
	{
		DockWidget::DockWidget(QWidget *parent, Qt::WindowFlags flags) :
			QDockWidget(parent, flags)
		{
			setProperty("focused", false);
			setFocusPolicy(Qt::StrongFocus);
		}

		DockWidget::DockWidget(const QString &title, QWidget *parent,
			Qt::WindowFlags flags) : QDockWidget(title, parent, flags)
		{
			setProperty("focused", false);
			setFocusPolicy(Qt::StrongFocus);
		}

		void DockWidget::focusInEvent(QFocusEvent *)
		{
			setProperty("focused", true);
			style()->unpolish(this);
			style()->polish(this);
		}

		void DockWidget::focusOutEvent(QFocusEvent *)
		{
			setProperty("focused", false);
			style()->unpolish(this);
			style()->polish(this);
		}

		bool DockWidget::eventFilter(QObject *, QEvent *event)
		{
			if (event->type() == QEvent::FocusIn)
			{
				setProperty("focused", true);
				style()->unpolish(this);
				style()->polish(this);
			}
			else if (event->type() == QEvent::FocusOut)
			{
				setProperty("focused", false);
				style()->unpolish(this);
				style()->polish(this);
			}
			else if (event->type() == QEvent::ChildAdded)
			{
				addChildren(static_cast<QChildEvent*>(event)->child());
			}
			else if (event->type() == QEvent::ChildRemoved)
			{
				removeChildren(static_cast<QChildEvent*>(event)->child());
			}
			return false;
		}

		void DockWidget::childEvent(QChildEvent *event)
		{
			if (event->added())
			{
				addChildren(event->child());
			}
			else if (event->removed())
			{
				removeChildren(event->child());
			}
		}

		void DockWidget::addChildren(QObject *object)
		{
			if (!object->isWidgetType())
			{
				return;
			}
			QQueue<QObject*> install;
			install.push_back(object);
			while (!install.empty())
			{
				object = install.front();
				install.pop_front();
				object->installEventFilter(this);
				for (auto &i : object->children())
				{
					if (i->isWidgetType())
					{
						install.push_back(i);
					}
				}
			}
		}

		void DockWidget::removeChildren(QObject *object)
		{
			if (!object->isWidgetType())
			{
				return;
			}
			QQueue<QObject*> install;
			install.push_back(object);
			while (!install.empty())
			{
				object = install.front();
				install.pop_front();
				object->installEventFilter(this);
				for (auto &i : object->children())
				{
					if (i->isWidgetType())
					{
						install.push_back(i);
					}
				}
			}
		}
	}
}
