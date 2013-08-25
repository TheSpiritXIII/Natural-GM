/**
 *  @file ResourceSplitter.cpp
 *
 *  @section License
 *
 *	  Copyright (C) 2013 Daniel Hrabovcak
 *
 *	  This file is a part of the Natural GM IDE.
 *
 *	  This program is free software: you can redistribute it and/or modify
 *	  it under the terms of the GNU General Public License as published by
 *	  the Free Software Foundation, either version 3 of the License, or
 *	  (at your option) any later version.
 *
 *	  This program is distributed in the hope that it will be useful,
 *	  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	  GNU General Public License for more details.
 *
 *	  You should have received a copy of the GNU General Public License
 *	  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include "ResourceTab.hpp"
#include "Editor.hpp"
#include "ResourceProjectItem.hpp"
#include "ResourceSplitter.hpp"
#include "WindowManager.hpp"
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
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
			setDocumentMode(true);

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

			connect(this, &ResourceTab::tabCloseRequested, this, &ResourceTab::closeTab);
		}

		Resource::Editor *ResourceTab::resourceOpen(Model::ResourceBaseItem *resource)
		{
			using NGM::Resource::Editor;
			Resource::Resource *r = resource->toResourceProjectItem()->resource;
			Editor *widget = r->type->widget(this);
			qDebug() << "No Resource found." << widget;
			if (widget != nullptr)
			{
				widget->block(true);
				resource->root()->project->serializer->read(widget, r);
				widget->block(false);
				setCurrentIndex(addTab(widget, resource->data().toString()));
				widgets.insert(std::pair<Model::ResourceBaseItem*, Resource::Editor*>(resource, widget));
				splitter->parentWidget->setWindowFilePath(tabText(currentIndex()));
				return widget;
			}
			return nullptr;
		}

		void ResourceTab::resourceSave(Resource::Editor *editor) const
		{
			for (auto &i : widgets)
			{
				if (i.second == editor)
				{
					Model::ResourceProjectItem *r = i.first->toResourceProjectItem();
					r->project->serializer->write(editor, r->resource);
					break;
				}
			}
		}

		bool ResourceTab::contains(Model::ResourceBaseItem *item)
		{
			std::map<Model::ResourceBaseItem*, Resource::Editor*>::iterator i;
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

		void ResourceTab::closeTab(int ind)
		{
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, "", "Close tab " + tabText(ind) + "?", QMessageBox::Yes|QMessageBox::No);

			if (reply == QMessageBox::Yes)
				removeTab(ind);

			/*QMessageBox message;
				//message.setText("The resource '"+resource->name+"'' has been modified.");
				message.setInformativeText("Do you want to save your changes?");
				message.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
				message.setDefaultButton(QMessageBox::Save);
				switch (message.exec())
				{
				case QMessageBox::Save:
					//saveResource(resource);
					return true;
				case QMessageBox::Discard:
					return true;
				default:
					return false;
				}*/
		}

		void ResourceTab::modifedWidget(const bool &modified)
		{
			qDebug() << modified;
			int i = indexOf(static_cast<QWidget*>(sender()));
			QString text = tabText(i);
			if (modified)
			{
				text.append('*');
			}
			else
			{
				text.chop(1);
			}
			setTabText(i, text);
			splitter->parentWidget->setWindowFilePath(tabText(currentIndex()));
		}
	}
}
