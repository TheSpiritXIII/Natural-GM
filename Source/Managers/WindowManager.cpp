/**
 *  @file WindowManager.cpp
 *  @brief Defines a class that manages basic settings with windows.
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

namespace NGM
{
	namespace Manager
	{
		WindowManager::WindowManager() : actionManager(this, &projectManager), directory(QDir::homePath()+"/Documents/GameMaker/Projects")
		{
			actionManager.actions[ActionManager::ActionPreferences] = new QAction(tr("Preferences"), this);
			actionManager.actions[ActionManager::ActionPreferences]->setShortcut(QKeySequence::New);
			actionManager.actions[ActionManager::ActionOpen] = new QAction(tr("Open"), this);
			actionManager.actions[ActionManager::ActionOpen]->setShortcut(QKeySequence::Open);
			connect(actionManager.actions[ActionManager::ActionPreferences], &QAction::triggered, [this]()
			{
				this->createProjectDialog();
			});
			connect(actionManager.actions[ActionManager::ActionOpen], &QAction::triggered, [this]()
			{
				this->openProjectDialog();
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
			add->addAction(actionManager.actions[ActionManager::ActionPreferences]);
			add->addAction(actionManager.actions[ActionManager::ActionOpen]);
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
			Dialog::ProjectDialog d(&projectManager, this);
			d.exec();
		}

		void WindowManager::addProject(Model::ResourceProjectItem *project)
		{
			hierarchy->append(project);
		}

		void WindowManager::openProjectDialog()
		{
			QFileDialog d(0, tr("Open an Existing Project"));

			QString formats = tr("All Files")+"  (*.*);;";
			for(auto& i : projectManager.projects_)
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

			Resource::Project *project = projectManager.projects_.find(type)->second;

			Resource::Resource *r = new Resource::Resource(project->type, NULL, filename, Resource::Resource::IsFilename);
			hierarchy->append(new Model::ResourceProjectItem(r, project, "Loaded file."));
			//windows.front()->resourceSplitter->resourceOpen()
			//project->widget()
		}
	}
}
