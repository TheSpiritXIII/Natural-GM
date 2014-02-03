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
#include "ProjectManager.hpp"
#include <algorithm>

///INCOMPLETE
#include "../Global.hpp"
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

#include <algorithm>

typedef QList<NGM::Resource::Project*>::const_iterator ProjectIteratorConst;

NGM::Manager::ProjectManager::~ProjectManager()
{
	for (ProjectIterator i = _projects.begin(); i != _projects.end(); ++i)
	{
		delete (*i);
	}
	for (QList<Resource::Type*>::iterator i = _types.begin();
		 i != _types.end(); ++i)
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
			addType(typeFile);

			Project *project = new Resource::Project("GML Script", GMOther,
				GMLScriptDesc, FileDetails(QStringList("*.gml")),
				&textSerializer, typeFile, Resource::Project::FileType);
			projects.insert(ProjectPair("GML Script", project));
			addProject(project);

			project =  new Resource::Project("Plain Text", General,
				PlainTextDesc, QStringList("*.txt"), &textSerializer,
				typeFile, Resource::Project::FileType);
			files.insert(ProjectPair("Plain Text", project));
			addProject(project);

			project =  new Resource::Project(GMStudioProj ,GMStudio,
				GMStudioProjDesc, FileDetails(QStringList("*.project.gmx")),
				&gmxSerializer, nullptr);
			projects.insert(ProjectPair(GMStudioProj, project));
			addProject(project);
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
			bool added = false;
			for (auto &i : _projects)
			{
				for (int k = 0; k != categoryFilter.size(); ++k)
				{
					if (i->category == categoryFilter[k])
					{
						added = true;
						break;
					}
				}
				if (!added)
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
				}
				added = false;
			}
		}
	}
}

void NGM::Manager::ProjectManager::addProject(Resource::Project *project)
{
	_projects.append(project);
}

NGM::Resource::Project *NGM::Manager::ProjectManager::findProject(
		const QString &name)
{
	for (ProjectIteratorConst i = _projects.begin(); i != _projects.end(); ++i)
	{
		qDebug() << (*i)->name;
		if ((*i)->name == name)
		{
			return *i;
		}
	}
	return nullptr;
}

void NGM::Manager::ProjectManager::addType(Resource::Type *type)
{
	_types.insert(std::lower_bound(_types.begin(), _types.end(), type,
								   &Resource::Type::lessThan), type);
}

const NGM::Resource::Type *NGM::Manager::ProjectManager::findType(
		const QString &name) const
{
	return *std::lower_bound(_types.begin(), _types.end(), name,
							 &Resource::Type::lessThanText);
}
