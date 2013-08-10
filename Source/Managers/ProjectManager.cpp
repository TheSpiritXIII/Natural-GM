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
using std::map;
using std::pair;
using std::string;
using std::multimap;

namespace NGM
{
	using namespace Resource;
	namespace Manager
	{
		ProjectManager::ProjectManager()
		{
			types.insert(pair<const char*, NGM::Resource::Type*>("Plain Text", new NGM::Resource::TextType(QObject::tr("ngm_PlainText"), QObject::tr("Plain Text"))));
			projects.insert(pair<QString, NGM::Resource::Project*>(GMLScript, new NGM::Resource::Project(&textSerializer, types.begin()->second, GMOther, GMLScriptDesc, QStringList(".gml"))));
			projects.insert(pair<QString, NGM::Resource::Project*>(PlainText, new NGM::Resource::Project(&textSerializer, nullptr, General, PlainTextDesc, QStringList(".txt"))));
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

		void ProjectManager::registerType(const string &name, Type *type)
		{
			types.insert(pair<string, NGM::Resource::Type*>(name, type));
		}

		const NGM::Resource::Type *ProjectManager::getType(const std::string &name) const
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
	}
}
