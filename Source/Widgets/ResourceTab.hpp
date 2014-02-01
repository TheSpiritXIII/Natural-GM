/**
 *  @file ResourceTab.hpp
 *  @section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
 *      Copyright (C) 2013 Joshua Spayd
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
#ifndef _NGM_RESOURCETAB__HPP
#define _NGM_RESOURCETAB__HPP
#include <QTableWidget>
#include "ResourceContentItem.hpp"
#include <map>

namespace NGM
{
	namespace Resource
	{
		class Editor;
		struct Content;
	}
	namespace Manager
	{
		class WindowManager;
	}
	namespace Widget
	{
		class ResourceSplitter;

		/**************************************************//*!
		 *	@brief	A tab widget that stores resource items.
		******************************************************/
		class ResourceTab : public QTabWidget
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			 *	@brief	Creates an empty tab with a parent.
			******************************************************/
			ResourceTab(ResourceSplitter *parent = 0);

			/**************************************************//*!
			 *	@brief	Opens the indicated resource.
			 *	@param	item The resource to open.
			******************************************************/
			Resource::Editor *resourceOpen(Model::ResourceBaseItem *item);

			/**************************************************//*!
			 *	@brief	Save the indicated resource.
			 *	@param	widget The widget to save.
			******************************************************/
			void resourceSave(Resource::Editor *editor) const;

			/**************************************************//*!
			 *	@brief	Returns the tab index to the indicated
			 *			resource, if open, otherwise -1.
			******************************************************/
			int resourceIsOpen(Model::ResourceBaseItem *resource);

			/**************************************************//*!
			*	@brief	Closes the resource if it is open.
			******************************************************/
			void resourceClose(Model::ResourceBaseItem *resource);

			/**************************************************//*!
			*	@brief	Set the tab index to the indicated index.
			*	@see	resourceIsOpen
			******************************************************/
			void resourceSwitchTo(int index);

			/**************************************************//*!
			*	@return	Whether the indicated ResourceBaseItem is
			*			open as a page on this tab.
			******************************************************/
			bool contains(Model::ResourceBaseItem *item);

			/**************************************************//*!
			*	@brief	Moves the current tab to resourceTab.
			******************************************************/
			void moveWidget(const int &index, ResourceTab *resourceTab);

			/**************************************************//*!
			*	@brief	Indicates if a tab is being dragged.
			*
			*	A tab might be being dragged by another instance
			*	of this application. This function makes confirms
			*	that it is coming from this one.
			******************************************************/
			static inline bool isDragging()
			{
				return dragWidget == nullptr;
			}

		public slots:

			/**************************************************//*!
			*	@brief	Updates the tab name.
			******************************************************/
			void modifiedWidget(const bool &modified);

			/**************************************************//*!
			*	@brief	Updates the parent on focus.
			******************************************************/
			void focused(Resource::Editor *editor);

		protected:

			/**************************************************//*!
			*	@see	end
			******************************************************/
			enum End : uint8_t
			{
				None		=	0,
				Right		=	1,
				Left		=	2
			};

			/**************************************************//*!
			*	@brief	Indicates which items to show on the
			*			context menu.
			******************************************************/
			End end;

			/**************************************************//*!
			*	@brief	Contains the widget currently being
			*			dragged or nullptr is there is none.
			******************************************************/
			static QWidget *dragWidget;

			/**************************************************//*!
			*	@brief	Creates a highlight widget.
			******************************************************/
			void dragEnterEvent(QDragEnterEvent*);

			/**************************************************//*!
			*	@brief	Destroys the highlight widget.
			******************************************************/
			void dragLeaveEvent(QDragLeaveEvent*);

			/**************************************************//*!
			*	@brief	Moves the highlight widget.
			******************************************************/
			void dragMoveEvent(QDragMoveEvent*);

			void dropEvent(QDropEvent *);

			friend class ResourceSplitter;

		private:

			/**************************************************//*!
			*	@brief	Maps a resource item to its open widget.
			******************************************************/
			std::map<Model::ResourceBaseItem*, Resource::Editor*> widgets;

			/**************************************************//*!
			*	@brief	The parent of this widget.
			******************************************************/
			ResourceSplitter *splitter;

			/**************************************************//*!
			*	@brief	Stores the index of the last clicked page.
			******************************************************/
			int rightClicked;

			friend class NGM::Manager::WindowManager;
		};
	}
}

#endif // _NGM__RESOURCETAB__HPP
