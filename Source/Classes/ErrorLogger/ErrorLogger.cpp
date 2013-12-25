/**
 *  @file ErrorLogger.cpp
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
#include "ErrorLogger.hpp"
#include <QMessageBox>
#include <QTextStream>
#include <QIODevice>
#include <QFile>

namespace NGM
{
	namespace Debug
	{
		void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
		{
			QFile file("log.txt");
			file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
			QTextStream stream(&file);
			switch (type)
			{
			case QtDebugMsg:
				stream << "Debug: "		<< message			<< endl
				<< "\tAt File: "		<< context.file		<< endl
				<< "\tIn Function: "	<< context.function	<< endl
				<< "\tAt Line Number: "	<< context.line		<< endl;
				break;
			case QtWarningMsg:
				stream << "Warning: "	<< message			<< endl
				<< "\tAt File: "		<< context.file		<< endl
				<< "\tIn Function: "	<< context.function	<< endl
				<< "\tAt Line Number: "	<< context.line		<< endl;
				break;
			case QtCriticalMsg:
				stream << "Crticial: "	<< message			<< endl
				<< "\tAt File: "		<< context.file		<< endl
				<< "\tIn Function: "	<< context.function	<< endl
				<< "\tAt Line Number: "	<< context.line		<< endl;
				break;
			case QtFatalMsg:
				QMessageBox::critical(0, "Error", "Critical: " + message +
					+ "\n\tAt File: "			+ context.file
					+ "\n\tIn Function: "		+ context.function
					+ "\n\tAt Line Number: "	+ context.line + "\n");
				exit(1);
			}
			file.close();
		}
	}
}
