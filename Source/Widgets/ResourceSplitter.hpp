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
#include <list>

namespace NGM
{
	namespace Manager
	{
		class WindowManager;
	}
	namespace Widget
	{
		class ResourceSplitter : public QSplitter
		{
			Q_OBJECT

		public:

			enum Settings
			{
				Move		=	0x00000000,
				Clone		=	0x00000001,
				Next		=	0x00000000,
				Prev		=	0x00000010
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
			void resourceOpen(Model::ResourceBaseItem *resource, bool active = true);

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
			 *	@brief	Adds a widget to the currently open tab.
			******************************************************/
			void movePage(ResourceSplitter *move, uint8_t settings);

			/**************************************************//*!
			 *	@brief	Requests the current widget to cut.
			******************************************************/
			void cut();

			void paste();

		private:

			/**************************************************//*!
			 *	@brief	Stores the window manager.
			******************************************************/
			Manager::WindowManager *windowManager;

			/**************************************************//*!
			 *	@brief	Stores the current active resource tab.
			******************************************************/
			ResourceTab *current;

			/**************************************************//*!
			 *	@brief	Stores all tab widgets for quick access.
			******************************************************/
			std::list<ResourceTab*> tabs;
		};
	}
}

#endif // _NGM_TABSPLITWIDGET__HPP
