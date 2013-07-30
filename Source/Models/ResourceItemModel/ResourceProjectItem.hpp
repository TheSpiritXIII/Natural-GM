/**
 *  @file ResourceProjectItem.hpp
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
#ifndef _NGM_RESOURCEPROJECTITEM__HPP
#define _NGM_RESOURCEPROJECTITEM__HPP
#include "ResourceGroupItem.hpp"

namespace NGM
{
	namespace Resource
	{
		class Resource;
		class Project;
	}
	namespace Model
	{
		class ResourceProjectItem : public ResourceGroupItem
		{
		public:

			/**************************************************//*!
			*	@brief Creates an item with the indicated name.
			******************************************************/
			ResourceProjectItem(NGM::Resource::Resource *resource, NGM::Resource::Project *project, const QString &name) :
				ResourceGroupItem(name), resource(resource), project(project) {}

			/**************************************************//*!
			 *	@brief The resource of the item that this item represents.
			******************************************************/
			Resource::Resource *resource;

			/**************************************************//*!
			 *	@brief The project that all resources depend on.
			******************************************************/
			Resource::Project *project;

			/**************************************************//*!
			*	@return A safe case to a ResourceProjectItem. Returns this.
			******************************************************/
			ResourceProjectItem *toResourceProjectItem()
			{
				return this;
			}
		};
	}
}

#endif // _NGM_RESOURCEPROJECTITEM__HPP
