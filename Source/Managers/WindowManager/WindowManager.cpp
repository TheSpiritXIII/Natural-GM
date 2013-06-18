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
#include "WindowManager.hpp"
#include "MainWindow.hpp"
#include "QDebug"
#include <algorithm>

namespace NGM
{
	namespace Manager
	{
		WindowManager::WindowManager()
		{
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
	}
}
