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

/*
- For creating new resources:
Resource name type.
Resource display name.
Insert group to.
*/

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
		* messages may even be discarded. If the functions
		* are fast enough (like layoutCreate() will probably
		* be), then showing messages is not necessary.
		******************************************************/
		struct Serializer
		{

			/**************************************************//*!
			*	@brief	Flags for serializer settings.
			******************************************************/
			enum Option
			{
				ResaveAll		=	0x01,	/*!< Resave the whole project
												whenever a resource save is
												requested. */
				NoDuplicates	=	0x02,	/*!< Disallows duplicate naming when
												an item is renamed. All items
												are checked against
												duplicates. */
				NoSortSubItems	=	0x04,	/*!< Sets the NoSort flag on the
												project item, making sub items
												not sorted. */
				SetWorkingDir	=	0x08	/*!< Hints that the working
												directory should be set to the
												project directory before saving
												resources. */
			};

			/**************************************************//*!
			*	@brief	Sets the indicated settings.
			******************************************************/
			Serializer(const SerializerOptions &settings = 0);

			/// DEPRECATED
			virtual void read(Editor *editor, Content *resource, const SerializerOptions &options = 0) const = 0;

			/// DEPRECATED
			virtual void write(Editor *editor, Content *resource, const SerializerOptions &options = 0) const = 0;

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
			const SerializerOptions settings;

			/// TODO
			virtual void layoutCreate(Model::ResourceProjectItem *item) const;

			/// TODO
			virtual void layoutLoad(Model::ResourceProjectItem *item) const;

			/// TODO
			virtual void layoutSave(Model::ResourceProjectItem *item) const;

			/// TODO
			virtual void layoutReload(
					const Model::ResourceProjectItem *item) const;

			/// TODO
			//virtual void resourceRenamed() const;

			/// TODO
			//virtual void resourceCreate() const;

			//virtual void resource

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
			*			that shows up in the status bar. This
			*			must be called first if you intend to use
			*			the other progress functions.
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
