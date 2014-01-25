/**
 *  @file Serializer.hpp
 *	@section License
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
#ifndef NGM__SERIALIZER__HPP
#define NGM__SERIALIZER__HPP
#include "ResourceProjectItem.hpp"
#include "Variant.hpp"
#include <QProgressBar>
#include <QString>
#include <cstdint>

namespace NGM
{
	namespace Manager
	{
		class ProjectManager;
	}
	namespace Resource
	{
		class Editor;

		typedef uint8_t SerializerOptions;
		typedef uint8_t SerializerSettings;

		/**************************************************//*!
		*	@brief	Loads, creates and saves projects and
		*			files contained in projects.
		*
		* When any of the main loading function are called,
		* the status bar of all windows changes to display
		* a progress bar and a text label which can be
		* changed using setProgressText(), setProgressMax()
		* and setProgressValue(). These functions push
		* to an event queue in the main application, so
		* their data might not show up right away. Old
		* messages may even be discarded.
		******************************************************/
		struct Serializer
		{

			/**************************************************//*!
			*	@brief	Flags for serializer settings.
			******************************************************/
			enum Settings
			{
				// Requests the serializer to call save after write.
				ResaveAll	=	0x01,
				// Allows the user to move and rename root structures.
				CanModifyRoots	=	0x02,
				// Sorts items except roots automatically. They cannot be moved.
				AutoSortItems	=	0x04,
				// Does not let the user move items, even if not sorted.
				NonMovableItems	=	0x08,
				// Requests the serializer to set the working directory before read.
				SetWorkingDir	=	0x10
			};

			/**************************************************//*!
			*	@brief	Options for reading and writing data.
			******************************************************/
			enum Options
			{
				DynamicIcons	=	0x01
			};

			/**************************************************//*!
			*	@brief	Sets the indicated settings.
			******************************************************/
			Serializer(const SerializerSettings &settings = 0);

			/// DEPRECATED
			virtual void read(Editor *editor, Resource *resource, const SerializerOptions &options = 0) const = 0;

			/// DEPRECATED
			virtual void write(Editor *editor, Resource *resource, const SerializerOptions &options = 0) const = 0;

			/// DEPRECATED
			virtual bool structure(Model::ResourceProjectItem *item,
				const Manager::ProjectManager *projectManager,
				QProgressBar *progressBar) const = 0;

			/// DEPRECATED
			virtual void restructure(Model::ResourceProjectItem *item) const = 0;

			/**************************************************//*!
			*	@brief	Determines how the project is structured.
			*	@see	Settings
			******************************************************/
			const SerializerSettings settings;

		protected:

			/**************************************************//*!
			*	@brief	Sets the display text of the progress bar
			*			that shows up in the status bar.
			******************************************************/
			void setProgressText(const QString &text) const;

			/**************************************************//*!
			*	@brief	Sets the value of the progress bar that
			*			shows up in the status bar. This must be
			*			between 0 and the max value.
			*	@see	setProgressMax()
			******************************************************/
			void setProgressValue(int value) const;

			/**************************************************//*!
			*	@brief	Sets the max value of the progress bar
			*			that shows up in the status bar. Ideally,
			*			this is called first.
			*	@see	setProgressValue()
			******************************************************/
			void setProgressMax(int value) const;

			/**************************************************//*!
			*	@brief	Queues the main thread to delete the item
			*			at the indicated row of the parent. To be
			*			used only be layoutReload().
			*	@param	count The amount of items starting at row
			*			to remove. Using this improves
			*			performance.
			******************************************************/
			void removeItem(const Model::ResourceGroupItem *parent, int row,
				int count = 1) const;

			/**************************************************//*!
			*	@brief	Queues the main thread to insert the
			*			indicated items. To be used only by
			*			layoutReload().
			*	@param	count The number of items to add.
			******************************************************/
			void insertItem(Model::ResourceBaseItem *item,
				const Model::ResourceGroupItem *parent, int row,
				int count = 1) const;

			/// TODO
			virtual void layoutCreate(Model::ResourceProjectItem *item) const;

			/// TODO
			virtual void layoutLoad(Model::ResourceProjectItem *item) const;

			/// TODO
			virtual void layoutSave(Model::ResourceProjectItem *item) const;

			/// TODO
			virtual void layoutReload(
					const Model::ResourceProjectItem *item) const;

			/*resourceOpen();
			resourceSave();

			Application Manager needs:
			- Project load begin signal.
			- Project load finished signal.
			*/
		};
	}
}

#endif // _NGM_SERIALIZER__HPP
