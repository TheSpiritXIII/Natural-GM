/**
 *	@file ResourceSpliterHandle.hpp
 *	@section License
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
#ifndef _NGM_RESOURCESPLITTERHANDLE_HPP__
#define _NGM_RESOURCESPLITTERHANDLE_HPP__
#include <QSplitterHandle>

namespace NGM
{
	namespace Widget
	{
		class ResourceSplitter;

		/**************************************************//*!
		*	@brief	A splitter handle type for ResourceSplitter.
		*
		*	Provides drag/drop based capabilities. Displays a
		*	highlight when can drop and sends its splitter a
		*	message when a drop is completed.
		******************************************************/
		class ResourceSplitterHandle : public QSplitterHandle
		{
		public:

			/**************************************************//*!
			*	@brief	Creates a splitter handle with the given
			*			orientation and parent.
			******************************************************/
			ResourceSplitterHandle(Qt::Orientation, ResourceSplitter *parent);

		protected:

			/**************************************************//*!
			*	@brief	Highlights the widget when a preferrable
			*			drop is given.
			******************************************************/
			void dragEnterEvent(QDragEnterEvent*);

			/**************************************************//*!
			*	@brief	Dehighlights the widget.
			*	@see dragEnterEvent
			******************************************************/
			void dragLeaveEvent(QDragLeaveEvent*);

			/**************************************************//*!
			*	@brief	Tells the splitter parent to create a new
			*			tab widget at the current position.
			******************************************************/
			void dropEvent(QDropEvent*);

		};
	}
}

#endif // _NGM_RESOURCESPLITTERHANDLE_HPP__
