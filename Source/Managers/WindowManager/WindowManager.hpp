/**
 *  @file WindowManager.hpp
 *  @brief Declares a class that manages basic settings within windows.
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
#pragma once
#ifndef _NGM_WINDOWMANAGER_HPP
#define _NGM_WINDOWMANAGER__HPP
#include "ActionManager.hpp"
#include <QAction>
#include <vector>

namespace NGM
{
	class MainWindow;

	namespace Model
	{
		class BasicModel;
	}

	namespace Manager
	{
		class ResourceManager;
		class ProjectManager;

		/*! Contains actions, icons and other properties. */
		class WindowManager
		{
		public:

			/*! Creates a window. */
			WindowManager();

			/*! Destroys all windows. */
			~WindowManager();

			/*! Contains all actions and icons. */
			ActionManager actionManager;

			/*! Holds all registered resource types. */
			std::vector<QAction*> resources;

			/*! Adds and returns a new and empty window. */
			NGM::MainWindow *addWindow();

			/*! Permanantly removes the indicated window. */
			void removeWindow(MainWindow *window);

		protected:

			Model::BasicModel *hierarchy;
			// ColumnModel *messages;

			friend class NGM::MainWindow;

		private:

			/*! Holds all created windows. */
			std::vector<MainWindow*> windows;
		};
	}
}

#endif // _NGM_WINDOWMANAGER__HPP
