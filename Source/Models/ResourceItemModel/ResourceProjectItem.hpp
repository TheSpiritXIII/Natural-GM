/**
 *  @file ResourceProjectItem.hpp
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
#ifndef NGM__RESOURCEPROJECTITEM__HPP
#define NGM__RESOURCEPROJECTITEM__HPP
#include "ResourceGroupItem.hpp"

// TODO: Maybe move resource and project type to private and make const?

namespace NGM
{
	namespace Resource
	{
		struct Resource;
		struct Project;
	}
	namespace Model
	{
		/**************************************************//*!
		*	@see	ResourceProjectItem::Setting
		******************************************************/
		typedef uint8_t ProjectSettings;

		/**************************************************//*!
		*	@brief	An item that stores both children and
		*			project metadata.
		*
		* As this item requires a filepath, it is recommended
		* not to use ProjectBaseItem::setText(), as this will
		* cause confusion. Instead, use setFilepath().
		******************************************************/
		class ResourceProjectItem final : public ResourceGroupItem
		{
		public:

			/// DEPRECATED.
			enum Settings
			{
				isPreloaded		=	0x01,	// Changes the way the serializer works.
				cacheItems		=	0x02	// Caches added items by type.
			};

			/**************************************************//*!
			*	@brief	Settings that change the way that the
			*			users is able to interact with items.
			******************************************************/
			enum Setting
			{
				Temporary		=	0x01,	/*!< Denotes that the project is
												temporary and as such, be cached
												wherever possible. */
				NoDuplicates	=	0x02,	/*!< Disallows duplicate naming when
												a project is renamed. All items
												are checked. */
				NoSubDuplicates	=	0x06,	/*!< Disallows duplicate naming when
												a project is renamed. Only the
												current subcategory is
												checked. */
				AllowSubMoving	=	0x08,	/*!< Allows the user to move items
												only in their containing sub
												categories. */
				AllowMoving		=	0x18,	/*!< Allows the user to move items
												around in the tree. */
				NoStaticSubCat	=	0x20,	/*!< Indicates that the sub
												categories are not static, and
												can be moved. This flag also
												allows sub categories to be
												renamed. */
				CreateGroups	=	0x40	/*!< Allows the user to create
												groups, where they are able
												to move their items. */
			};

			/// DEPRECATED
			ResourceProjectItem(NGM::Resource::Resource *resource,
				NGM::Resource::Project *project, const QString &filepath,
				ProjectSettings settings);

			/**************************************************//*!
			*	@brief	Returns the directory that this item is
			*			stored in.
			******************************************************/
			inline const QString directory() const
			{
				return _directory;
			}

			/**************************************************//*!
			*	@brief	Returns the file name. This is also the
			*			display name.
			******************************************************/
			inline const QString filename() const
			{
				return _filename;
			}

			/**************************************************//*!
			*	@brief	Changes the internal filepath and updates
			*			the item display text.
			******************************************************/
			void setFilepath(const QString filepath);

			/// INCOMPLETE
			Resource::Resource *resource;

			/// INCOMPLETE
			Resource::Project *project;

			/**************************************************//*!
			*	@brief	Returns a safe case to a this.
			******************************************************/
			ResourceProjectItem *toProjectItem();

		private:

			/**************************************************//*!
			*	@brief	Contains the directory that the project
			*			is stored in.
			******************************************************/
			QString _directory;

			/**************************************************//*!
			*	@brief	Contains the filename.
			*	@see	_directory
			******************************************************/
			QString _filename;

			/**************************************************//*!
			*	@brief	Project interaction hints.
			******************************************************/
			ProjectSettings _settings;
		};
	}
}

#endif // NGM__RESOURCEPROJECTITEM__HPP
