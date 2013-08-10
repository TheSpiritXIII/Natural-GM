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
#include "../Resources/Widget.hpp"
#include "ResourceProjectItem.hpp"
#include "ResourceSplitter.hpp"
#include "WindowManager.hpp"
#include <QMenu>
#include <QDebug>
using std::list;
using std::pair;

namespace NGM
{
	namespace Widget
	{
		ResourceTab::ResourceTab(ResourceSplitter *parent) : QTabWidget(parent), splitter(parent)
		{
			setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			setTabsClosable(true);
			setContentsMargins(0, 0, 0, 0);
			setContextMenuPolicy(Qt::CustomContextMenu);
			setMovable(true);

			connect(this, &ResourceTab::customContextMenuRequested, [this](const QPoint &point)
			{
				rightClicked = widget(tabBar()->tabAt(point));
				QMenu *menu = new QMenu(this);
				if (count() != 1)
				{
					if (splitter->count() == 1)
					{
						connect(menu->addAction("Split Next Horizontal"), &QAction::triggered, [this]()
						{
							this->setCurrentWidget(this->rightClicked);
							this->splitter->movePage(this->splitter, 0);
							this->splitter->setOrientation(Qt::Horizontal);
						});
						connect(menu->addAction("Split Next Vertical"), &QAction::triggered, [this]()
						{
							this->setCurrentWidget(this->rightClicked);
							this->splitter->movePage(this->splitter, 0);
							this->splitter->setOrientation(Qt::Vertical);
						});
					}
					else
					{
						connect(menu->addAction("Move to Next"), &QAction::triggered, [this]()
						{
							this->setCurrentWidget(this->rightClicked);
							this->splitter->movePage(this->splitter, ResourceSplitter::Next);
						});
						connect(menu->addAction("Move to Previous"), &QAction::triggered, [this]()
						{
							this->setCurrentWidget(this->rightClicked);
							this->splitter->movePage(this->splitter, ResourceSplitter::Prev);
						});
					}
				}
				/*menu->addSeparator();
				menu->addAction("Move Next Dialog");
				menu->addAction("Move Next Window");*/
				menu->popup(this->mapToGlobal(point));
			});
		}

		Resource::Widget *ResourceTab::resourceOpen(Model::ResourceBaseItem *resource)
		{
			using NGM::Resource::Widget;
			Resource::Resource *r = resource->toResourceProjectItem()->resource;
			Widget *widget = r->type->widget();
			if (widget != nullptr)
			{
				resource->root()->project->serializer->read(widget, r);
				setCurrentIndex(addTab(widget, resource->data().toString()));
				widgets.insert(std::pair<Model::ResourceBaseItem*, Resource::Widget*>(resource, widget));
				return widget;
			}
			return nullptr;
		}

		bool ResourceTab::contains(Model::ResourceBaseItem *item)
		{
			std::map<Model::ResourceBaseItem*, Resource::Widget*>::iterator i;
			i = widgets.find(item);
			if (i != widgets.end())
			{
				setCurrentWidget(i->second);
				return true;
			}
			return false;
		}

		void ResourceTab::changeEvent(QEvent *event)
		{
			QTabWidget::changeEvent(event);
		}
	}
}
