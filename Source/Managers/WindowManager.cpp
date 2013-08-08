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

namespace NGM
{
	namespace Manager
	{
		WindowManager::WindowManager(int argc, char *argv[]) :
			QApplication(argc, argv), actionManager(this, &projectManager),
			directory(QDir::homePath()+"/Documents/GameMaker/Projects")
		{
			installEventFilter(this);

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
			actionManager.actions[ActionManager::ActionSaveAs] = new QAction(tr("Save As..."), this);
			actionManager.actions[ActionManager::ActionSaveAs]->setEnabled(false);
			actionManager.actions[ActionManager::ActionSaveAll] = new QAction(tr("Save All"), this);
			actionManager.actions[ActionManager::ActionSaveAll]->setEnabled(false);
			actionManager.actions[ActionManager::ActionCut] = new QAction(tr("Cut"), this);
			actionManager.actions[ActionManager::ActionCut]->setEnabled(false);
			connect(actionManager.actions[ActionManager::ActionCut], &QAction::triggered, [this]()
			{
				this->currentWindow->resourceSplitter->cut();
			});
			actionManager.actions[ActionManager::ActionCopy] = new QAction(tr("Copy"), this);
			actionManager.actions[ActionManager::ActionCopy]->setEnabled(false);
			actionManager.actions[ActionManager::ActionPaste] = new QAction(tr("Paste"), this);
			actionManager.actions[ActionManager::ActionPaste]->setEnabled(false);
			actionManager.actions[ActionManager::ActionRedo] = new QAction(tr("Redo"), this);
			actionManager.actions[ActionManager::ActionRedo]->setEnabled(false);
			actionManager.actions[ActionManager::ActionUndo] = new QAction(tr("Undo"), this);
			actionManager.actions[ActionManager::ActionUndo]->setEnabled(false);
			actionManager.actions[ActionManager::ActionAbout] = new QAction(tr("About"), this);
			connect(actionManager.actions[ActionManager::ActionAbout], &QAction::triggered, [this]()
			{
				Dialog::AboutDialog *d = new Dialog::AboutDialog(0);
				d->exec();
			});

			actionManager.reload();
			hierarchy = new Model::ResourceItemModel();
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

			currentWindow = add;
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
			Dialog::ProjectDialog *d = new Dialog::ProjectDialog(&projectManager, this);
			d->show();
		}

		void WindowManager::addProject(Model::ResourceProjectItem *project)
		{
			hierarchy->append(project);
		}

		void WindowManager::openProjectDialog()
		{
			QFileDialog d(0, tr("Open an Existing Project"));

			QString formats = tr("All Files")+"  (*.*);;";
			for(auto& i : projectManager.projects)
			{
				formats += i.first + "( ";
				for(QString j : i.second->extensions)
				{
					formats += "*" + j + " ";
				}
				formats.chop(1);
				formats += ");;";
			}
			formats.chop(2);

			d.setNameFilter(formats);

			d.exec();

			QString filename = d.selectedFiles().first();
			QString type = d.selectedNameFilter();
			type.truncate(type.lastIndexOf('('));

			Resource::Project *project = projectManager.projects.find(type)->second;

			Resource::Resource *r = new Resource::Resource(project->type, NULL, filename, Resource::Resource::IsFilename);
			hierarchy->append(new Model::ResourceProjectItem(r, project, filename.right(filename.size()-filename.lastIndexOf('/')-1)));
			//windows.front()->resourceSplitter->resourceOpen()
			//project->widget()
		}

		bool WindowManager::eventFilter(QObject*, QEvent *event)
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
			return false;
		}
	}
}
