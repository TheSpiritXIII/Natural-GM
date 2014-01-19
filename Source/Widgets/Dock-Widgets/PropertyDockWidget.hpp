/**
 *  @file PropertyDockWidget.hpp
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
#ifndef NGM__PROPERTYDOCKWIDGET__HPP
#define NGM__PROPERTYDOCKWIDGET__HPP
#include "DockWidget.hpp"

namespace NGM
{
	namespace Resource
	{
		class SerialData;
	}
	namespace Manager
	{
		class AppManager;
	}
	namespace Widget
	{
		/**************************************************//*!
		*	@brief	A dock widget with executable commands
		*			and settable properties.
		******************************************************/
		class PropertyDockWidget : public DockWidget
		{
			Q_OBJECT

		public:

			PropertyDockWidget(Manager::AppManager *manager, QWidget *parent = 0,
				Qt::WindowFlags flags = 0) : DockWidget(parent, flags), manager(manager) {}

			PropertyDockWidget(Manager::AppManager *manager, const QString &title,
				QWidget *parent = 0, Qt::WindowFlags flags = 0) :
				DockWidget(title, parent, flags), manager(manager) {}

			/**************************************************//*!
			*	@brief	Executes a command that is unique to
			*			every dock widget with a parameter. It
			*			may or may not return anything.
			******************************************************/
			virtual Resource::SerialData *executeCommand(uint8_t command,
				Resource::SerialData *data = nullptr) = 0;

			/**************************************************//*!
			*	@brief	Sets the indicated property. Properties
			*			names are unique to each dock widget.
			******************************************************/
			virtual void setProperty(const QString &name,
				Resource::SerialData *data = nullptr)
			{
				Q_UNUSED(name);
				Q_UNUSED(data);
			}

			/**************************************************//*!
			*	@brief	Returns the property value of the
			*			indicated name.
			******************************************************/
			virtual Resource::SerialData *property(const QString &name)
			{
				Q_UNUSED(name);
				return nullptr;
			}

		protected:

			/**************************************************//*!
			*	@brief	Stores the global manager. Docks are
			*			allowed to do whatever they want.
			******************************************************/
			Manager::AppManager *manager;

		};
	}
}

#endif // NGM__PROPERTYDOCKWIDGET__HPP
