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
#include "ResourceContentItem.hpp"
#include <stdint.h>
#include <set>
#include <map>
#include <string>
#include <QDebug>

namespace NGM
{
	namespace Resource
	{
		struct Resource;
		struct Project;
	}
	namespace Model
	{
		class ResourceProjectItem : public ResourceGroupItem
		{
		public:

			enum Settings
			{
				isPreloaded		=	0x01,	// Changes the way the serializer works.
				cacheItems		=	0x02	// Caches added items by type.
			};

			/**************************************************//*!
			*	@brief Creates an item with the indicated name.
			******************************************************/
			ResourceProjectItem(NGM::Resource::Resource *resource, NGM::Resource::Project *project,
								const QString &filepath, const uint8_t &settings) :
				ResourceGroupItem("Yes"), resource(resource), project(project), settings(settings)
			{
				int split = filepath.lastIndexOf('/')+1;
				_name = filepath.right(filepath.size()-split);
				dir = filepath.left(split);
				qDebug() << dir;
			}

			const QString directory()
			{
				return dir;
			}

			/**************************************************//*!
			 *	@brief The resource of the item that this item represents.
			******************************************************/
			Resource::Resource *resource;

			/**************************************************//*!
			 *	@brief The project that all resources depend on.
			******************************************************/
			Resource::Project *project;

			/**************************************************//*!
			 *	@brief The project that all resources depend on.
			******************************************************/
			const uint8_t settings;

			/**************************************************//*!
			*	@return A safe case to a ResourceProjectItem. Returns this.
			******************************************************/
			ResourceProjectItem *toProjectItem()
			{
				return this;
			}

		private:

			std::map<std::string, std::set<ResourceContentItem*>> cache;

			QString dir;
			QString file;

		};
	}
}

#endif // _NGM_RESOURCEPROJECTITEM__HPP
