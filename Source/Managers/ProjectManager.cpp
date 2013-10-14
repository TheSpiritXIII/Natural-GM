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
#include "../Global.hpp"
#include "ProjectManager.hpp"
#include <QMessageBox>
#include "../Resources/Types/TextType.hpp"
#include <QDebug>
#include "../Defines.hpp"
using std::map;
using std::pair;
using std::string;
using std::multimap;
using namespace NGM::Definition;

namespace NGM
{
	using namespace Resource;
	typedef std::pair<const QString, Resource::Project*> ProjectPair;
	namespace Manager
	{
		ProjectManager::ProjectManager()
		{
			types["text/text"] = new NGM::Resource::TextType(QObject::tr("Plain Text"), QObject::tr("Plain Text"));
			projects.insert(ProjectPair("GML Script", new NGM::Resource::Project(&textSerializer, types.begin()->second, GMOther, GMLScriptDesc, QStringList("*.gml"))));
			files.insert(ProjectPair("Plain Text", new NGM::Resource::Project(&textSerializer, types.begin()->second, General, PlainTextDesc, QStringList("*.txt") << "*.*")));
			projects.insert(ProjectPair(GMStudioProj, new NGM::Resource::Project(&gmxSerializer, types.begin()->second, GMStudio, GMStudioProjDesc, QStringList("*.project.gmx"))));
		}

		ProjectManager::~ProjectManager()
		{
			for (auto& i : projects)
			{
				delete i.second;
			}
			for (auto& i : types)
			{
				delete i.second;
			}
		}

		void ProjectManager::registerProject(NGM::Resource::Serializer *serializer,
			const QString &name, const QString &category, const QString &description,
			const QStringList extensions, NGM::Resource::Type *type)
		{
			projects.insert(pair<QString, NGM::Resource::Project*>(name, new NGM::Resource::Project(serializer, type, category, description, extensions)));
		}

		void ProjectManager::registerFileProject(NGM::Resource::Serializer *serializer,
			const QString &name, const QString &category, const QString &description,
			const QStringList extensions, NGM::Resource::Type *type)
		{
			files.insert(pair<QString, NGM::Resource::Project*>(name, new NGM::Resource::Project(serializer, type, category, description, extensions)));
		}

		void ProjectManager::registerType(const QString &name, Type *type)
		{
			types.insert(pair<QString, NGM::Resource::Type*>(name, type));
		}

		const NGM::Resource::Type *ProjectManager::getType(const QString &name) const
		{
			return types.find(name)->second;
		}

		const multimap<const QString, Project*> &ProjectManager::getProjectList() const
		{
			return projects;
		}

		const multimap<const QString, Project*> &ProjectManager::getFileProjectList() const
		{
			return files;
		}

		map<const QString, Project*> ProjectManager::getProjectCategory(QString category, bool root) const
		{
			map<const QString, NGM::Resource::Project*> p;
			for (auto& i : projects)
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

		map<const QString, Project*> ProjectManager::getFileProjectCategory(const QString category, bool root) const
		{
			map<const QString, NGM::Resource::Project*> p;
			for (auto& i : files)
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
