/**
 *  @file PluginManager.cpp
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
#include "PluginManager.hpp"
#include <QStringBuilder>
#include <QMessageBox>
#include <QDir>

#include <QDebug>

namespace NGM
{
	namespace Manager
	{
		typedef Plugin *(*Load)();

		void PluginManager::load()
		{
			QDir dir(QStringLiteral("plugins/"));
			QStringList list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
			for (auto &i : list)
			{
				qDebug() << i;
				loadPlugin(dir.absolutePath() % QStringLiteral("/") %
						   i % QStringLiteral("/"));
			}
			for (auto &i : _libraries)
			{
				qDebug() << "Poop";
				i.plugin()->init();
			}
		}

		bool PluginManager::load(const QString &directory)
		{
			QFile file(QStringLiteral("plugins/") % directory);
			if (file.exists())
			{
				// Size increased if successful.
				size_t size = _libraries.size();
				loadPlugin(file.fileName());
				if (size != _libraries.size())
				{
					return true;
				}
			}
			return false;
		}

		list<const Plugin *> PluginManager::plugins() const
		{
			list<const Plugin*> list;
			for (auto &i : _libraries)
			{
				list.push_back(i.plugin());
			}
			return list;
		}

		void PluginManager::loadPlugin(const QString &directory)
		{
			QLibrary *lib = new QLibrary(directory % QStringLiteral("plugin"));
			if (lib->load())
			{
				Load function = reinterpret_cast<Load>(lib->resolve("plugin"));
				if (function)
				{
					Plugin *plug = function();
					if (plug != nullptr)
					{
						_libraries.insert(PluginLibrary(plug, lib));
					}
					else
					{
						lib->unload();
						QMessageBox::warning(0, QStringLiteral("Warning"),
							QStringLiteral("Could not load plugin: ") % directory);
						delete lib;
					}
				}
				else
				{
					lib->unload();
					QMessageBox::warning(0, QStringLiteral("Warning"),
						QStringLiteral("Could not resolve plugin: ") % directory);
					delete lib;
				}
			}
			else
			{
				QMessageBox::warning(0, QStringLiteral("Warning"),
					QStringLiteral("Could not load plugin: ") % lib->errorString());
				delete lib;
			}
		}
	}
}
