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
#include "ResourceSplitter.hpp"
#include "WindowManager.hpp"
#include <QDebug>
#include <QLabel>
#include "Widget.hpp"
#include <QDebug>

namespace NGM
{
	namespace Widget
	{
		ResourceSplitter::ResourceSplitter(Manager::WindowManager *windowManager, QWidget *parent) :
			QSplitter(parent), windowManager(windowManager)
		{
			setChildrenCollapsible(false);
		}

		void ResourceSplitter::resourceOpen(Model::ResourceBaseItem *resource, bool active)
		{
			if (count() == 0 || active == false)
			{
				ResourceTab *tab = new ResourceTab(this);
				Resource::Widget *widget = tab->resourceOpen(resource);
				widget->connect(widget, &Resource::Widget::canCopy, [this](const bool &value)
				{
					this->windowManager->canCopy(value);
				});
				widget->connect(widget, &Resource::Widget::canPaste, [this](const bool &value)
				{
					qDebug() << "PASTING.";
					this->windowManager->canPaste(value);
				});
				addWidget(tab);
				current	= tab;
				tabs.push_back(current);
			}
			else
			{
				for (ResourceTab *i : tabs)
				{
					if (i->contains(resource))
					{
						return;
					}
				}
				current->resourceOpen(resource);
			}
		}

		void ResourceSplitter::movePage(ResourceSplitter *move, uint8_t settings)
		{
			if (move == this)
			{
				if (!(settings & Prev))
				{
					std::list<ResourceTab*>::iterator i;
					for (i = tabs.begin(); i != tabs.end(); ++i)
					{
						if ((*i) == current)
						{
							++i;
							break;
						}
					}
					if (i == tabs.end())
					{
						ResourceTab *tab = new ResourceTab(this);
						addWidget(tab);

						QWidget *widget = current->currentWidget();
						QString text = current->tabText(current->currentIndex());
						current->removeTab(current->currentIndex());
						tab->addTab(widget, text);

						if (current->count() == 0)
						{
							tabs.remove((*i));
							current->deleteLater();
						}

						current	= tab;
						tabs.push_back(current);
					}
					else
					{
						QWidget *widget = current->currentWidget();
						QString text = current->tabText(current->currentIndex());
						current->removeTab(current->currentIndex());

						if (current->count() == 0)
						{
							tabs.remove((*i));
							current->deleteLater();
						}

						(*i)->addTab(widget, text);
						current = (*i);
					}
				}
				else
				{

				}
			}
			//if (count() == 0)
			//move->current->currentWidget()
		}

		void ResourceSplitter::cut()
		{
			Resource::Widget *widget = static_cast<Resource::Widget*>(current->currentWidget());
			widget->cutRequest();
		}

		void ResourceSplitter::paste()
		{
			Resource::Widget *widget = static_cast<Resource::Widget*>(current->currentWidget());
			widget->pasteRequest();
		}
	}
}
