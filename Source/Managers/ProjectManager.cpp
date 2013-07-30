/**
 *  @file ProjectManager.hpp
 *  @brief Declares a class that stores project metadata.
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
#include "Global.hpp"
#include "ProjectManager.hpp"
#include <QMessageBox>
#include "Resources/Types/TextType.hpp"
#include <QDebug>

namespace NGM
{
	using namespace Resource;
	namespace Manager
	{
		ProjectManager::ProjectManager() :
			/*types
			{
				new Resource::TextType(QObject::tr("Plain Text"), QObject::tr("Plain Text"))
			},
			projects
			{
				new Resource::Project(&textSerializer, types[0], GMLScript, GMOther, GMLScriptDesc, QStringList(".gml")),
				new Resource::Project(&textSerializer, types[0], PlainText, General, PlainTextDesc, QStringList(".txt"))
			},*/
			types_
			{
				pair<const char*, Resource::Type*>("Plain Text", new Resource::TextType(QObject::tr("ngm_PlainText"), QObject::tr("Plain Text")))
			},
			projects_
			{
				pair<QString, Resource::Project*>(GMLScript, new Resource::Project(&textSerializer, types_.find("Plain Text")->second, GMLScript, GMOther, GMLScriptDesc, QStringList(".gml"))),
				pair<QString, Resource::Project*>(PlainText, new Resource::Project(&textSerializer, types_.find("Plain Text")->second, PlainText, General, PlainTextDesc, QStringList(".txt")))
			}
		{
		}

		ProjectManager::~ProjectManager()
		{
			for (auto& i : projects_)
			{
				delete i.second;
			}
			for (auto& i : types_)
			{
				delete i.second;
			}
		}

		void ProjectManager::registerProject(QString name, QString category, QString description, QStringList extensions, Type *type)
		{
			//projects.push_back(new Resource::Project(NULL, NULL, name, type, description, extensions));
		}

		const multimap<QString, Resource::Project*> ProjectManager::getProjectList()
		{
			return projects_;
		}

		/*void ProjectManager::registerResource(QString name, QString plural)
		{
			for (Resource::Type *i : types)
			{
				if (i->name == name)
				{
#ifdef NGM_DEBUG
					qDebug() << "ProjectManager - Error - Cannot register, type already exists:" << name;
#else
					QMessageBox::critical(0, "Error", "Cannot register resource type.");
#endif
					return;
				}
			}
			types.push_back(new Resource::Type(name, plural));
		}*/

		/*Resource::Project *ProjectManager::getProject(QString name, QString category)
		{
			for (Resource::Project *i : projects)
			{
				if (i->name == name && i->category == category)
				{
					return i;
				}
			}
			return NULL;
		}*/

		map<QString, Resource::Project*> ProjectManager::getProjectCategory(QString category, bool root) const
		{
			map<QString, Resource::Project*> p;
			for (auto& i : projects_)
			{
				if (root)
				{
					if (i.second->category.left(i.second->category.indexOf('-')) == category)
					{
						p.insert(i);
					}
				}
				else if (i.second->category == category)
				{
					p.insert(i);
				}
			}
			return p;
		}
	}
}
