/**
 *  @file ResourceSplitter.hpp
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
#ifndef _NGM_TABSPLITWIDGET__HPP
#define _NGM_TABSPLITWIDGET__HPP
#include <QSplitter>
#include "ResourceTab.hpp"
#include "ResourceContentItem.hpp"
#include "ResourceSplitterHandle.hpp"
#include "HighlightWidget.hpp"
#include <deque>

namespace NGM
{
	namespace Manager
	{
		class WindowManager;
	}
	class MainWindow;

	namespace Widget
	{
		class ResourceSplitter : public QSplitter
		{
			Q_OBJECT

		public:

			enum Settings
			{
				Previous	=	0x01,
				Clone		=	0x02
			};

			/**************************************************//*!
			 *	@brief	Creates an empty splitter.
			******************************************************/
			ResourceSplitter(Manager::WindowManager *windowManager, QWidget *parent = 0);

			/**************************************************//*!
			 *	@brief	Opens the indicated resource.
			 *	@param	resource The resource to add.
			 *	@param	active True to add to the current tab, or
			 *	false to add as a new tab.
			******************************************************/
			void resourceOpen(Model::ResourceBaseItem *resource, const bool &active = true);

			/**************************************************//*!
			 *	@brief	Returns the tab index to the indicated
			 *			resource, if open, otherwise -1.
			******************************************************/
			int resourceIsOpen(Model::ResourceBaseItem *resource) const;

			/**************************************************//*!
			 *	@brief	Requests to reset the window manager state.
			******************************************************/
			void resetState();

			/**************************************************//*!
			 *	@brief	Set the tab index to the indicated index.
			 *	@see	resourceIsOpen
			******************************************************/
			void resourceSwitchTo(int index);

			/**************************************************//*!
			 *	@brief	Moves the currently opened tab to the
			 *			indicated splitter.
			 *	@param	index The tab index to move.
			 *	@param	splitter The splitter to move to.
			 *	@see	Settings
			******************************************************/
			void movePage(const int &index, ResourceSplitter *splitter, const uint8_t settings = false);

			/**************************************************//*!
			*	@brief	Assigns
			******************************************************/
			void focusWidget(Resource::Editor *editor);

			/**************************************************//*!
			*	@brief	Stores the parent widget.
			******************************************************/
			QWidget *const parentWidget;

			/**************************************************//*!
			*	@brief	Stores the window manager.
			******************************************************/
			Manager::WindowManager *windowManager;

		protected:

			/**************************************************//*!
			*	@brief	Creates a handle with drag/drop capabilities.
			******************************************************/
			QSplitterHandle *createHandle();

			void dragEnterEvent(QDragEnterEvent*);

			void dragLeaveEvent(QDragLeaveEvent*);

			void dropEvent(QDropEvent*);

			/**************************************************//*!
			*	@brief	Stores the current active resource tab.
			******************************************************/
			ResourceTab *current;

			/**************************************************//*!
			*	@brief	Caches the currently focused editor.
			******************************************************/
			Resource::Editor *focusedEditor;

			/**************************************************//*!
			*	@brief	The tab being dragged or nullptr.
			******************************************************/
			static QTabBar *dragTab;

			/**************************************************//*!
			*	@brief	Highlights on drag event.
			******************************************************/
			static HighlightWidget *highlightWidget;

			friend class ResourceTab;

		private:

			/**************************************************//*!
			*	@brief	The next consecutive tab relative to the
			*			indicated tab.
			*	@param	prev True to return the next consecutive
			*			tab.
			******************************************************/
			ResourceTab *nextResourceTab(const bool &prev);

			/**************************************************//*!
			*	@brief	Stores all tab widgets for quick access.
			******************************************************/
			std::deque<ResourceTab*> tabs;
		};
	}
}

#endif // _NGM_TABSPLITWIDGET__HPP
