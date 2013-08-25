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
#include <QString>
#include <vector>
#include <QLabel>
#include <QProgressBar>

#include <QTreeView>
#include <QPushButton>
#include "ResourceBaseItem.hpp"
#include "ResourceItemModel.hpp"
#include <QVBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>

#include "Project.hpp"
#include "Resource.hpp"
#include "ResourceSplitter.hpp"

namespace NGM
{
	namespace Manager
	{
		class WindowManager;
	}

	using std::vector;

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

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
			DockHeirarchy,
			DockProperties,
			DockMessages,
			DockOutput,
			DockSearch,
			DockActions
		};

		/*! Updates the window title. */
		void updateTitle();

		//void heirarchyOpenProject(Model::ResourceProjectItem *item);

	protected:

		/*! Main dock widgets. */
		QDockWidget *docks[6];

		/*! Other, registered dock widgets. */
		std::vector<QDockWidget*> docksRegistered;

		/*! Defines whether or not to update the data. */
		bool active;

		friend class WindowManager;

		Model::ResourceBaseItem *item;
		QStandardItem *item2;

		Widget::ResourceSplitter *resourceSplitter;
		QTreeView *heirarchyView;

		friend class Manager::WindowManager;

		QLabel *statusLabel;
		QProgressBar *statusProgress;

	private slots:

		void heirarchyOpenItem(const QModelIndex & index);

		void heirarchyVisibilityChanged(bool visible);

		void heirarchySetItem(const QString &name);
	};
}

#endif // _NGM_MAINWINDOW__HPP
