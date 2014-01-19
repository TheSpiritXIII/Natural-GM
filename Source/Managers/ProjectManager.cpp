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


NGM::Manager::ProjectManager::~ProjectManager()
{
	for (QSet<Resource::Project*>::iterator i = _projects.begin(); i != _projects.end(); ++i)
	{
		delete (*i);
	}
}

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
			_types.insert(typeFile);

			Project *project = new Resource::Project("GML Script", GMOther,
				GMLScriptDesc, FileDetails(QStringList("*.gml")),
				&textSerializer, typeFile, Resource::Project::FileType);
			projects.insert(ProjectPair("GML Script", project));
			_projects.insert(project);

			project =  new Resource::Project("Plain Text", General,
				PlainTextDesc, QStringList("*.txt"), &textSerializer,
				typeFile, Resource::Project::FileType);
			files.insert(ProjectPair("Plain Text", project));
			_projects.insert(project);

			project =  new Resource::Project(GMStudioProj ,GMStudio,
				GMStudioProjDesc, FileDetails(QStringList("*.project.gmx")),
				&gmxSerializer, nullptr);
			projects.insert(ProjectPair(GMStudioProj, project));
			_projects.insert(project);
		}

		void ProjectManager::registerProject(Resource::Serializer *serializer,
			const QString &name, const QString &category,
			const QString &description, const QStringList extensions,
			Resource::Type *type)
		{
			projects.insert(pair<QString, Resource::Project*>(name,
				new Resource::Project(serializer, type, category, description,
				extensions)));
			_projects.insert(new Resource::Project(name, category,
				description, FileDetails(extensions), serializer, type));
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
			if (_types.find(type) != _types.end())
			{
				type->addFactory(++factory);
				while (size != 1)
				{
					type->addFactory(++factory);
					--size;
				}
				_types.insert(type);
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
			auto i = _types.find(type);
			delete type;
			if (i != _types.end())
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

		void ProjectManager::projectsByCategories
			(QVector<QVector<Resource::Project*>> *list,
			 const QStringList &categoryFilter) const
		{
			// TODO Add Filter.
			bool added = false;
			for (auto &i : _projects)
			{
				for (auto &j : *list)
				{
					if (j.front()->category == i->category)
					{
						added = true;
						break;
					}
				}
				if (!added)
				{
					QVector<Resource::Project*> subcategory;
					subcategory.append(i);
					list->append(subcategory);
				}
				added = false;
			}
		}
	}
}
