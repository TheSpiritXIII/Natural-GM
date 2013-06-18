/**
 *  @file ResourceItem.hpp
 *  @brief Declares an item that holds a resource.
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
#pragma once
#ifndef _NGM_RESOURCEITEM__HPP
#define _NGM_RESOURCEITEM__HPP
#include <BasicItem.hpp>

namespace NGM
{
	namespace Resource
	{
		class Base;
	}
	namespace Model
	{
		class ResourceItem : public BasicItem
		{
		public:

			/*! Stores the resource. */
			NGM::Resource::Base *resource;

			/*! Creates an item with a name and an attributed resource. */
			ResourceItem(NGM::Resource::Base *resource, const QString &data);

			/*! Remove and deallocate the stored resource. */
			virtual ~ResourceItem();
		};
	}
}

#endif // _NGM_RESOURCEITEM__HPP
