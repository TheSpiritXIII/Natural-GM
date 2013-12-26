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
#include <QDockWidget>

namespace NGM
{
	namespace Resource
	{
		class SerialData;
	}
	namespace Widget
	{
		/**************************************************//*!
		*	@brief	A dock widget with executable commands
		*			and settable properties.
		******************************************************/
		class PropertyDockWidget : public QDockWidget
		{
			/**************************************************//*!
			*	@brief	Executes a command that is unique to
			*			every dock widget with a parameter. It
			*			may or may not return anything.
			******************************************************/
			virtual Resource::SerialData *executeCommand(uint8_t command,
				Resource::SerialData *data = nullptr) = 0;

			/**************************************************//*!
			*	@brief	Sets the indicated property. Properties
			*			are unique to each dock widget.
			******************************************************/
			virtual void setProperty(const QString &name,
				Resource::SerialData *data = nullptr) = 0;

			/**************************************************//*!
			*	@brief	Returns the property value of the
			*			indicated name.
			******************************************************/
			virtual const Resource::SerialData *property(const QString &name) = 0;

		};
	}
}

#endif // NGM__PROPERTYDOCKWIDGET__HPP
