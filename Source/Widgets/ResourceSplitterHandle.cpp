/**
 *	@file ResourceSpliterHandle.cpp
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
#include "ResourceTab.hpp"
#include "ResourceSplitterHandle.hpp"
#include "ResourceSplitter.hpp"
#include <QDragEnterEvent>
#include <QApplication>
#include <QMimeData>
#include <QDebug>

namespace NGM
{
	namespace Widget
	{
		ResourceSplitterHandle::ResourceSplitterHandle(Qt::Orientation o,
			ResourceSplitter *parent) : QSplitterHandle(o, parent)
		{
			setAcceptDrops(true);
		}

		void ResourceSplitterHandle::dragEnterEvent(QDragEnterEvent *event)
		{
			if (event->mimeData()->hasFormat("natural-gm/tab-detach") && ResourceTab::isDragging())
			{
				setPalette(QPalette(QApplication::palette().highlight().color()));
				event->accept();
			}
		}

		void ResourceSplitterHandle::dragLeaveEvent(QDragLeaveEvent *event)
		{
			qDebug() << "Drag Left";
			setPalette(style()->standardPalette());
		}

		void ResourceSplitterHandle::dropEvent(QDropEvent *event)
		{
			ResourceSplitter *resourceSplitter = static_cast<ResourceSplitter*>(splitter());

		}
	}
}
