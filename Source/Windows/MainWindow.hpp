/**
 *  @file MainWindow.hpp
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
#include <QPlainTextEdit>
#include "Project.hpp"
#include "Content.hpp"
#include "ResourceSplitter.hpp"

namespace NGM
{
	namespace Manager
	{
		class WindowManager;
	}

	/**************************************************//*!
	*	@brief	A visual representation of data.
	******************************************************/
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:

		/**************************************************//*!
		*	@brief	Creates a window with default settings.
		******************************************************/
		MainWindow(NGM::Manager::WindowManager *data, QWidget *parent = 0);

		/**************************************************//*!
		*	@brief	All widgets are destroyed.
		******************************************************/
		~MainWindow() {}

		/**************************************************//*!
		*	@brief	The manager from which data is obtained
		*			from before being visually updated.
		******************************************************/
		NGM::Manager::WindowManager *data;

		/**************************************************//*!
		*	@brief	Contains all dock types.
		******************************************************/
		enum Docks
		{
			DockHeirarchy,
			DockProperties,
			DockMessages,
			DockOutput,
			DockSearch,
			DockActions,
			DockCommand,
			DockNotes
		};

		/**************************************************//*!
		*	@brief	Updates the window title by combining
		*			the current filename and application name.
		******************************************************/
		void updateTitle();

protected:

		/**************************************************//*!
		*	@brief	A resource splitter contains editors.
		******************************************************/
		Widget::ResourceSplitter *resourceSplitter;

		/**************************************************//*!
		*	@brief	Manages the close event to ask for user
		*			confirmation.
		******************************************************/
		void closeEvent(QCloseEvent *);

		/**************************************************//*!
		*	@brief	Allocates and shows a status message on
		*			the window. This is necessary before using
		*			statusLabel or statusProgressBar;
		******************************************************/
		void initStatusMessage();

		/**************************************************//*!
		*	@brief	Destroys the current status message.
		******************************************************/
		void destroyStatusMessage();

		/**************************************************//*!
		*	@brief	A label in the status bar. Uses only plain
		*			text (HTML formatting is not default).
		*	@see	initStatusMessage();
		******************************************************/
		QLabel *statusLabel;

		/**************************************************//*!
		*	@brief	A progress bar in the status bar.
		*	@see	initStatusMessage()
		******************************************************/
		QProgressBar *statusProgressBar;

		/**************************************************//*!
		*	@brief	Stores all default dock widgets.
		******************************************************/
		QDockWidget *docks[8];

		/**************************************************//*!
		*	@brief	Contains registered dock widgets.
		******************************************************/
		std::vector<QDockWidget*> docksRegistered;

		/**************************************************//*!
		*	@brief	Displays the main heirarchy.
		*
		*	The heirarchy data is stored in the window manager.
		******************************************************/
		QTreeView *heirarchyView;

		friend class Manager::WindowManager;
		friend class Widget::ResourceSplitter;

		// Overestimate window size.
		uint32_t buff[32];

	private:

		 /**************************************************//*!
		*	@brief	Creates a context menu when the user
		*			right clicks on the heirarchy.
		******************************************************/
		void heirarchyContextMenuRequested(const QPoint &point);

		/**************************************************//*!
		*	@brief	A text edit with temporary text.
		******************************************************/
		QPlainTextEdit *notesTextEdit;

		/**************************************************//*!
		*	@brief	Displays text that is output from the
		*			compiler.
		******************************************************/
		QPlainTextEdit *outputTextEdit;

		/**************************************************//*!
		*	@brief	Displays errors and warnings from the
		*			compiler.
		******************************************************/
		QTableView *messagesTableView;

		/**************************************************//*!
		*	@brief	Displays the current widget's properties.
		******************************************************/
		void *propertyView;

		/**************************************************//*!
		*	@brief	Displays search options and results.
		******************************************************/
		void *searchWidget;

		/**************************************************//*!
		*	@brief	Displays draggable actions.
		******************************************************/
		void *actionsWidget;

		/**************************************************//*!
		*	@brief	A user based command prompt.
		******************************************************/
		void *commandWidget;

		/**************************************************//*!
		*	@brief	The current right clicked/selected item.
		******************************************************/
		Model::ResourceBaseItem *selectedItem;

	private slots:

		/**************************************************//*!
		*	@brief	Opens the heirarchy at the indicated index.
		******************************************************/
		void heirarchyOpenItem(const QModelIndex & index);

		/**************************************************//*!
		*	@brief	De/allocates the heirarchy tree when its
		*			visibility changed.
		******************************************************/
		void heirarchyVisibilityChanged(bool visible);

		/**************************************************//*!
		*	@brief	Opens the current selected item using
		*			the file editor from the specified
		*			factory index.
		******************************************************/
		void openFileEditor(int index);

	};
}

#endif // _NGM_MAINWINDOW__HPP
