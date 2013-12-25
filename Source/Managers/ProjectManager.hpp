/**
 *  @file ProjectManager.hpp
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
#pragma once
#ifndef _NGM_PROJECTMANAGER__HPP
#define _NGM_PROJECTMANAGER__HPP
#include <map>
#include <string>
#include <QIcon>
#include <QString>
#include "Type.hpp"
#include "../Global.hpp"
#include "Project.hpp"
#include "TextSerializer.hpp"
#include "GMXSerializer.hpp"
#include "Set.hpp"

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

			/**************************************************//*!
			*	@brief	Registers a project type with the
			*			specified metadata.
			*	@param	serializer The way the file is loaded.
			*	@param	name The name of the project type.
			*	@param	category The category of the project. You
			*			can use "|" to add a subcategory.
			*	@param	description A detailed description of the
			*			project type.
			*	@param	extensions	A list of supported extensions.
			******************************************************/
			void registerProject(Resource::Serializer *serializer,
				const QString &name, const QString &category,
				const QString &description, const QStringList extensions,
				Resource::Type *type);

			/**************************************************//*!
			*	@brief	Registers a file project type with the
			*			specified metadata.
			*	@param	serializer The way the file is loaded.
			*	@param	name The name of the project type.
			*	@param	category The category of the project. You
			*			can use "|" to add a subcategory.
			*	@param	description A detailed description of the
			*			project type.
			*	@param	extensions	A list of supported extensions.
			******************************************************/
			void registerFile(Resource::Serializer *serializer,
				const QString &name, const QString &category,
				const QString &description, const QStringList extensions,
				Resource::Type *type);

			/**************************************************//*!
			*	@brief	Stores and adds a resource type.
			******************************************************/
			void registerType(const QString &name, Resource::Type *type);
			void registerType(const QString &name, Resource::Factory *factory, size_t size = 0);

			/**************************************************//*!
			*	@brief	Returns the type with the specified name.
			******************************************************/
			const Resource::Type *getType(const QString &name) const;

			/**************************************************//*!
			*	@brief	Returns a list of all registered projects.
			******************************************************/
			const std::multimap<const QString, Resource::Project*>&
				getProjectList() const;

			/**************************************************//*!
			*	@brief	Returns a list of all registered file
			*			projects.
			******************************************************/
			const std::multimap<const QString, Resource::Project*>&
				getFileProjectList() const;

			/**************************************************//*!
			*	@return A map containing all projects in the
			*			indicated category.
			*	@param	category The category you are looking for.
			*	@param	root True if you wish to include
			*			subcategories, false otherwise
			******************************************************/
			std::map<const QString, Resource::Project*> getProjectCategory(QString category, bool root) const;

			/**************************************************//*!
			*	@return A map containing all projects in the
			*			indicated category.
			*	@param	category The category to search.
			*	@param	root True if you wish to include
			*			subcategories, false otherwise
			******************************************************/
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

			/**************************************************//*!
			*	@brief	Stores all registered types.
			******************************************************/
			Set<Resource::Type*> types;

			/**************************************************//*!
			*	@brief	Stores all registered types.
			******************************************************/
			Resource::Type *typeFile;

			/**************************************************//*!
			*	@brief	Stores all registered projects.
			******************************************************/
			std::multimap<const QString, Resource::Project*> projects;

			/**************************************************//*!
			*	@brief	Stores all registered file types.
			******************************************************/
			std::multimap<const QString, Resource::Project*> files;

			friend class NGM::Manager::WindowManager;
			friend class NGM::Manager::ActionManager;
		};
	}
}

#endif // _NGM_PROJECTMANAGER__HPP
