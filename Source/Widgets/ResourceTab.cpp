/**
 *  @file ResourceSplitter.cpp
 *
 *  @section License
 *
 *	  Copyright (C) 2013 Daniel Hrabovcak and Joshua Spayd
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
#include "MainWindow.hpp"
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <QMimeData>
using std::list;
using std::pair;

namespace NGM
{
	namespace Widget
	{
		QWidget *ResourceTab::dragWidget = nullptr;

		ResourceTab::ResourceTab(ResourceSplitter *parent) : QTabWidget(parent), splitter(parent)
		{
			setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			setElideMode(Qt::ElideRight);
			setTabsClosable(true);
			setContentsMargins(0, 0, 0, 0);
			setContextMenuPolicy(Qt::CustomContextMenu);
			setMovable(true);
			setDocumentMode(true);
			setAcceptDrops(true);

			connect(this, &ResourceTab::currentChanged, [this](const int&)
			{
				Resource::Editor *editor = static_cast<Resource::Editor*>(currentWidget());
				if (editor != nullptr)
				{
					editor->setFocus();
				}
			});

			connect(this, &ResourceTab::customContextMenuRequested, [this](const QPoint &point)
			{
				rightClicked = tabBar()->tabAt(point);

				//Do nothing if there was no tab clicked.
				if (rightClicked == -1)
				{
					return;
				}

				Resource::Editor *editor = static_cast<Resource::Editor*>(currentWidget());
				if (editor != nullptr)
				{
					editor->setFocus();
				}

				QMenu *menu = new QMenu(this);
				if (splitter->count() == 1)
				{
					connect(menu->addAction("Split Next Horizontal"), &QAction::triggered, [this]()
					{
						splitter->movePage(rightClicked, splitter, 0);
						splitter->setOrientation(Qt::Horizontal);
					});
					connect(menu->addAction("Split Next Vertical"), &QAction::triggered, [this]()
					{
						splitter->movePage(rightClicked, splitter, 0);
						splitter->setOrientation(Qt::Vertical);
					});
					menu->addSeparator();
					connect(menu->addAction("Clone Next Horizontal"), &QAction::triggered, [this]()
					{
						splitter->movePage(rightClicked, splitter, ResourceSplitter::Clone);
					});
					//menu->addSeperator();
					//menu.addAction(tr("Move to Dialog"));
					//menu->addSeparator()
					//menu.addAction(tr("Move to Window"));
				}
				else
				{
					qDebug() << end;
					qDebug() << count();
					if (end != Right || count() != 1)
					{
						connect(menu->addAction("Move to Next"), &QAction::triggered, [this]()
						{
							splitter->movePage(rightClicked, splitter);
						});
					}
					if (end != Left || count() != 1)
					{
						connect(menu->addAction("Move to Previous"), &QAction::triggered, [this]()
						{
							splitter->movePage(rightClicked, splitter, ResourceSplitter::Previous);
						});
					}
					menu->addSeparator();
					connect(menu->addAction("Clone to Next"), &QAction::triggered, [this]()
					{
						splitter->movePage(rightClicked, splitter, ResourceSplitter::Clone);
					});
				}
				/*menu->addSeparator();
				//menu->addAction("Move Next Dialog");
				connect(menu->addAction(tr("Move to Window")), &QAction::triggered, [this]()
				{
					MainWindow* win = splitter->windowManager->addWindow();
					for (auto &i : widgets)
					{
						if (i.second == rightClicked)
						{
							Model::ResourceBaseItem* item = i.first;
							win->resourceSplitter->resourceOpen(item);
							removeTab(indexOf(rightClicked));
						}
					}
				});*/
				menu->popup(mapToGlobal(point));
			});

			connect(this, &ResourceTab::tabCloseRequested, [this](int index)
			{
				QWidget *w = widget(index);
				Resource::Editor *editor = static_cast<Resource::Editor*>(w);
				qDebug() << editor;
				if (editor != nullptr)
				{
					auto i = widgets.begin();
					Model::ResourceBaseItem *item;
					for(; i != widgets.end(); ++i)
					{
						if (i->second == editor)
						{
							item = i->first;
							break;
						}
					}
					qDebug() << (editor->getState());
					if (editor->getState() & Resource::Editor::IsModified)
					{
						Model::ResourceProjectItem *projectItem = item->toProjectItem();

						QMessageBox message;
						message.setIcon(QMessageBox::Question);
						message.setText("The resource \"" + item->name() + "\" has been modified.");
						message.setInformativeText("Do you want to save your changes?");
						message.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
						message.setDefaultButton(QMessageBox::Yes);

						switch (message.exec())
						{
						case QMessageBox::Yes:
							if (projectItem != nullptr)
							{
								projectItem->project->serializer->write(editor, projectItem->resource);
							}
							else
							{
								Model::ResourceContentItem *contentItem = item->toContentItem();
								contentItem->root()->project->serializer->write(editor, contentItem->resource);
							}
							break;
						case QMessageBox::No:
							break;
						default:
							return;
						}
					}
					if (count() == 1)
					{
						splitter->resetState();
						deleteLater();
					}
					widgets.erase(i);
				}
				removeTab(index);
				w->deleteLater();
			});
		}

		Resource::Editor *ResourceTab::resourceOpen(Model::ResourceBaseItem *item)
		{
			Model::ResourceProjectItem *project = item->toProjectItem();
			Resource::Resource *resource = (project == nullptr ? item->toContentItem()->resource : project->resource);

			if (project == nullptr)
			{
				project = item->toContentItem()->root();
			}

			Resource::Editor *widget = resource->type->create(project, this);

			if (widget != nullptr)
			{
				const Resource::Serializer *serializer = project->project->serializer;
				if (serializer->settings & Resource::Serializer::SetWorkingDir)
				{
					QDir::setCurrent(project->directory());
				}
				serializer->read(widget, resource);
				widget->initialize();

				setCurrentIndex(addTab(widget, item->name()));
				widgets.insert(std::pair<Model::ResourceBaseItem*, Resource::Editor*>(item, widget));
				return widget;
			}
			return nullptr;
		}

		void ResourceTab::resourceSave(Resource::Editor *editor) const
		{
			qDebug() << "TEST 1";
			qDebug() << widgets.size();
			for (auto &i : widgets)
			{
				if (i.second == editor)
				{
					Model::ResourceProjectItem *project = i.first->toProjectItem();
					if (project == nullptr)
					{
						Model::ResourceContentItem *item = i.first->toContentItem();
						item->root()->project->serializer->write(editor, item->resource);
					}
					else
					{
						project->project->serializer->write(editor, project->resource);
					}
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

		void ResourceTab::focused(Resource::Editor *editor)
		{
			splitter->current = this;
			splitter->focusWidget(editor);
		}

		void ResourceTab::modifiedWidget(const bool &modified)
		{
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

		void ResourceTab::moveWidget(const int &index, ResourceTab *resourceTab)
		{
			QWidget *w = widget(index);
			QString t = tabText(index);
			removeTab(index);
			//resourceTab->addTab(w, t);

			Resource::Editor *editor = static_cast<Resource::Editor*>(w);
			if (editor != nullptr)
			{
				editor->resourceTab = resourceTab;
				for (auto &i : this->widgets)
				{
					if (i.second == editor)
					{
						resourceTab->widgets.insert(i);
						widgets.erase(i.first);
						break;
					}
				}
				resourceTab->setCurrentIndex(resourceTab->addTab(w, t));
			}
			else
			{
				resourceTab->setCurrentIndex(resourceTab->addTab(w, t));
			}

			if (count() == 0)
			{
				deleteLater();
			}
		}

		void ResourceTab::dragEnterEvent(QDragEnterEvent *event)
		{
			if (event->mimeData()->hasFormat("natural-gm/tab-detach") &&
				ResourceSplitter::dragTab == nullptr &&
				ResourceSplitter::highlightWidget == nullptr)
			{
				qDebug() << "ENTERED";
				ResourceSplitter::highlightWidget = new HighlightWidget(splitter->parentWidget);
				ResourceSplitter::highlightWidget->show();
				dragMoveEvent(event);
				event->setDropAction(Qt::MoveAction);
				event->accept();
			}
		}

		void ResourceTab::dragLeaveEvent(QDragLeaveEvent *event)
		{
			delete ResourceSplitter::highlightWidget;
			ResourceSplitter::highlightWidget = nullptr;
		}

		void ResourceTab::dragMoveEvent(QDragMoveEvent *event)
		{
			int halfSize;
			QPoint mappedPosition = mapTo(splitter->parentWidget, pos());

			// Calculate orientation, if necessary.
			if (splitter->count() == 1)
			{
				Qt::Orientation oldOrientation = splitter->orientation();
				int distanceX = abs(width()/2-event->pos().x());
				int distanceY = abs(height()/2-event->pos().y());
				if (distanceX+distanceY > 64)
				{
					if (distanceX > distanceY)
					{
						if (oldOrientation != Qt::Horizontal)
						{
							halfSize = width()/2;

							// Probably glitch.
							mappedPosition.setX(mappedPosition.x()-pos().x());

							splitter->setOrientation(Qt::Horizontal);
							ResourceSplitter::highlightWidget->setGeometry(mappedPosition.x(),
								mappedPosition.y()+tabBar()->height(), halfSize, height()-tabBar()->height());
							return;
						}
					}
					else
					{
						if (oldOrientation != Qt::Vertical)
						{
							halfSize = (height()-tabBar()->height())/2;

							// Probably glitch.
							mappedPosition.setY(mappedPosition.y()-pos().y());

							splitter->setOrientation(Qt::Vertical);
							ResourceSplitter::highlightWidget->setGeometry(mappedPosition.x()+halfSize,
								mappedPosition.y()+tabBar()->height(), halfSize, height()-tabBar()->height());
							return;
						}
					}
				}
			}

			if (splitter->orientation() == Qt::Horizontal)
			{
				halfSize = width()/2;

				// Probably glitch.
				mappedPosition.setX(mappedPosition.x()-pos().x());

				if (event->pos().x() < halfSize)
				{
					if (ResourceSplitter::highlightWidget->x() != mappedPosition.x())
					{
						ResourceSplitter::highlightWidget->setGeometry(mappedPosition.x(),
							mappedPosition.y()+tabBar()->height(), halfSize, height()-tabBar()->height());
					}
				}
				else if (ResourceSplitter::highlightWidget->x() != mappedPosition.x()+halfSize)
				{
					ResourceSplitter::highlightWidget->setGeometry(mappedPosition.x()+halfSize,
						mappedPosition.y()+tabBar()->height(), halfSize, height()-tabBar()->height());
				}
			}
			else
			{
				halfSize = (height()-tabBar()->height())/2;

				// Probably glitch.
				mappedPosition.setY(mappedPosition.y()-pos().y());

				if (event->pos().y() < halfSize+tabBar()->height())
				{
					if (ResourceSplitter::highlightWidget->y() != mappedPosition.y())
					{
						ResourceSplitter::highlightWidget->setGeometry(mappedPosition.x(),
							mappedPosition.y()+tabBar()->height(), width(), halfSize);
					}
				}
				else if (ResourceSplitter::highlightWidget->y() != mappedPosition.y()+halfSize)
				{
					ResourceSplitter::highlightWidget->setGeometry(mappedPosition.x(),
						mappedPosition.y()+halfSize+tabBar()->height(), width(), halfSize);
				}
			}
			event->accept();
		}

		void ResourceTab::dropEvent(QDropEvent *event)
		{
			delete ResourceSplitter::highlightWidget;
			ResourceSplitter::highlightWidget = nullptr;
		}
	}
}
