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
		struct Content;
		struct Project;
	}
	namespace Model
	{
		/**************************************************//*!
		*	@brief	An item that stores both children and
		*			project metadata.
		*
		* As this item requires a filepath, it is recommended
		* not to use ProjectBaseItem::setText(), as this will
		* cause confusion to users. Instead, use
		* setFilepath().
		******************************************************/
		class ResourceProjectItem final : public ResourceGroupItem
		{
		public:

			/**************************************************//*!
			*	@brief	TODO
			******************************************************/
			ResourceProjectItem(NGM::Resource::Content *resource,
				const Resource::Project *project, const QString &filepath,
				ResourceItemFlags settings);

			/**************************************************//*!
			*	@brief	Returns a safe case to a this.
			******************************************************/
			ResourceProjectItem *toProjectItem();

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
			*			the item display text. The existance of
			*			the file is not checked for.
			******************************************************/
			void setFilepath(const QString &filepath);

			/**************************************************//*!
			*	@brief	Updates the file and display text. The
			*			existance of the file is not checked for.
			******************************************************/
			void setFilename(const QString &filename);

			/**************************************************//*!
			*	@brief	Sets the item's modification flag. If the
			*			item is modified, an asterisk appears at
			*			the end of the display text.
			******************************************************/
			void setModified(bool modified);

			/**************************************************//*!
			*	@brief	Returns the contained project metadata.
			******************************************************/
			inline const Resource::Project *project() const
			{
				return _project;
			}

			/**************************************************//*!
			*	@brief	Stores the actual resource content data.
			******************************************************/
			Resource::Content *resource;

		private:

			/**************************************************//*!
			*	@brief	Updates the display text based on the
			*			filename and modified flag.
			******************************************************/
			void updateText();

			/**************************************************//*!
			*	@brief	Stores the project metadata.
			******************************************************/
			const Resource::Project *_project;

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
		};
	}
}

#endif // NGM__RESOURCEPROJECTITEM__HPP
