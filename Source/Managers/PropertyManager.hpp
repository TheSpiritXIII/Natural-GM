/**
 *  @file PropertyManager.hpp
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
#ifndef NGM__PROPERTYMANAGER__HPP
#define NGM__PROPERTYMANAGER__HPP
#include <QString>

namespace NGM
{
	namespace Resource
	{
		class SerialData;
	}
	namespace Manager
	{
		class WindowManager;

		/**************************************************//*!
		*	@brief	Provides easy access to dock and editor
		*			properties, especially to plugins.
		*
		* Properties are unique to each different object
		* type, so names must match. Naming conflicts are an
		* issue so plugin developers are encouraged to be
		* wise with naming. Always check plugin documentation
		* for both object names and property names.
		*
		* In addition, for docks that update in a
		* synchroniszed fasion with docks in other windows,
		* setting the "all" parameter to true in several
		* functions will have undesirable consequences.
		******************************************************/
		class PropertyManager
		{
		public:

			/**************************************************//*!
			*	@brief	Allocates a property manager. It must
			*			have access to the window manager.
			******************************************************/
			PropertyManager(WindowManager *);

			/**************************************************//*!
			*	@brief	Returns true if there exists a dock type
			*			with the indicated name.
			******************************************************/
			bool dockExists(const QString &name);

			/**************************************************//*!
			*	@brief	Finds the indicated dock and sets a
			*			property to the indicated value and
			*			scope.
			*	@param	name The dock type name to modify.
			*	@param	property The property to change.
			*	@param	data The new value for the property.
			*	@param	all If true, all docks are modified, or
			*			else only the active dock is modified.
			******************************************************/
			void dockSetProperty(const QString &name, const QString &property,
				Resource::SerialData *data, bool all = false);

			/**************************************************//*!
			*	@brief	Executes a command.
			*	@param	name The dock type name to modify.
			*	@param	command The command to execute. This is
			*			unique with every dock type.
			*	@param	data The new value for the property.
			*	@param	all If true, all docks are modified, or
			*			else only the active dock is modified.
			******************************************************/
			Resource::SerialData *dockExecute(const QString &name,
				uint8_t command, Resource::SerialData *data = nullptr,
				bool all = false);

			/**************************************************//*!
			*	@brief	Returns the value of the indicated dock
			*			type name of the property.
			******************************************************/
			Resource::SerialData *dockProperty(const QString &name,
				const QString &property);

			/**************************************************//*!
			*	@brief	Returns the value of the indicated editor
			*			type name of the property.
			******************************************************/
			bool editorExists(const QString &name);

			/**************************************************//*!
			*	@brief	Finds the indicated editor and sets a
			*			property to the indicated value and
			*			scope.
			*	@param	name The dock type name to modify.
			*	@param	property The property to change.
			*	@param	data The new value for the property.
			*	@param	all If true, all editor are modified, or
			*			else only the active editor is modified.
			******************************************************/
			void editorSetProperty(const QString &name, const QString &property,
				Resource::SerialData *data, bool all = false);

			/**************************************************//*!
			*	@brief	Executes a command.
			*	@param	name The dock type name to modify.
			*	@param	command The command to execute. This is
			*			unique with every dock type.
			*	@param	data The new value for the property.
			*	@param	all If true, all docks are modified, or
			*			else only the active dock is modified.
			******************************************************/
			Resource::SerialData *editorExecute(const QString &name,
				uint8_t command, Resource::SerialData *data = nullptr,
				bool all = false);

			/**************************************************//*!
			*	@brief	Returns the value of the indicated editor
			*			type name of the property.
			******************************************************/
			Resource::SerialData *editorProperty(const QString &name,
				const QString &property);

		private:

			/**************************************************//*!
			*	@brief	Stores the window manager. It must always
			*			exist.
			******************************************************/
			WindowManager *_windowManager;

		};
	}
}

#endif // NGM__PROPERTYMANAGER__HPP
