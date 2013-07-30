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
#include <vector>
#include <QIcon>
#include <QString>
#include "Type.hpp"
#include "Global.hpp"
#include "Project.hpp"
#include "TextSerializer.hpp"

namespace NGM
{
	namespace Resource
	{
		class Type;
	}
	namespace Manager
	{
		class WindowManager;
		class ActionManager;
		using std::map;
		using std::pair;
		using std::multimap;

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
			*	@brief	Registers a serializer.
			******************************************************/
			void registerSerializer(Resource::Serializer *serializer);

			/**************************************************//*!
			*	@brief	Gets the serializer at the specified index.
			******************************************************/
			Resource::Serializer *getSerializer(int index);

			/**************************************************//*!
			*	@brief	Registers a project type with the
			*			specified metadata.
			*	@param	name The name of the project type.
			*	@param	category The category of the project. You
			*			can use "|" to add a subcategory.
			*	@param	description A detailed description of the
			*			project type.
			*	@param	extensions	A list of supported extensions.
			******************************************************/
			void registerProject(QString name,
								 QString category,
								 QString description,
								 QStringList extensions,
								 Resource::Type *type);

			/**************************************************//*!
			*	@brief	Stores and adds a resource type.
			******************************************************/
			void registerType(QString name, Resource::Type *type);

			/**************************************************//*!
			*	@brief	Returns the type at the specified index.
			******************************************************/
			Resource::Type *getType(QString name);

			/**************************************************//*!
			*	@brief	Reloads all icons.
			*	@param	location The directory to search for icons.
			******************************************************/
			void reloadIcons(QString location);

			/**************************************************//*!
			*	@brief	Returns a list of all registered projects.
			******************************************************/
			const multimap<QString, Resource::Project*> getProjectList();

			/**************************************************//*!
			*	@return A map containing all projects in the
			*			indicated category.
			*	@param	category The category you are looking for.
			*	@param	root True if you wish to include
			*			subcategories, false otherwise
			******************************************************/
			map<QString, Resource::Project*> getProjectCategory(QString category, bool root) const;

		private:

			/**************************************************//*!
			*	@brief	A basic serializer for opening text files. (CHANGE)
			******************************************************/
			Resource::TextSerializer textSerializer;

			/**************************************************//*!
			*	@brief	Contains all resource types. (REMOVE)
			******************************************************/
			//std::vector<Resource::Type*> types;

			/**************************************************//*!
			*	@brief	Contains all project types.
			******************************************************/
			//std::vector<Resource::Project*> projects;

			/**************************************************//*!
			*	@brief	Stores all registered types.
			******************************************************/
			std::multimap<const char*, Resource::Type*> types_;

			/**************************************************//*!
			*	@brief	Stores all registered projects.
			******************************************************/
			std::multimap<QString, Resource::Project*> projects_;

			friend class NGM::Manager::WindowManager;
			friend class NGM::Manager::ActionManager;
		};
	}
}

#endif // _NGM_PROJECTMANAGER__HPP
