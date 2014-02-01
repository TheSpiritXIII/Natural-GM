/**
 *  @file ResourceContentItem.hpp
 *  @section License
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
#ifndef NGM__RESOURCECONTENTITEM__HPP
#define NGM__RESOURCECONTENTITEM__HPP
#include "ResourceBaseItem.hpp"
#include "Content.hpp"

namespace NGM
{
	namespace Model
	{
		/**************************************************//*!
		*	@see	ResourceContentItem::Setting
		******************************************************/
		typedef uint8_t ResourceSettings;

		/**************************************************//*!
		*	@brief	An item that stores a resource and an
		*			optional file path.
		******************************************************/
		class ResourceContentItem : public ResourceBaseItem
		{
		public:

			/**************************************************//*!
			*	@brief	Creates an item. The item text is updated
			*			to match the resource filename
			******************************************************/
			ResourceContentItem(NGM::Resource::Content *content,
								ResourceItemFlags = IsSorted,
								ResourceGroupItem *container = nullptr);

			/**************************************************//*!
			*	@brief	Creates an item with the indicated item
			*			text and settings.
			******************************************************/
			ResourceContentItem(NGM::Resource::Content *content,
				const QString &text, ResourceItemFlags = IsSorted,
				ResourceGroupItem *container = nullptr);

			/**************************************************//*!
			*	@brief	A safe cast to this.
			******************************************************/
			ResourceContentItem *toContentItem();

			/**************************************************//*!
			*	@brief	Sets the resource filepath and updates
			*			the item display text.
			******************************************************/
			void setFilepath(const QString &filepath);

			/**************************************************//*!
			*	@brief	Updates the items text based on the
			*			resource filename.
			******************************************************/
			void updateText();

			/**************************************************//*!
			*	@brief	Stores the actual content data.
			******************************************************/
			NGM::Resource::Content *content;
		};
	}
}

#endif // NGM__RESOURCEITEM__HPP
