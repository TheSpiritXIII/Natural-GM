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
#include "Resource.hpp"

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
		*
		* The file path is optional because there may not be
		* a file path or the file path is not a system path.
		* A system path might be helpful to a serializer. For
		* example, a zip path can be stored that way (because
		* zip files are not exactly system paths). For this
		* reason, a boolean exists to test whether or not
		* the file path was meant to be a system path.
		******************************************************/
		class ResourceContentItem : public ResourceBaseItem
		{
		public:

			/**************************************************//*!
			*	@brief	Hints for how the user interacts with
			*			this item.
			******************************************************/
			enum Setting
			{
				IsSystemPath	=	0x1,	/*!< Hints that the file path
												should be a real path. */
				NoExtension		=	0x2		/*!< Omits the extension when
												setting a file path. */
			};

			/**************************************************//*!
			*	@brief	Creates an item with the indicated name.
			******************************************************/
			ResourceContentItem(NGM::Resource::Resource *resource,
				const QString &filepath, ResourceSettings settings = 0);

			/**************************************************//*!
			*	@brief	Sets the internal filepath and updates
			*			the item display text.
			******************************************************/
			void setFilepath(const QString &filepath);

			/// INCOMPLETE
			NGM::Resource::Resource *resource;

			/**************************************************//*!
			*	@brief	A safe cast to this.
			******************************************************/
			ResourceContentItem *toContentItem();

		private:

			/**************************************************//*!
			*	@brief	Stores a filepath.
			******************************************************/
			QString _filepath;

			/**************************************************//*!
			*	@brief	Resource display hints.
			******************************************************/
			ResourceSettings _settings;
		};
	}
}

#endif // NGM__RESOURCEITEM__HPP
