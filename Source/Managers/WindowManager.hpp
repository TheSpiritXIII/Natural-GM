/**
 *  @file WindowManager.hpp
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
#pragma once
#ifndef _NGM_WINDOWMANAGER_HPP
#define _NGM_WINDOWMANAGER__HPP
#include <QApplication>
#include "ActionManager.hpp"
#include "ProjectManager.hpp"
#include "SettingManager.hpp"
#include "../Global.hpp"
#include <QAction>
#include <list>

namespace NGM
{
	class MainWindow;

	namespace Model
	{
		class ResourceItemModel;
		class ResourceProjectItem;
	}

	namespace Widget
	{
		class ResourceSplitter;
	}

	namespace Resource
	{
		class Widget;
	}

	namespace Manager
	{
		class ResourceManager;
		class ProjectManager;
		class ActionManager;

		/**************************************************//*!
		*	@brief	Creates Windows and manages all other
		*			resources and managers.
		******************************************************/
		class WindowManager : public QApplication
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates a single window.
			******************************************************/
			WindowManager(int argc, char *argv[]);

			/**************************************************//*!
			*	@brief	Destroys all windows.
			******************************************************/
			~WindowManager();

			/**************************************************//*!
			*	@brief	Contains all project metadata.
			******************************************************/
			Manager::ProjectManager projectManager;

			/**************************************************//*!
			*	@brief	Contains all actions and icons.
			******************************************************/
			Manager::ActionManager actionManager;

			/**************************************************//*!
			*	@brief	Contains all settings.
			******************************************************/
			Manager::SettingManager settingManager;

			/**************************************************//*!
			*	@brief	Adds and returns a new and empty window.
			******************************************************/
			MainWindow *addWindow();

			/**************************************************//*!
			*	@brief	Permanantely destroys the indicated window.
			******************************************************/
			void removeWindow(MainWindow *window);

			/**************************************************//*!
			*	@brief	Adds a new project to the heirachy model.
			******************************************************/
			void addProject(NGM::Model::ResourceProjectItem *project);

		protected:

			/**************************************************//*!
			*	@brief	Contains all loaded projects and resources.
			******************************************************/
			Model::ResourceItemModel *heirarchy;

			/**************************************************//*!
			*	@brief	Creates a new project with user input.
			******************************************************/
			void createProjectDialog();

			/**************************************************//*!
			*	@brief	Opens an existing project with user input.
			******************************************************/
			void openProjectDialog();

			/**************************************************//*!
			*	@brief	Filters keyboard shortcuts.
			******************************************************/
			bool eventFilter(QObject*object, QEvent *event);

			friend class NGM::MainWindow;
			friend class Manager::ActionManager;

		protected:

			/**************************************************//*!
			*	@brief	Activates cut/copy actions.
			******************************************************/
			void canCopy(const bool &value);

			/**************************************************//*!
			*	@brief	Activates the paste action.
			******************************************************/
			void canPaste(const bool &value);

			/**************************************************//*!
			*	@brief	Activates the select action.
			******************************************************/
			void canSelect(const bool &value);

			/**************************************************//*!
			*	@brief	Activates the undo action.
			******************************************************/
			void canUndo(const bool &value);

			/**************************************************//*!
			*	@brief	Activates the redo action.
			******************************************************/
			void canRedo(const bool &value);

			/**************************************************//*!
			*	@brief	Activates the save actions.
			******************************************************/
			void isModified(const bool &value);

			/**************************************************//*!
			*	@brief	Sets the current resource widget.
			******************************************************/
			void setResourceWidget(Resource::Widget *widget);

			friend class Widget::ResourceSplitter;

		private:

			/**************************************************//*!
			*	@brief	Stores all created windows.
			******************************************************/
			std::list<MainWindow*> windows;

			/**************************************************//*!
			*	@brief	Stores the current focused window.
			******************************************************/
			MainWindow *currentWindow;

			/**************************************************//*!
			*	@brief	Stores the currently focused widget.
			******************************************************/
			Resource::Widget *resourceWidget;
		};
	}
}

#endif // _NGM_WINDOWMANAGER__HPP
