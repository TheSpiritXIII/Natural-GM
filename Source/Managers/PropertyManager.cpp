/**
 *  @file PropertyManager.cpp
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
#include "PropertyManager.hpp"

namespace NGM
{
	namespace Manager
	{
		PropertyManager::PropertyManager(WindowManager *windowManager) :
			_windowManager(windowManager) {}

		bool PropertyManager::dockExists(const QString &name)
		{
			Q_UNUSED(name);
			return false;
		}

		void PropertyManager::dockSetProperty(const QString &name,
			const QString &property, Resource::SerialData *data, bool all)
		{
			Q_UNUSED(name);
			Q_UNUSED(property);
			Q_UNUSED(data);
			Q_UNUSED(all);
		}

		Resource::SerialData *PropertyManager::dockExecute(const QString &name,
			uint8_t command, Resource::SerialData *data, bool scope)
		{
			Q_UNUSED(name);
			Q_UNUSED(command);
			Q_UNUSED(data);
			Q_UNUSED(scope);
			return nullptr;
		}

		Resource::SerialData *PropertyManager::dockProperty(const QString &name,
			const QString &property)
		{
			Q_UNUSED(name);
			Q_UNUSED(property);
			return nullptr;
		}

		bool PropertyManager::editorExists(const QString &name)
		{
			Q_UNUSED(name);
			return false;
		}

		void PropertyManager::editorSetProperty(const QString &name,
			const QString &property, Resource::SerialData *data, bool all)
		{
			Q_UNUSED(name);
			Q_UNUSED(property);
			Q_UNUSED(data);
			Q_UNUSED(all);
		}

		Resource::SerialData *PropertyManager::editorExecute(const QString
			&name, uint8_t command, Resource::SerialData *data, bool scope)
		{
			Q_UNUSED(name);
			Q_UNUSED(command);
			Q_UNUSED(data);
			Q_UNUSED(scope);
			return nullptr;
		}

		Resource::SerialData *PropertyManager::editorProperty(const QString
			&name, const QString &property)
		{
			Q_UNUSED(name);
			Q_UNUSED(property);
			return nullptr;
		}
	}
}
