/**
 *  @file GlobalManager.cpp
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
#include "GlobalManager.hpp"
#include "Global.hpp"
#include <QMainWindow>
#include <QStringList>
#include <QLocalSocket>
#include <QFile>

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::setfill;

#include <QDebug>

namespace NGM
{
	namespace Manager
	{
		GlobalManager *GlobalManager::_instance = nullptr;

		GlobalManager::GlobalManager(int &argc, char *argv[]) :
			QApplication(argc, argv), _flags(0)
		{
			int i = 0;
			QString file = "poopoo";
			QStringList args = arguments();
			args.removeFirst();
			if (args.size() != 0)
			{
				if (!isValidFlag(args.at(0)))
				{
					file = arguments()[0];
					i = 1;
				}
			}

			for (; i != args.size(); ++i)
			{
				if (!isValidFlag(args.at(i)))
				{
					cout << "Error: Invalid arguments: Command does not exist.";
					_flags |= Close;
					return;
				}
			}

			/*if (!file.isEmpty() && !QFile::exists(file))
			{
				cout << "Error: Invalid arguments: File does not exist.";
				exit(BadArguments);
			}*/

			if ((_flags & MultiWindow) == 0)
			{
				QLocalSocket socket;
				socket.connectToServer(NGM_APPLICATION_KEY);
				if (socket.waitForConnected(1000))
				{
					QByteArray data(file.toUtf8());
					socket.write(data);
					_flags |= Close;
					socket.waitForBytesWritten();
					return;
				}
			}

			if (_instance != nullptr)
			{
				_flags |= Close;
				return;
			}
			_instance = this;

			server = new QLocalServer(this);
			connect(server, &QLocalServer::newConnection, this, &GlobalManager::getProcessMessage);
			server->listen(NGM_APPLICATION_KEY);

			QMainWindow *window = new QMainWindow();
			window->show();
		}

		void GlobalManager::getProcessMessage()
		{
			QLocalSocket *socket = server->nextPendingConnection();
			if (socket == nullptr)
			{
					return;
			}
			socket->waitForReadyRead();
			qDebug() << "MESSAGE:" << socket->readAll();
		}

		bool GlobalManager::isValidFlag(const QString &flag)
		{
			if (flag.at(0) == QChar('-'))
			{
				int check = 1;
				if (flag.at(1) == QChar('-'))
				{
					check = 2;
				}
				if (flag.at(check) == QChar('h'))
				{
					cout << "-- Natural GM Help --" << endl;
					cout << left << setw(32) << setfill(' ') << "-h, --help";
					cout << left << setw(64) << setfill(' ') << "Displays the help file.";
					cout << endl;
					cout << left << setw(32) << setfill(' ') << "-m, --multiwindow";
					cout << left << setw(64) << setfill(' ') << "Opens an instance in a new window (without combining instances).";
					cout << endl;
					cout << left << setw(32) << setfill(' ') << "-s, --safemode";
					cout << left << setw(64) << setfill(' ') << "Disables all plugin functionality.";
					return false;
				}
				else if (flag.at(check) == QChar('m'))
				{
					_flags |= MultiWindow;
					return true;
				}
			}
			return false;
		}
	}
}
