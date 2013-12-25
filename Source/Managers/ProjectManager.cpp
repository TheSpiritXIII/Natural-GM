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
#include "Factory.hpp"
#include <QMessageBox>
#include <QDebug>
#include "TextEditor.hpp"
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
		bool operator<(NGM::Resource::Type* type, const QString &string)
		{
			return type->name < string;
		}

		ProjectManager::ProjectManager()
		{
			typeFile = new NGM::Resource::Type(QStringLiteral("file"), new Factory(QStringLiteral("Default Text Editor"), &TextEditor::create));
			types.insert(typeFile);
			projects.insert(ProjectPair("GML Script", new Resource::Project(&textSerializer, typeFile, GMOther, GMLScriptDesc, QStringList("*.gml"))));
			files.insert(ProjectPair("Plain Text", new Resource::Project(&textSerializer, typeFile, General, PlainTextDesc, QStringList("*.txt") << "*.*")));
			projects.insert(ProjectPair(GMStudioProj, new Resource::Project(&gmxSerializer, nullptr, GMStudio, GMStudioProjDesc, QStringList("*.project.gmx"))));
		}

		ProjectManager::~ProjectManager()
		{
			for (auto& i : projects)
			{
				delete i.second;
			}
			for (auto i : types)
			{
				delete i;
			}
		}

		void ProjectManager::registerProject(Resource::Serializer *serializer,
			const QString &name, const QString &category,
			const QString &description, const QStringList extensions,
			Resource::Type *type)
		{
			projects.insert(pair<QString, Resource::Project*>(name,
				new Resource::Project(serializer, type, category, description,
				extensions)));
		}

		void ProjectManager::registerFile(Resource::Serializer *serializer,
			const QString &name, const QString &category,
			const QString &description, const QStringList extensions,
			Resource::Type *type)
		{
			files.insert(pair<QString, Resource::Project*>(name,
				new Resource::Project(serializer, type, category, description,
				extensions)));
		}

		void ProjectManager::registerType(const QString &name, Factory *factory, size_t size)
		{
			Resource::Type *type = new Type(name);
			if (types.find(type) != types.end())
			{
				type->addFactory(++factory);
				while (size != 1)
				{
					type->addFactory(++factory);
					--size;
				}
				types.insert(type);
				delete type;
			}
			else
			{
				type->addFactory(factory);
			}
		}

		const NGM::Resource::Type *ProjectManager::getType(const QString &name) const
		{
			Resource::Type *type = new Type(name);
			auto i = types.find(type);
			delete type;
			if (i != types.end())
			{
				return (*i);
			}
			return nullptr;
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
