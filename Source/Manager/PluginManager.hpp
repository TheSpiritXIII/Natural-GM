/*-
 *  Copyright (c) 2014 Daniel Hrabovcak
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 *  for more details.
**/
#pragma once
#include <QSet>

class QWidget;

namespace NGM
{
	namespace Core
	{
		struct Library;
	};
	namespace Manager
	{
		/**************************************************//*!
		*  @brief  Loads plugins.
		******************************************************/
		struct PluginManager
		{
			PluginManager();
			~PluginManager();

			/**************************************************//*!
			*  @brief  Finds and loads all plugins.
			******************************************************/
			void load();

			/**************************************************//*!
			*  @brief  Loads the indicated plugin. The default
			*          plugin directory is searched for the
			*          plugin and then is validated.
			*  @return False if the plugin has failed to load or
			*          does not exist, or true if the load is
			*          successful.
			******************************************************/
			bool load(const QString &name);
			
			/**************************************************//*!
			*  @brief  Creates and returns a dialog that is
			*          capable of modifying plugins.
			******************************************************/
			QWidget *dialog();

			/**************************************************//*!
			*  @brief  Returns the list of plugins.
			******************************************************/
			const QSet<Core::Library*> &plugins() const;

		private:
			QSet<Core::Library*> _plugins;
		};
	};
}
