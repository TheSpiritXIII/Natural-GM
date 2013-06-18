/**
 *  @file ErrorLogger.cpp
 *  @brief Defines a Qt based error logging function.
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
#include "ErrorLogger.hpp"
#include <QTextStream>
#include <QIODevice>
#include <QFile>

namespace NGM
{
	namespace Debug
	{
		void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
		{
			QString txt;
			switch (type)
			{
			case QtDebugMsg:
				txt = "Debug: " + msg + QIODevice::Text +
				"At File: " + context.file + QIODevice::Text +
				"In Function: " + context.function + QIODevice::Text +
				"At Line Number: " + context.line + QIODevice::Text;
				break;
			case QtWarningMsg:
				txt = "Warning: " + msg + QIODevice::Text +
				"At File: " + context.file + QIODevice::Text +
				"In Function: " + context.function + QIODevice::Text +
				"At Line Number: " + context.line + QIODevice::Text;
				break;
			case QtCriticalMsg:
				txt = "Critical: " + msg + QIODevice::Text +
				"At File: " + context.file + QIODevice::Text +
				"In Function: " + context.function + QIODevice::Text +
				"At Line Number: " + context.line + QIODevice::Text;
				break;
			case QtFatalMsg:
				txt = "Fatal: " + msg + QIODevice::Text +
				"At File: " + context.file + QIODevice::Text +
				"In Function: " + context.function + QIODevice::Text +
				"At Line Number: " + context.line + QIODevice::Text;
				abort();
			}
			QFile outFile("log.txt");
			outFile.open(QIODevice::WriteOnly | QIODevice::Append);
			QTextStream ts(&outFile);
			ts << txt << endl;
		}
	}
}
