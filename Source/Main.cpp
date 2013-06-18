/**
 *  @file Main.cpp
 *  @brief Declares the main entry point.
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
#include <QApplication>
#include "ErrorLogger.hpp"
#include "WindowManager.hpp"

int main(int argc, char *argv[])
{

#ifdef NGM_LOGGER
	qInstallMessageHandler(NGM::Debug::messageHandler);
#endif

	QApplication a(argc, argv);
	a.setApplicationName("Natural GM");

	NGM::Manager::WindowManager data;

#ifdef NGM_LOGGER
	if (QFile("log.txt").exists())
	{
		QMessageBox::critical(0, "Critical Errors Found!",
		"Errors were found when running this program. Please report and send the log file "
		"(log.txt) to the author. Delete the log file after you report it to remove this warning.");
	}
#endif

	return a.exec();
}
