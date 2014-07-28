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
#include "PluginManager.hpp"
#include "PluginDialog.hpp"
#include "Directory.hpp"
#include "Library.hpp"
#include "PluginDepr.hpp"
#include <QStringBuilder>
#include <QDir>

#include "TestPlugin.hpp"

typedef NGM::API::Plugin *(*PluginFunc)();

NGM::Manager::PluginManager::PluginManager()
{
	_plugins.insert(new Core::Library(new TestPlugin(), 0));
}

NGM::Manager::PluginManager::~PluginManager()
{
	for (auto &i : _plugins)
	{
		delete i;
	}
}

void NGM::Manager::PluginManager::load()
{
	QDir dir;
	QFileInfoList list = dir.entryInfoList(QStringList(),
	  QDir::AllDirs | QDir::NoDotDot);
	for (auto &i : list)
	{
		load(i.completeBaseName());
	}
}

bool NGM::Manager::PluginManager::load(const QString &name)
{
	QString location = NGM::Core::directory % QString("Plugins/") % name %
	  QChar('/') % name;
	if (QLibrary::isLibrary(location))
	{
		QLibrary *lib = new QLibrary(location);
		lib->load();
		PluginFunc load = reinterpret_cast<PluginFunc>(lib->resolve("plugin"));
		if (load)
		{
			API::Plugin *plugin = load();
			if (plugin && !plugin->name.isEmpty() &&
			  !plugin->authors.isEmpty() && !plugin->description.isEmpty())
			{
				_plugins.insert(new Core::Library(plugin, lib));
			}
			else
			{
				delete lib;
				return false;
			}
		}
		else
		{
			delete lib;
			return false;
		}
	}
	return true;
}

QWidget *NGM::Manager::PluginManager::dialog()
{
	return new Widget::PluginDialog(&_plugins);
}

const QSet<NGM::Core::Library *> &NGM::Manager::PluginManager::plugins() const
{
	return _plugins;
}


