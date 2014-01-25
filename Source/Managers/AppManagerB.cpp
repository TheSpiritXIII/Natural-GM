/**
 *  @file AppManagerB.cpp
 *	@brief Deals with actions commands.
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
#include "AppManager.hpp"
#include "AboutDialog.hpp"
#include "ProjectDialog2.hpp"
#include <QMessageBox>

#include <QDebug>

namespace NGM
{
	namespace Manager
	{
		void AppManager::showIncomplete()
		{
			QMessageBox::warning(0, "Warning", "Functionality has been "
								 "disabled.", QMessageBox::Cancel);
		}

		void AppManager::showAboutDialog()
		{
			Dialog::AboutDialog d;
			d.exec();
		}

		void AppManager::showNewProjectDialog()
		{
			ProjectPointer project;
			QString location, templater;
			Manager::ProjectPreferences preferences;
			Dialog::ProjectDialog2 d(this, &project, &location, &templater,
									 &preferences);
			d.setWindowIcon(*_iconManager.applicationIcon());
			if (d.exec() == QDialog::Accepted)
			{
				showIncomplete();
				qDebug() << project.data->name;
				// createProject(type, location);
			}
		}
	}
}
