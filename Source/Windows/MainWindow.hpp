/**
 *  @file MainWindow.hpp
 *  @brief Declares a window class which controls properties.
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
#ifndef _NGM_MAINWINDOW__HPP
#define _NGM_MAINWINDOW__HPP
#include <QMainWindow>
#include <QDockWidget>
#include <vector>

#include <QTreeView>
#include <QPushButton>
#include "BasicItem.hpp"
#include "BasicModel.hpp"
#include <QVBoxLayout>
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>

namespace NGM
{
	namespace Manager
	{
		class WindowManager;
	}

	using std::vector;

	class MainWindow : public QMainWindow
	{
	public:

		/*! Creates the main window. */
		MainWindow(NGM::Manager::WindowManager *data, QWidget *parent = 0);

		/*! Removes main winRobdow. */
		~MainWindow() {}

		/*! Stores property data. */
		NGM::Manager::WindowManager *data;

		/*! A list of default dock types. */
		enum Docks
		{
			DockHierarchy,
			DockProperties,
			DockMessages,
			DockOutput,
			DockSearch,
			DockActions
		};

		/*! Updates the window title. */
		void updateTitle();

	protected:

		/*! Main dock widgets. */
		QDockWidget *docks[6];

		/*! Other, registered dock widgets. */
		std::vector<QDockWidget*> docksRegistered;

		/*! Defines whether or not to update the data. */
		bool active;

		friend class WindowManager;

		Model::BasicItem *item;
		QStandardItem *item2;
	};
}

#endif // _NGM_MAINWINDOW__HPP
