/**
 *  @file ResourceContentItem.hpp
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
#ifndef _NGM_RESOURCECONTENTITEM__HPP
#define _NGM_RESOURCECONTENTITEM__HPP
#include "ResourceBaseItem.hpp"
#include "Resource.hpp"

namespace NGM
{
	namespace Model
	{
		/**************************************************//*!
		*	@brief An item that stores a resource. This class
		*		   can only be used with ResourceItemModel.
		******************************************************/
		class ResourceContentItem : public ResourceBaseItem
		{
		public:

			/**************************************************//*!
			*	@brief Creates an item with the indicated name.
			******************************************************/
			ResourceContentItem(NGM::Resource::Resource *resource, const QString &name) :
				ResourceBaseItem(name), resource(resource) {}

			/**************************************************//*!
			 *	@brief The resource of the item that this item represents.
			******************************************************/
			NGM::Resource::Resource *resource;

			ResourceContentItem *toContentItem()
			{
				return this;
			}
		};
	}
}

#endif // _NGM_RESOURCEITEM__HPP
