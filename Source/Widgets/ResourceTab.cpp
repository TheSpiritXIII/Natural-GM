/**
 *  @file ResourceSplitter.cpp
 *
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
#include "ResourceTab.hpp"
#include "Resources/Widget.hpp"
#include "ResourceProjectItem.hpp"
#include <QDebug>

namespace NGM
{
	namespace Widget
	{
		ResourceTab::ResourceTab(QWidget *parent) : QTabWidget(parent)
		{
			setTabsClosable(true);
			setContentsMargins(0, 0, 0, 0);
			//setDocumentMode(true);
		}

		void ResourceTab::resourceOpen(Model::ResourceBaseItem *resource)
		{
			using NGM::Resource::Widget;
			Resource::Resource *r = resource->toResourceProjectItem()->resource;
			qDebug() << r->type;
			Widget *widget = r->type->widget();
			if (widget != NULL)
			{
				resource->root()->project->serializer->read(widget, r);
				setCurrentIndex(addTab(widget, resource->data().toString()));
			}
		}
	}
}
