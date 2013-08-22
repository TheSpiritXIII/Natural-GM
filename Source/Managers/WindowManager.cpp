/**
 *  @file WindowManager.cpp
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
#include "MainWindow.hpp"
#include "WindowManager.hpp"
#include "ProjectDialog.hpp"
#include "ProjectManager.hpp"
#include "ResourceProjectItem.hpp"
#include <QFileDialog>
#include <algorithm>
#include <QDir>
#include <QDebug>
#include "ResourceProjectItem.hpp"
#include <QToolBar>
#include "AboutDialog.hpp"
#include <QDebug>
#include <QKeyEvent>
#include <QMenuBar>
#include "Widget.hpp"

namespace NGM
{
	namespace Manager
	{
		WindowManager::WindowManager(int argc, char *argv[]) :
			QApplication(argc, argv), actionManager(this, &projectManager), resourceWidget(nullptr)
		{
#ifdef Q_OS_WIN32
			setWindowIcon(QIcon("naturalgm.ico"));
#elif defined Q_OS_MAC
			setWindowIcon(QIcon("naturalgm.icns"));
#endif

			installEventFilter(this);

			setApplicationDisplayName("Natural GM");

			actionManager.actions[ActionManager::ActionNewProject] = new QAction(tr("New Project"), this);
			connect(actionManager.actions[ActionManager::ActionNewProject], &QAction::triggered, [this]()
			{
				this->createProjectDialog();
			});
			actionManager.actions[ActionManager::ActionOpenProject] = new QAction(tr("Open Project"), this);
			connect(actionManager.actions[ActionManager::ActionOpenProject], &QAction::triggered, [this]()
			{
				this->openProjectDialog();
			});
			actionManager.actions[ActionManager::ActionSave] = new QAction(tr("Save"), this);
			actionManager.actions[ActionManager::ActionSave]->setEnabled(false);
			connect(actionManager.actions[ActionManager::ActionSave], &QAction::triggered, [this]()
			{
				this->resourceWidget->isSaved();
				this->resourceWidget->getResourceTabWidget()->resourceSave(this->resourceWidget);
			});
			actionManager.actions[ActionManager::ActionSaveAs] = new QAction(tr("Save As..."), this);
			actionManager.actions[ActionManager::ActionSaveAs]->setEnabled(false);
			actionManager.actions[ActionManager::ActionSaveAll] = new QAction(tr("Save All"), this);
			actionManager.actions[ActionManager::ActionSaveAll]->setEnabled(false);
			actionManager.actions[ActionManager::ActionCut] = new QAction(tr("Cut"), this);
			actionManager.actions[ActionManager::ActionCut]->setEnabled(false);
			actionManager.actions[ActionManager::ActionCopy] = new QAction(tr("Copy"), this);
			actionManager.actions[ActionManager::ActionCopy]->setEnabled(false);
			actionManager.actions[ActionManager::ActionPaste] = new QAction(tr("Paste"), this);
			actionManager.actions[ActionManager::ActionPaste]->setEnabled(false);
			actionManager.actions[ActionManager::ActionRedo] = new QAction(tr("Redo"), this);
			actionManager.actions[ActionManager::ActionRedo]->setEnabled(false);
			actionManager.actions[ActionManager::ActionUndo] = new QAction(tr("Undo"), this);
			actionManager.actions[ActionManager::ActionUndo]->setEnabled(false);
			actionManager.actions[ActionManager::ActionSelectAll] = new QAction(tr("Select All"), this);
			actionManager.actions[ActionManager::ActionSelectAll]->setEnabled(false);
			actionManager.actions[ActionManager::ActionZoomIn] = new QAction(tr("Zoom In"), this);
			actionManager.actions[ActionManager::ActionZoomIn]->setEnabled(false);
			actionManager.actions[ActionManager::ActionZoomOut] = new QAction(tr("Zoom Out"), this);
			actionManager.actions[ActionManager::ActionZoomOut]->setEnabled(false);
			actionManager.actions[ActionManager::ActionZoom] = new QAction(tr("Zoom"), this);
			actionManager.actions[ActionManager::ActionZoom]->setEnabled(false);
			actionManager.actions[ActionManager::ActionAbout] = new QAction(tr("About"), this);
			connect(actionManager.actions[ActionManager::ActionAbout], &QAction::triggered, [this]()
			{
				Dialog::AboutDialog *d = new Dialog::AboutDialog(0);
				d->exec();
			});

			actionManager.reload();
			heirarchy = new Model::ResourceItemModel();
			addWindow();
		}

		WindowManager::~WindowManager()
		{
			for (MainWindow *w : windows)
			{
				delete w;
			}
		}

		MainWindow* WindowManager::addWindow()
		{
			MainWindow *add = new MainWindow(this);
			windows.push_back(add);
			add->show();

			QToolBar *toolbar = new QToolBar(tr("Main"), add);
			toolbar->addAction(actionManager.actions[ActionManager::ActionNewProject]);
			toolbar->addAction(actionManager.actions[ActionManager::ActionOpenProject]);
			toolbar->addAction(actionManager.actions[ActionManager::ActionSave]);
			toolbar->addAction(actionManager.actions[ActionManager::ActionSaveAll]);
			toolbar->setIconSize(QSize(16, 16));
			add->addToolBar(toolbar);

			toolbar = new QToolBar(tr("Clipboard"), add);
			toolbar->addAction(actionManager.actions[ActionManager::ActionCut]);
			toolbar->addAction(actionManager.actions[ActionManager::ActionCopy]);
			toolbar->addAction(actionManager.actions[ActionManager::ActionPaste]);
			toolbar->addSeparator();
			toolbar->addAction(actionManager.actions[ActionManager::ActionUndo]);
			toolbar->addAction(actionManager.actions[ActionManager::ActionRedo]);
			toolbar->addSeparator();
			toolbar->addAction(actionManager.actions[ActionManager::ActionZoomIn]);
			toolbar->addAction(actionManager.actions[ActionManager::ActionZoomOut]);
			toolbar->addAction(actionManager.actions[ActionManager::ActionZoom]);
			toolbar->setIconSize(QSize(16, 16));
			add->addToolBar(toolbar);

			QMenuBar *menuBar = new QMenuBar(add);
			QMenu *menu = new QMenu(tr("File"), add);
			menu->addAction(actionManager.actions[ActionManager::ActionNewProject]);
			menu->addAction(actionManager.actions[ActionManager::ActionOpenProject]);
			menu->addAction(actionManager.actions[ActionManager::ActionSave]);
			menu->addAction(actionManager.actions[ActionManager::ActionSaveAll]);
			menuBar->addMenu(menu);
			menu = new QMenu(tr("Edit"), add);
			menu->addAction(actionManager.actions[ActionManager::ActionCut]);
			menu->addAction(actionManager.actions[ActionManager::ActionCopy]);
			menu->addAction(actionManager.actions[ActionManager::ActionPaste]);
			menu->addSeparator();
			menu->addAction(actionManager.actions[ActionManager::ActionUndo]);
			menu->addAction(actionManager.actions[ActionManager::ActionRedo]);
			menuBar->addMenu(menu);
			menu = new QMenu(tr("Help"), add);
			menu->addAction(actionManager.actions[ActionManager::ActionAbout]);
			menuBar->addMenu(menu);
			add->setMenuBar(menuBar);

			return add;
		}

		void WindowManager::removeWindow(MainWindow *window)
		{
			for (auto w = windows.begin(); w != windows.end(); ++w)
			{
				if ((*w) == window)
				{
					delete window;
					windows.erase(w);
					return;
				}
			}
		}

		void WindowManager::createProjectDialog()
		{
			Dialog::ProjectDialog *d = new Dialog::ProjectDialog(&projectManager, &settingManager, this);
			d->show();
		}

		void WindowManager::addProject(Model::ResourceProjectItem *project)
		{
			heirarchy->append(project);
		}

		void WindowManager::openProjectDialog()
		{
			QFileDialog *d = new QFileDialog(0, tr("Open an Existing Project"));

			QString formats;
			for(auto& i : projectManager.projects)
			{
				formats.append(i.first);
				formats.append("( ");
				for(QString j : i.second->extensions)
				{
					formats.append(j);
					formats.append(" ");
				}
				formats.replace(formats.length(), 1, ')');
				formats += ";;";
			}
			formats.chop(2);

			d->setNameFilter(formats);

			if (d->exec() == QDialog::Accepted)
			{
				QString filename = d->selectedFiles().first();
				QString type = d->selectedNameFilter();
				type.truncate(type.lastIndexOf('('));

				Resource::Project *project = projectManager.projects.find(type)->second;

				Resource::Resource *r = new Resource::Resource(project->type, NULL, filename, Resource::Resource::IsFilename);
				heirarchy->append(new Model::ResourceProjectItem(r, project, filename.right(filename.size()-filename.lastIndexOf('/')-1)));
			}

			d->deleteLater();
		}

		bool WindowManager::eventFilter(QObject *object, QEvent *event)
		{
			if (event->type() == QEvent::KeyPress)
			{
				QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
				if (keyEvent->matches(QKeySequence::New))
				{
					actionManager.actions[ActionManager::ActionNewProject]->trigger();
					return true;
				}
				if (keyEvent->matches(QKeySequence::Open))
				{
					actionManager.actions[ActionManager::ActionOpenProject]->trigger();
					return true;
				}
				if (keyEvent->matches(QKeySequence::Cut))
				{
					actionManager.actions[ActionManager::ActionCut]->trigger();
					return true;
				}
				return false;
			}
			return QObject::eventFilter(object, event);;
		}

		void WindowManager::canCopy(const bool &value)
		{
			actionManager.actions[ActionManager::ActionCut]->setEnabled(value);
			actionManager.actions[ActionManager::ActionCopy]->setEnabled(value);
		}

		void WindowManager::canPaste(const bool &value)
		{
			actionManager.actions[ActionManager::ActionPaste]->setEnabled(value);
		}

		void WindowManager::canSelect(const bool &value)
		{
			actionManager.actions[ActionManager::ActionSelectAll]->setEnabled(value);
		}

		void WindowManager::isModified(const bool &value)
		{
			actionManager.actions[ActionManager::ActionSave]->setEnabled(value);
		}

		void WindowManager::canUndo(const bool &value)
		{
			actionManager.actions[ActionManager::ActionUndo]->setEnabled(value);
		}

		void WindowManager::canRedo(const bool &value)
		{
			actionManager.actions[ActionManager::ActionRedo]->setEnabled(value);
		}

		void WindowManager::setResourceWidget(Resource::Widget *widget)
		{
			if (resourceWidget != nullptr)
			{
				qDebug() << "Not NULLIO.";
				disconnect(resourceWidget, &Resource::Widget::canCopy, this, &WindowManager::canCopy);
				disconnect(resourceWidget, &Resource::Widget::canPaste, this, &WindowManager::canPaste);
				disconnect(resourceWidget, &Resource::Widget::canSelect, this, &WindowManager::canSelect);
				disconnect(resourceWidget, &Resource::Widget::canUndo, this, &WindowManager::canUndo);
				disconnect(resourceWidget, &Resource::Widget::canRedo, this, &WindowManager::canRedo);
				disconnect(actionManager.actions[ActionManager::ActionCut], &QAction::triggered, resourceWidget, &Resource::Widget::cutRequest);
				disconnect(actionManager.actions[ActionManager::ActionCopy], &QAction::triggered, resourceWidget, &Resource::Widget::copyRequest);
				disconnect(actionManager.actions[ActionManager::ActionPaste], &QAction::triggered, resourceWidget, &Resource::Widget::pasteRequest);
				disconnect(actionManager.actions[ActionManager::ActionUndo], &QAction::triggered, resourceWidget, &Resource::Widget::undoRequest);
				disconnect(actionManager.actions[ActionManager::ActionRedo], &QAction::triggered, resourceWidget, &Resource::Widget::redoRequest);
			}
			uint8_t settings = widget->getState();
			qDebug() << "Is really modified?" << settings;
			canCopy(settings & Resource::Widget::CanCopy);
			canPaste(settings & Resource::Widget::CanPaste);
			canSelect(settings & Resource::Widget::CanSelect);
			canUndo(settings & Resource::Widget::CanUndo);
			canRedo(settings & Resource::Widget::CanRedo);
			connect(widget, &Resource::Widget::canCopy, this, &WindowManager::canCopy);
			connect(widget, &Resource::Widget::canPaste, this, &WindowManager::canPaste);
			connect(widget, &Resource::Widget::canSelect, this, &WindowManager::canSelect);
			connect(widget, &Resource::Widget::canUndo, this, &WindowManager::canUndo);
			connect(widget, &Resource::Widget::canRedo, this, &WindowManager::canRedo);
			connect(widget, &Resource::Widget::isModified, this, &WindowManager::isModified);
			connect(actionManager.actions[ActionManager::ActionCut], &QAction::triggered, widget, &Resource::Widget::cutRequest);
			connect(actionManager.actions[ActionManager::ActionCopy], &QAction::triggered, widget, &Resource::Widget::copyRequest);
			connect(actionManager.actions[ActionManager::ActionPaste], &QAction::triggered, widget, &Resource::Widget::pasteRequest);
			connect(actionManager.actions[ActionManager::ActionUndo], &QAction::triggered, widget, &Resource::Widget::undoRequest);
			connect(actionManager.actions[ActionManager::ActionRedo], &QAction::triggered, widget, &Resource::Widget::redoRequest);
			resourceWidget = widget;
		}
	}
}
