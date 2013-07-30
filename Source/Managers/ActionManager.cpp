/**
 *  @file ActionManager.cpp
 *  @brief Defines a class that stores icons and actions.
 *
 *  @section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
 *
 *      This file is a part of the Natural GM IDE.
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
#include <QFile>
#include "ActionManager.hpp"
#include "WindowManager.hpp"
#include "ProjectManager.hpp"
#include "Resources/Project.hpp"
#include <QDebug>

namespace NGM
{
	namespace Manager
	{
		ActionManager::ActionManager(WindowManager *manager, ProjectManager *project) :
			theme("Natural Native"), project(project), manager(manager) {}

		ActionManager::~ActionManager()
		{
			// Inherited behavior.
		}

		QIcon *ActionManager::getIconFromTheme(QString location)
		{
			return iconByTheme.find(location)->second;
		}

		QIcon *ActionManager::getIconFromFile(QString location)
		{
			return iconByTheme.find(location)->second;
		}

		QString ActionManager::getFullThemeDirectory(QString name)
		{
			return "icons/"+theme+"/"+name;
		}

		void ActionManager::reload()
		{
			//actions[ActionNew]->setIcon(QIcon("icons/"+theme+"/main/new"));
			//actions[ActionOpen]->setIcon(QIcon("icons/"+theme+"/main/open"));
			//actions[ActionSave]->setIcon(QIcon("icons/"+theme+"/main/save"));
			/*for(Resource::Type* i : project->types_)
			{
				i->icon = QIcon("icons/"+theme+"/project/"+i->name);
			}*/
		}
	}
}
