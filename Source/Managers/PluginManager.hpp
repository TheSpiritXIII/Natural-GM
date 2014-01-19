/**
 *  @file PluginManager.hpp
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
#ifndef NGM__PLUGINMANAGER__HPP
#define NGM__PLUGINMANAGER__HPP
#include <QFileSystemWatcher>
#include "Plugin.hpp"
#include <QLibrary>
#include <QList>
#include <QHash>

namespace NGM
{
	namespace Manager
	{
		/**************************************************//*!
		*	@brief	Loads and manages projects.
		******************************************************/
		class PluginManager
		{
		public:

			/**************************************************//*!
			*	@brief	Loads all plugins. They are loaded from
			*			the "Plugins" directory. This function
			*			reloads all plugins.
			******************************************************/
			void load();

			/**************************************************//*!
			*	@brief	Loads a plugin by directory name. Returns
			*			true if there are plugin dependencies.
			******************************************************/
			bool load(const QString &directory);

			/**************************************************//*!
			*	@brief	Removes the indicated plugin.
			******************************************************/
			void remove(const Resource::Plugin *plugin);

			/**************************************************//*!
			*	@brief	Generates a list of plugins.
			******************************************************/
			QList<const Resource::Plugin*> plugins() const;

		private:

			/**************************************************//*!
			*	@brief	Stores all loaded libraries.
			******************************************************/
			QHash<Resource::Plugin*, QLibrary*> _libraries;

			/**************************************************//*!
			*	@brief	Loads the indicated plugin.
			******************************************************/
			void loadPlugin(const QString &directory);

		};
	}
}
#endif //NGM__PLUGINMANAGER__HPP
