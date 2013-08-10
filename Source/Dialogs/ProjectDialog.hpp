/**
 *  @file ProjectDialog.hpp
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
#ifndef _NGM_PROJECTDIALOG__HPP
#define _NGM_PROJECTDIALOG__HPP
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QListWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "ProjectManager.hpp"
#include "Project.hpp"
#include <list>
#include <map>

namespace NGM
{
	namespace Manager
	{
		class WindowManager;
		class ProjectManager;
		class SettingManager;
	}
	namespace Dialog
	{
		/**************************************************//*!
		*	@brief	A dialog that shows a list of registered
		*			project types and that lets the user pick
		*			one of those types.
		******************************************************/
		class ProjectDialog : public QDialog
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates the dialog.
			******************************************************/
			ProjectDialog(Manager::ProjectManager *projectManager,
						  Manager::SettingManager *settingManager,
						  Manager::WindowManager *windowManager,
						  QWidget *parent = 0);

			/**************************************************//*!
			*	@brief	Removes all associated widget.
			******************************************************/
			~ProjectDialog();

		private slots:

			/**************************************************//*!
			*	@brief	Closes the dialog without any further actions.
			******************************************************/
			void cancelRequest();

			/**************************************************//*!
			*	@brief	Open a browse dialog for finding directories.
			******************************************************/
			void browseRequest();

			/**************************************************//*!
			*	@brief	Exits and creates the chosen project type.
			******************************************************/
			void chooseRequest();

			/**************************************************//*!
			*	@brief	Updates the projects list based on the
			*			current category item.
			******************************************************/
			void updateList(QTreeWidgetItem *current, QTreeWidgetItem *);

			/**************************************************//*!
			*	@brief	Updates the description to the project on
			*			the indicated item row.
			******************************************************/
			void updateDescription(QString text);

		protected:

			/**************************************************//*!
			*	@brief	Makes the dialog partially transparent.
			******************************************************/
			void changeEvent(QEvent *event);

		private:

			/**************************************************//*!
			*	@brief	Shows projects in a list.
			******************************************************/
			QListWidget *projectList;

			/**************************************************//*!
			*	@brief	Shows a project category tree.
			******************************************************/
			QTreeWidget *projectTree;

			/**************************************************//*!
			*	@brief	Contains all projects in the current
			*			selected category.
			******************************************************/
			std::list<Resource::Project*> projects;

			/**************************************************//*!
			*	@brief	Contains the main user settings.
			******************************************************/
			Manager::WindowManager *windowManager;

			/**************************************************//*!
			*	@brief	Contains all registered projects types.
			******************************************************/
			Manager::ProjectManager *projectManager;

			/**************************************************//*!
			*	@brief	Contains all settings.
			******************************************************/
			Manager::SettingManager *settingManager;

			/**************************************************//*!
			*	@brief	Shows the description of the currently
			*			selected project type.
			******************************************************/
			QLabel *description;

			/**************************************************//*!
			*	@brief	Shows the location of the currently
			*			selected directory.
			******************************************************/
			QLineEdit *directoryEdit;

			/**************************************************//*!
			*	@brief	An editable widget for naming projects.
			******************************************************/
			QLineEdit *projectEdit;

			/**************************************************//*!
			*	@brief	Decides whether or not to add a seperate
			*			directory for the project type.
			******************************************************/
			QCheckBox *dirAddCheck;

			/**************************************************//*!
			*	@brief	Decides whether the currently selected
			*			project type is default.
			******************************************************/
			QCheckBox *dirDefaultCheck;

			/**************************************************//*!
			*	@brief	Decides whether the currently selected
			*			directory is used as the default.
			******************************************************/
			QCheckBox *dirUseCheck;

			/**************************************************//*!
			*	@brief	Decides whether to create a temporary
			*			project or not.
			******************************************************/
			QCheckBox *dirTempCheck;

			/**************************************************//*!
			*	@brief	A button for browsing directories.
			******************************************************/
			QPushButton *browseButton;

			/**************************************************//*!
			*	@brief	A cache for storing the project types in
			*			the currently selected category.
			******************************************************/
			std::map<const QString, Resource::Project*> cache;

			/**************************************************//*!
			*	@brief	Makes sure the dialog does not fade.
			******************************************************/
			bool wait;
		};
	}
}

#endif // _NGM_NGMPROJECTDIALOG__HPP*/
