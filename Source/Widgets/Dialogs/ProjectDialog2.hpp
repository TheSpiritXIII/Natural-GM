/**
 *  @file ProjectDialog.hpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
 *
 *      This file is part of the Natural GM IDE.
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
#ifndef NGM__PROJECTDIALOG__HPP
#define NGM__PROJECTDIALOG__HPP
#include "SettingManager.hpp"
#include <QDialog>
using NGM::Manager::ProjectPreferences;

class QLabel;
class QCheckBox;
class QLineEdit;
class QToolButton;
class QRadioButton;
class QVBoxLayout;

namespace NGM
{
	namespace Resource
	{
		class Project;
	}
	namespace Manager
	{
		class AppManager;
		class SettingManager;
	}
	namespace Widget
	{
		class ProjectWidget;
	}

	/**************************************************//*!
	*	@brief	Stores a project pointer.
	******************************************************/
	struct ProjectPointer
	{
		const Resource::Project *data;
	};
	namespace Dialog
	{	
		/**************************************************//*!
		*	@brief	A dialog that allows a user to choose a
		*			project type, template and file location.
		******************************************************/
		class ProjectDialog2 final : public QDialog
		{
		public:

			/**************************************************//*!
			*	@brief	Creates the dialog. Parameters are not
			*			set until after the dialog is closed.
			*	@param	projects The chosen project type.
			*	@param	location The chosen user save location.
			*	@param	templater The name of the chosen
			*			template or an empty string is none was
			*			chosen.
			*	@param	preferences Hints for saving settings.
			*
			* This dialog takes several pointers. All pointers
			* are modified and are set when this dialog is
			* accepted. If it is rejected, pointers are cleared.
			******************************************************/
			ProjectDialog2(const Manager::AppManager *manager,
				ProjectPointer *project, QString *location, QString *templater,
				ProjectPreferences *preferences, QWidget *parent = 0);

		private slots:

			/**************************************************//*!
			*	@brief	Executed when the list button is pressed.
			*			Icon mode is turned off.
			******************************************************/
			void listButtonPressed(bool checked);

			/**************************************************//*!
			*	@brief	Executed when the icon button is pressed.
			*			Icon mode is turned on.
			******************************************************/
			void iconButtonPressed(bool checked);

			/**************************************************//*!
			*	@brief	Executed when "Display Files" button is
			*			toggled. Switches the display view, if
			*			possible.
			******************************************************/
			void displayFiles(bool checked);

			/**************************************************//*!
			*	@brief	Executed when "Display Projects" button
			*			is toggled.Switches the display view, if
			*			possible.
			******************************************************/
			void displayProjects(bool checked);

			/**************************************************//*!
			*	@brief	Executed when the project selection is
			*			changed. Labels and templates are
			*			reloaded.
			******************************************************/
			void projectChanged(const Resource::Project *project);

			/**************************************************//*!
			*	@brief	Changes the sort type. This is either 0
			*			for ascending or 1 for descending.
			******************************************************/
			void sortChanged(int type);

			/**************************************************//*!
			*	@brief	Clears current templates and loads new
			*			ones if they are valid.
			*	@see	addTemplate()
			*	@see	clearTemplate()
			******************************************************/
			void checkTemplates();

			/**************************************************//*!
			*	@brief	Adds an entry to the template list. The
			*			validity of tempaltes is not checked.
			*	@see	checkTemplates()
			******************************************************/
			void addTemplate(const QString &text);

			/**************************************************//*!
			*	@brief	Deletes all templates.
			*	@see	clearTemplates()
			******************************************************/
			void clearTemplates();

			/**************************************************//*!
			*	@brief	Checks for errors in directories, and
			*			there are no errors, this dialog is
			*			accepted.
			******************************************************/
			void choosePressed();

			/**************************************************//*!
			*	@brief	Loads and sets the current directory.
			******************************************************/
			void getDirectory();

			/**************************************************//*!
			*	@brief	Sets the current template name.
			******************************************************/
			void setCurrentTemplate();

			/**************************************************//*!
			*	@brief	Clears all return values, such as the
			*			location and template names and rejects.
			******************************************************/
			void cancelPressed();

		private:

			/**************************************************//*!
			*	@brief	Stores the current selected project.
			******************************************************/
			ProjectPointer *_project;

			/**************************************************//*!
			*	@brief	Stores a location that is modified, if
			*			this dialog is accepted.
			*	@see	choosePressed()
			******************************************************/
			QString * const _location;

			/**************************************************//*!
			*	@brief	Stores a location that is modified, if
			*			this dialog is accepted.
			*	@see	choosePressed()
			******************************************************/
			QString * const _template;

			/**************************************************//*!
			*	@brief	Setting preferences hint.
			******************************************************/
			ProjectPreferences * const _preferences;

			/**************************************************//*!
			*	@brief	Stores the default user directory.
			******************************************************/
			const QString _defaultDirectory;

			/**************************************************//*!
			*	@brief	Displays the currently selected widget.
			******************************************************/
			Widget::ProjectWidget *_projectWidget;

			/**************************************************//*!
			*	@brief	A button that sets the display to "Lists"
			*			when pressed.
			*	@see	listButtonPressed()
			******************************************************/
			QToolButton *_listViewButton;

			/**************************************************//*!
			*	@brief	A button that sets the display to "Icons"
			*			when pressed.
			*	@see	iconButtonPressed()
			******************************************************/
			QToolButton *_iconViewButton;

			/**************************************************//*!
			*	@brief	A button that displays file types when
			*			pressed.
			******************************************************/
			QToolButton *_displayFilesButton;

			/**************************************************//*!
			*	@brief	A button that displays project types when
			*			pressed.
			******************************************************/
			QToolButton *_displayProjectsButton;

			/**************************************************//*!
			*	@brief	Displays the selected project's
			*			description.
			******************************************************/
			QLabel *_projectLabel;

			/**************************************************//*!
			*	@brief	Displays the selected project's list of
			*			extensions.
			******************************************************/
			QLabel *_extensionsLabel;

			/**************************************************//*!
			*	@brief	Stores radio buttons denoting templates.
			******************************************************/
			QVBoxLayout *_radioLayout;

			/**************************************************//*!
			*	@brief	Decides whether or not the selected
			*			directory will become default.
			******************************************************/
			QCheckBox *_defaultCheck;

			/**************************************************//*!
			*	@brief	Decides whether or not to add a new
			*			directory for the project.
			******************************************************/
			QCheckBox *_addCheck;

			/**************************************************//*!
			*	@brief	Stores the current directory to create
			*			the project to.
			******************************************************/
			QLineEdit *_dirEdit;

			/**************************************************//*!
			*	@brief	Stores the name of the project.
			******************************************************/
			QLineEdit *_projectEdit;

			/**************************************************//*!
			*	@brief	Contains a list of all templates buttons.
			******************************************************/
			QList<QRadioButton*> _templateList;

			/**************************************************//*!
			*	@brief	The number of visible templates. This is
			*			never below 1.
			******************************************************/
			int _templates;
		};
	}
}

#endif // NGM__PROJECTDIALOG__HPP
