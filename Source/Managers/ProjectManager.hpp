/**
 *  @file ProjectManager.cpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#ifndef NGM__PROJECTMANAGER__HPP
#define NGM__PROJECTMANAGER__HPP
#include <QString>
#include <QList>

#include <map>
#include <QIcon>
#include "Type.hpp"
#include "../Global.hpp"
#include "Project.hpp"
#include "TextSerializer.hpp"
#include "GMXSerializer.hpp"

// Need to split Projects and Editors.
// Needs to fix over half functions.
namespace NGM
{
	namespace Resource
	{
		class Type;
		class Factory;
	}
	namespace Manager
	{
		class WindowManager;
		class ActionManager;

		typedef QList<Resource::Project*>::iterator ProjectIterator;

		/**************************************************//*!
		*	@brief	Iterates through a set of project's
		*			icons. Used for setting the icons.
		******************************************************/
		class ProjectIconIterator
		{
		public:

			/**************************************************//*!
			*	@brief	Creates a project icon iterator using
			*			a project set iterator.
			******************************************************/
			ProjectIconIterator(ProjectIterator i) : _i(i) {}

			/**************************************************//*!
			*	@brief	Returns the name of the project at the
			*			current position.
			******************************************************/
			const QString getName()
			{
				return (*_i)->name;
			}

			/**************************************************//*!
			*	@brief	Returns the icon at the current position.
			******************************************************/
			QIcon *getIcon()
			{
				return &(*_i)->icon;
			}

			/**************************************************//*!
			*	@brief	Returns whether or not the iterators
			*			match.
			******************************************************/
			inline bool operator==(const ProjectIterator &i) const
			{
				return _i == i;
			}

			/**************************************************//*!
			*	@brief	Increments the iterator.
			******************************************************/
			inline void operator++()
			{
				++_i;
			}

		private:

			/**************************************************//*!
			*	@brief	Stores the project set iterator.
			******************************************************/
			ProjectIterator _i;
		};

		/**************************************************//*!
		*	@brief	Registers project types.
		******************************************************/
		class ProjectManager
		{
		public:

			/**************************************************//*!
			*	@brief	Creates default serializers and types.
			******************************************************/
			ProjectManager();

			/**************************************************//*!
			*	@brief	Deallocates all project types.
			******************************************************/
			~ProjectManager();

			///	DEPRECATED
			const std::multimap<const QString, Resource::Project*>&
				getProjectList() const;

			///	DEPRECATED
			const std::multimap<const QString, Resource::Project*>&
				getFileProjectList() const;

			///	DEPRECATED
			std::map<const QString, Resource::Project*> getProjectCategory(QString category, bool root) const;

			///	DEPRECATED
			std::map<const QString, Resource::Project*> getFileProjectCategory(QString category, bool root) const;

			/**************************************************//*!
			*	@brief	Returns a type for editing file. These
			*			types are useful for editing any files.
			*			Ideally, this should contain text and
			*			hex editors.
			******************************************************/
			Resource::Type *fileType()
			{
				return typeFile;
			}

			/**************************************************//*!
			*	@brief	Returns a serializer that opens files.
			******************************************************/
			Resource::Serializer *fileSerializer()
			{
				return &textSerializer;
			}

			/**************************************************//*!
			*	@brief	Returns all projects sorted into
			*			different categories.
			*	@param	categoryFilter The categories that are
			*			allowed to be listed.
			******************************************************/
			void projectsByCategories
				(QVector<QVector<Resource::Project*>> *list,
				 const QStringList &categoryFilter) const;

			/**************************************************//*!
			*	@brief	Adds a project.
			******************************************************/
			void addProject(Resource::Project *project);

			/**************************************************//*!
			*	@brief	Returns the project with the specified
			*			name. This is O(n).
			******************************************************/
			// TODO: Maybe make this const.
			Resource::Project *findProject(const QString &name);

			/**************************************************//*!
			*	@brief	Adds a type.
			******************************************************/
			void addType(Resource::Type *type);

			/**************************************************//*!
			*	@brief	Returns the type with the specified name.
			*			This is O(logn).
			******************************************************/
			const Resource::Type *findType(const QString &name) const;

			/**************************************************//*!
			*	@brief	Returns an icon iterator, starting at
			*			the first project.
			******************************************************/
			inline ProjectIconIterator iconIterator()
			{
				return ProjectIconIterator(_projects.begin());
			}

			/**************************************************//*!
			*	@brief	Returns whether or not the project icon
			*			iterator is at the end.
			******************************************************/
			inline bool iconIteratorEnd(const ProjectIconIterator &i)
			{
				return i == _projects.end();
			}

		private:

			/**************************************************//*!
			*	@brief	A basic serializer for opening text
			*			files.
			******************************************************/
			Resource::TextSerializer textSerializer;

			/**************************************************//*!
			*	@brief	A serializer that opens GameMaker Studio
			*			projects.
			******************************************************/
			Resource::GMXSerializer gmxSerializer;

			QList<Resource::Type*> _types;

			/**************************************************//*!
			*	@brief	Stores all registered types.
			******************************************************/
			Resource::Type *typeFile;

			///	DEPRECATED
			std::multimap<const QString, Resource::Project*> projects;

			///	DEPRECATED
			std::multimap<const QString, Resource::Project*> files;

			/**************************************************//*!
			*	@brief	Stores all registered project types.
			******************************************************/
			QList<Resource::Project*> _projects;

			///	DEPRECATED
			friend class NGM::Manager::WindowManager;

			///	DEPRECATED
			friend class NGM::Manager::ActionManager;
		};
	}
}

#endif // NGM__PROJECTMANAGER__HPP
