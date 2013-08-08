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
#include "Global.hpp"
#include <QShortcut>
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

			/*! Contains bit flags for the settings variable. */
			enum Preferences
			{
				ShowWelcome         =   0b0000000000000001,
				NoResourceTabs      =   0b0000000000000010,
				HideResourceTabs    =   0b0000000000000100,
				ExternalResources   =   0b0000000000001000,
				CodeUseTabs         =   0b0000000000010000,
				CodeWarpNone        =   0b0000000000000000,
				CodeWarpChar        =   0b0000000000100000,
				CodeWarpWord        =   0b0000000001100000,
				CodeEdgeNone        =   0b0000000000000000,
				CodeEdgeLine        =   0b0000000010000000,
				CodeEdgeBack        =   0b0000000110000000,
				UseDirectory		=	0b0000001000000000,
				AddDirectory		=	0b0000010000000000,
				PreloadData			=	0b0000100000000000,
				UniqueIcons			=	0b0001000000000000
			};

			/**************************************************//*!
			*	@brief	Creates a single window.
			******************************************************/
			WindowManager(int argc, char *argv[]);

			/**************************************************//*!
			*	@brief	Destroys all windows.
			******************************************************/
			~WindowManager();

			/*! Contains all project metadata and icons. */
			Manager::ProjectManager projectManager;

			/*! Contains all actions and icons. */
			Manager::ActionManager actionManager;

			/*! Holds all registered resource types. */
			std::vector<QAction*> resources;

			/*! Adds and returns a new and empty window. */
			NGM::MainWindow *addWindow();

			/*! Permanantly removes the indicated window. */
			void removeWindow(MainWindow *window);

			/*! Add new project to the heirarchy model. */
			void addProject(NGM::Model::ResourceProjectItem *project);

			/*! Contains the default directory location. */
			QString directory;

			/*! Contains settings bits used by dialogs and windows. */
			uint16_t settings;

		protected:

			Model::ResourceItemModel *hierarchy;
			// ColumnModel *messages;

			void createProjectDialog();

			void openProjectDialog();

			friend class NGM::MainWindow;
			friend class Manager::ActionManager;

			bool eventFilter(QObject*, QEvent *event);

			void canCopy(const bool &i);
			void canPaste(const bool &i);
			void isModified(const bool &i);

		private:

			/*! Holds all created windows. */
			std::list<MainWindow*> windows;

			/**************************************************//*!
			*	@brief	Stores the current focused window.
			******************************************************/
			MainWindow *currentWindow;

			bool windowType;
		};
	}
}

#endif // _NGM_WINDOWMANAGER__HPP
