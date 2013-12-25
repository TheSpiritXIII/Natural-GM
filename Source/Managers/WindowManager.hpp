/**
 *  @file WindowManager.hpp
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
#pragma once
#ifndef _NGM_WINDOWMANAGER_HPP
#define _NGM_WINDOWMANAGER__HPP
#include "PluginManager.hpp"
#include <QApplication>
#include <QSharedMemory>
#include <QItemSelectionModel>
#include "ActionManager.hpp"
#include "ProjectManager.hpp"
#include "SettingManager.hpp"
#include "../Global.hpp"
#include <QStatusBar>
#include <QAction>
#include <queue>
#include <list>

namespace NGM
{
	class MainWindow;

	namespace Model
	{
		class ResourceBaseItem;
		class ResourceProjectItem;
	}

	namespace Widget
	{
		class ResourceTabWidget;
		class ResourceSplitter;
	}

	namespace Resource
	{
		class Editor;
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

			/**************************************************//*!
			*	@return	True if the current window's status bar
			*			is currently busy or the currently active
			*			widget is not a window, false otherwise.
			******************************************************/
			bool statusBarBusy();

			/**************************************************//*!
			*	@return	Adds a widget to the current window's
			*			status widget.
			*	@see	statusBarBusy
			******************************************************/
			void addStatusWidget(QWidget *widget, const int &size);

			/**************************************************//*!
			*	@return	Hides the current window's status
			*			widgets.
			******************************************************/
			void clearStatusWidgets();

		protected:

			/**************************************************//*!
			*	@brief	Contains all loaded projects and resources.
			******************************************************/
			QItemSelectionModel *selectionModel;//heirarchy;

			/**************************************************//*!
			*	@brief	Contains all loaded project items.
			******************************************************/
			Model::ResourceItemModel *heirarchy;

			/**************************************************//*!
			*	@brief	Creates a new project with user input.
			******************************************************/
			void createProjectDialog(const bool &files);

			/**************************************************//*!
			*	@brief	Opens an existing project with user input.
			******************************************************/
			void openProjectDialog(const bool &files);

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
			*	@brief	Activates the zoom in action.
			******************************************************/
			void canZoomIn(const bool &value);

			/**************************************************//*!
			*	@brief	Activates the zoom out action.
			******************************************************/
			void canZoomOut(const bool &value);

			/**************************************************//*!
			*	@brief	Activates the save actions.
			******************************************************/
			void isModified(const bool &value);

			/**************************************************//*!
			*	@brief	Sets the current resource widget.
			******************************************************/
			void setResourceWidget(Resource::Editor *widget);

			/**************************************************//*!
			*	@brief	Resets all actions.
			******************************************************/
			void resetState();

			friend class Widget::ResourceSplitter;

		private:

			PluginManager pluginManager;

			/**************************************************//*!
			*	@brief	Stores all created windows.
			******************************************************/
			std::list<MainWindow*> windows;

			/**************************************************//*!
			*	@brief	Stores the current focused window.
			******************************************************/
			MainWindow *currentWindow;

			/**************************************************//*!
			*	@brief	Stores the current focused window.
			******************************************************/
			Widget::ResourceTabWidget *currentTabWidget;

			/**************************************************//*!
			*	@brief	Stores the currently focused widget.
			******************************************************/
			Resource::Editor *resourceWidget;

			/**************************************************//*!
			*	@brief	Decides whether a window or dialog is the
			*			current active type. Active type is true
			*			if it is a window, false otherwise.
			******************************************************/
			bool activeType;

			/**************************************************//*!
			*	@brief	Stores a message for statusbars.
			******************************************************/
			QString message;

			/**************************************************//*!
			*	@brief	Stores a message for statusbars.
			******************************************************/
			int progressMax;

			/**************************************************//*!
			*	@brief	Stores a message for statusbars.
			******************************************************/
			int progressMin;

			/**************************************************//*!
			*	@brief	Stores a message for statusbars.
			******************************************************/
			int progressCurrent;

			/**************************************************//*!
			*	@return	Stores all current status bar widgets.
			******************************************************/
			std::queue<QWidget*> statusBarWidgets;

			/**************************************************//*!
			*	@brief	Asks user confirmation to close an indicated window.
			******************************************************/
			void closeWindow(MainWindow *window);

			/**************************************************//*!
			*	@brief	Forcefully destroys the indicated window.
			******************************************************/
			void destroyWindow(MainWindow *window);

			/**************************************************//*!
			*	@brief	Asks the user if they want to save any items.
			*	@param	list A detailed list of modified items.
			*	@see	Choice
			******************************************************/
			int saveRequest(const QString &list);

			/**************************************************//*!
			*	@brief	Asks the user if they want to quit the
			*			application.
			******************************************************/
			void exitRequest();

			/**************************************************//*!
			*	@brief	Gathers all modified editors in the
			*			indicated window and adds it to a list.
			******************************************************/
			void findModifiedFiles(MainWindow *window, QString &list);

			/**************************************************//*!
			*	@brief	Returns a viable project type for the
			*			indicated filename. This is determined
			*			by the file extension and/or name.
			******************************************************/
			Resource::Project *projectType(const QString &filename);

			void saveResource(Resource::Editor *editor, Model::ResourceBaseItem *item);
			Model::ResourceBaseItem *createProject(const QString &filename, Resource::Project *project);

			/**************************************************//*!
			*	@brief	Basic user dialog choices.
			******************************************************/
			enum Choice
			{
				Yes		=	1,
				No		=	2
			};
		};
	}
}

#endif // _NGM_WINDOWMANAGER__HPP
