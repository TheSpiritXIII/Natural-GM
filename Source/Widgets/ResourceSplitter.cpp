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
#include "Editor.hpp"
#include <QMimeData>
#include "TextEditor.hpp"
#include "Factory.hpp"

namespace NGM
{
	namespace Widget
	{
		QTabBar *ResourceSplitter::dragTab = nullptr;
		HighlightWidget *ResourceSplitter::highlightWidget = nullptr;

		ResourceSplitter::ResourceSplitter(Manager::WindowManager *windowManager, QWidget *parent) :
			QSplitter(parent), parentWidget(parent), windowManager(windowManager), focusedEditor(nullptr)
		{
			setChildrenCollapsible(false);
			setAcceptDrops(true);
		}

		void ResourceSplitter::resourceOpen(Model::ResourceBaseItem *resource, const bool &active)
		{
			if (count() == 0 || active == false)
			{
				current = new ResourceTab(this);
				addWidget(current);
				tabs.push_back(current);
				current->end = ResourceTab::Left;
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
			}

			Resource::Editor *widget = current->resourceOpen(resource);
			focusWidget(widget);

			connect(widget, &Resource::Editor::isModified, current, &ResourceTab::modifiedWidget);
			connect(widget, &Resource::Editor::isFocused, current, &ResourceTab::focused);
		}

		void ResourceSplitter::resourceAddEditor(Model::ResourceBaseItem *item,
			const Resource::Factory *factory, Resource::Serializer *serializer,
			const bool &active)
		{
			if (count() == 0 || active == false)
			{
				current = new ResourceTab(this);
				addWidget(current);
				tabs.push_back(current);
				current->end = ResourceTab::Left;
			}
			else
			{
				for (ResourceTab *i : tabs)
				{
					if (i->contains(item))
					{
						return;
					}
				}
			}
			qDebug() << current;
			Resource::Editor *editor = factory->create(item->root(), current);
			qDebug() << editor->getResourceTab();
			qDebug() << "Setting new directory." << item->root()->directory();
			QDir::setCurrent(item->root()->directory());
			serializer->read(editor, item->toContentItem()->resource);

			current->setCurrentIndex(current->addTab(editor, item->name()));
			editor->initialize();
			current->widgets.insert(std::pair<Model::ResourceBaseItem*, Resource::Editor*>(item, editor));
			qDebug() << current->widgets.size();
			focusWidget(editor);

			connect(editor, &Resource::Editor::isModified, current, &ResourceTab::modifiedWidget);
			connect(editor, &Resource::Editor::isFocused, current, &ResourceTab::focused);
		}

		void ResourceSplitter::movePage(const int &index, ResourceSplitter *splitter, const uint8_t settings)
		{
			if (splitter == this)
			{
				qDebug() << current;

				// Find the next consecutive resource tab.
				ResourceTab *clone, *tab = nullptr;
				if (tabs.size() != 0 && current != nullptr)
				{
					if (!(settings & Previous))
					{
						for (auto i = tabs.begin(); i != tabs.end()-1; ++i)
						{
							if ((*i) == current)
							{
								tab = (*(i+1));
								if (current->count() == 1 && !(settings & Clone))
								{
									tabs.erase(i);
								}
								break;
							}
						}
						if (current == (*(tabs.end()-1)) && current->count() == 1 && !(settings & Clone))
						{
							qDebug() << "Missing Code.";
							//tabs.pop_back();
						}
					}
					else
					{
						for (auto i = tabs.rbegin(); i != tabs.rend()-1; ++i)
						{
							if ((*i) == current)
							{
								tab = (*(i+1));
								if (current->count() == 1 && !(settings & Clone))
								{
									tabs.erase(i.base());
								}
								break;
							}
						}
						if (current == (*(tabs.rend()-1)) && current->count() == 1 && !(settings & Clone))
						{
							qDebug() << "Missing code.";
							//tabs.pop_front();
						}
					}
				}

				// Add the widget.
				if (tab != nullptr)
				{
					Resource::Editor *editor = static_cast<Resource::Editor*>(current->widget(index));

					if (!(settings & Clone))
					{
						if (editor != nullptr)
						{
							disconnect(editor, &Resource::Editor::isModified, current, &ResourceTab::modifiedWidget);
							disconnect(editor, &Resource::Editor::isFocused, current, &ResourceTab::focused);
							connect(editor, &Resource::Editor::isModified, tab, &ResourceTab::modifiedWidget);
							connect(editor, &Resource::Editor::isFocused, tab, &ResourceTab::focused);
						}
						clone = current;
						current->moveWidget(index, tab);
					}
					else
					{
						editor = (editor->clone(tab));
						connect(editor, &Resource::Editor::isModified, tab, &ResourceTab::modifiedWidget);
						connect(editor, &Resource::Editor::isFocused, tab, &ResourceTab::focused);
						tab->setCurrentIndex(tab->addTab(editor, current->tabText(index)));
					}

					if (!(settings & Previous) && clone == (*tabs.begin()))
					{
						qDebug() << "RIGHT";
						clone->end = ResourceTab::Left;
					}
					else if ((settings & Previous) && clone == (*tabs.end()))
					{
						qDebug() << "LEFT";
						clone->end = ResourceTab::Right;
					}
					else
					{
						qDebug() << "NONE";
						clone->end = ResourceTab::None;
					}
				}
				else
				{
					tab = new ResourceTab(this);
					Resource::Editor *editor = static_cast<Resource::Editor*>(current->widget(index));

					if (!(settings & Clone))
					{
						if (editor != nullptr)
						{
							disconnect(editor, &Resource::Editor::isModified, current, &ResourceTab::modifiedWidget);
							disconnect(editor, &Resource::Editor::isFocused, current, &ResourceTab::focused);
							connect(editor, &Resource::Editor::isModified, tab, &ResourceTab::modifiedWidget);
							connect(editor, &Resource::Editor::isFocused, tab, &ResourceTab::focused);
						}
						clone = current;
						current->moveWidget(index, tab);
					}
					else
					{
						tab->setCurrentIndex(tab->addTab((editor->clone(tab)), current->tabText(index)));
						connect(editor, &Resource::Editor::isModified, tab, &ResourceTab::modifiedWidget);
						connect(editor, &Resource::Editor::isFocused, tab, &ResourceTab::focused);
					}

					if (!(settings & Previous))
					{
						tabs.push_back(current);
						addWidget(current);
						current->end = ResourceTab::Right;
					}
					else
					{
						tabs.push_front(current);
						insertWidget(0, current);
						current->end = ResourceTab::Left;
					}

					if (!(settings & Previous) && clone == (*tabs.begin()))
					{
						qDebug() << "RIGHT";
						clone->end = ResourceTab::Left;
					}
					else if ((settings & Previous) && clone == (*tabs.end()))
					{
						qDebug() << "LEFT";
						clone->end = ResourceTab::Right;
					}
					else
					{
						qDebug() << "NONE";
						clone->end = ResourceTab::None;
					}

					// Hack to equalize splitter widths.
					moveSplitter(0, 0);
				}
			}
			else
			{

			}
		}

		void ResourceSplitter::focusWidget(Resource::Editor *editor)
		{
			if (focusedEditor != editor)
			{
				windowManager->clearStatusWidgets();
				windowManager->setResourceWidget(editor);
				parentWidget->setWindowFilePath(current->tabText(current->currentIndex()));
				if (editor != nullptr)
				{
					editor->status(windowManager);
				}
				focusedEditor = editor;
			}
			else
			{
				qDebug() << "Bad request";
			}
		}

		void ResourceSplitter::resetState()
		{
			windowManager->resetState();
		}

		QSplitterHandle *ResourceSplitter::createHandle()
		{
			return QSplitter::createHandle();
			//return new ResourceSplitterHandle(orientation(), this);
		}

		void ResourceSplitter::dragEnterEvent(QDragEnterEvent *event)
		{
			if (event->mimeData()->hasFormat("natural-gm/tab-detach") && dragTab != nullptr && count() == 0)
			{
				qDebug() << "ENTERED";
				highlightWidget = new HighlightWidget(parentWidget);
				highlightWidget->setGeometry(geometry());
				highlightWidget->show();
				event->setDropAction(Qt::MoveAction);
				event->accept();
			}
		}

		void ResourceSplitter::dragLeaveEvent(QDragLeaveEvent*)
		{
			delete highlightWidget;
			highlightWidget = nullptr;
		}

		void ResourceSplitter::dropEvent(QDropEvent*)
		{
			delete highlightWidget;
			highlightWidget = nullptr;
		}
	}
}
