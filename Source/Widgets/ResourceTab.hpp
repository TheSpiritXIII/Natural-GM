/**
 *  @file ResourceTab.hpp
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
#ifndef _NGM_RESOURCETAB__HPP
#define _NGM_RESOURCETAB__HPP
#include <QTableWidget>
#include "ResourceContentItem.hpp"
#include <map>

namespace NGM
{
	namespace Resource
	{
		class Widget;
		class Resource;
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
			 *	@param	resource The resource to open.
			******************************************************/
			Resource::Widget *resourceOpen(Model::ResourceBaseItem *resource);

			/**************************************************//*!
			 *	@brief	Save the indicated resource.
			 *	@param	widget The widget to save.
			******************************************************/
			void resourceSave(Resource::Widget *widget) const;

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
			 *	@brief	Closes the requested tab.
			******************************************************/
			void closeTab(int ind);

		public slots:

			/**************************************************//*!
			*	@brief	Updates the tab name.
			******************************************************/
			void modifedWidget(const bool &modified);

		protected:

			/**************************************************//*!
			*	@brief	Updates the parent on focus.
			******************************************************/
			void changeEvent(QEvent *event);

		private:

			/**************************************************//*!
			 *	@brief	Maps a resource item to its open widget.
			******************************************************/
			std::map<Model::ResourceBaseItem*, Resource::Widget*> widgets;

			/**************************************************//*!
			 *	@brief	The parent of this widget.
			******************************************************/
			ResourceSplitter *splitter;

			/**************************************************//*!
			 *	@brief	Holds the widget of the last clicked page.
			******************************************************/
			QWidget *rightClicked;
		};
	}
}

#endif // _NGM__RESOURCETAB__HPP
