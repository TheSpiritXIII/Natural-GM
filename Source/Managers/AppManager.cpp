/**
 *  @file GlobalManager.cpp
 *	@brief Deals with initialization.
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
#include "ResourceItemModel.hpp"
#include "ResourceContentItem.hpp"
#include "Global.hpp"
#include <QLocalSocket>
#include <QStringList>
#include <QMainWindow>
#include <QAction>
#include <QFile>


// REMOVE
#include <QDebug>

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::setfill;

// Single instance code needs more testing under Unix.

namespace NGM
{
	namespace Manager
	{
		// Setting Manager has to be created last, so it is destroyed first.
		AppManager::AppManager(int &argc, char *argv[]) : QApplication(argc, argv),
			server(nullptr), _flags(0), _projectManager(),
			_iconManager(&_projectManager), _settingManager(&_iconManager)
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

#ifdef Q_OS_UNIX
			while (1)
			{
#endif
				// Don't allow safe mode to connect processes.
				if ((_flags & SafeMode) == 0)
				{
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
#ifdef Q_OS_UNIX
					else
					{
						// Try to connect to server without closing.
						QLocalSocket *socket = new QLocalSocket(this);
						socket->connectToServer(NGM_APPLICATION_KEY);
						if (socket->waitForConnected(1000))
						{
							connect(socket, &QLocalSocket::disconnected, this, &AppManager::serverDisconnected);
							break;
						}
					}
#endif

					server = new QLocalServer(this);
					if (server->listen(NGM_APPLICATION_KEY))
					{
						connect(server, &QLocalServer::newConnection, this, &AppManager::getProcessMessage);
#ifdef Q_OS_UNIX
						break;
#endif
					}
#ifdef Q_OS_UNIX
					else
					{
						// This point should never be reached.
						// Delete in case of prior application crash.
						server->removeServer(NGM_APPLICATION_KEY);
						server->deleteLater();
					}
				}
#endif
			}

			setApplicationName(QStringLiteral("Natural GM"));
			setApplicationDisplayName(applicationName());
			_settingManager.load();

			connect(&_iconManager, &IconManager::iconsChanged, this, &AppManager::reloadActionIcons);
			QIcon *icons =_iconManager.actionIcons;
			_actions[IconManager::NewProject] = new QAction(icons[IconManager::NewProject], tr("New File or Project..."), this);
			_actions[IconManager::OpenProject] = new QAction(icons[IconManager::OpenProject], tr("Open File or Project..."), this);
			_actions[IconManager::Save] = new QAction(icons[IconManager::Save], tr("Save"), this);
			_actions[IconManager::SaveAs] = new QAction(icons[IconManager::SaveAs], tr("Save As..."), this);
			_actions[IconManager::SaveAll] = new QAction(icons[IconManager::SaveAll], tr("Save All"), this);
			_actions[IconManager::SaveProject] = new QAction(icons[IconManager::SaveProject], tr("Save Project"), this);
			_actions[IconManager::SaveProjectAs] = new QAction(icons[IconManager::SaveProjectAs], tr("Save Project As..."), this);
			_actions[IconManager::SaveProjectAll] = new QAction(icons[IconManager::SaveProjectAll], tr("Save All Projects"), this);
			_actions[IconManager::Close] = new QAction(icons[IconManager::Close], tr("Close"), this);
			_actions[IconManager::CloseAll] = new QAction(icons[IconManager::CloseAll], tr("Close All"), this);
			_actions[IconManager::PageSetup] = new QAction(icons[IconManager::PageSetup], tr("Page Setup"), this);
			_actions[IconManager::Print] = new QAction(icons[IconManager::Print], tr("Print"), this);
			_actions[IconManager::Exit] = new QAction(icons[IconManager::Exit], tr("Exit"), this);
			_actions[IconManager::Import] = new QAction(icons[IconManager::Import], tr("Import"), this);
			_actions[IconManager::Export] = new QAction(icons[IconManager::Export], tr("Export"), this);
			_actions[IconManager::Undo] = new QAction(icons[IconManager::Undo], tr("Undo"), this);
			_actions[IconManager::Redo] = new QAction(icons[IconManager::Redo], tr("Redo"), this);
			_actions[IconManager::Cut] = new QAction(icons[IconManager::Cut], tr("Cut"), this);
			_actions[IconManager::Copy] = new QAction(icons[IconManager::Copy], tr("Copy"), this);
			_actions[IconManager::Paste] = new QAction(icons[IconManager::Paste], tr("Paste"), this);
			_actions[IconManager::SelectAll] = new QAction(icons[IconManager::SelectAll], tr("Select All"), this);
			_actions[IconManager::ZoomIn] = new QAction(icons[IconManager::ZoomIn], tr("Zoom In"), this);
			_actions[IconManager::ZoomOut] = new QAction(icons[IconManager::ZoomOut], tr("Zoom Out"), this);
			_actions[IconManager::Zoom] = new QAction(icons[IconManager::Zoom], tr("Zoom"), this);
			_actions[IconManager::FindReplace] = new QAction(icons[IconManager::FindReplace], tr("Find and Replace"), this);
			_actions[IconManager::Build] = new QAction(icons[IconManager::Build], tr("Build"), this);
			_actions[IconManager::BuildAll] = new QAction(icons[IconManager::BuildAll], tr("Build All"), this);
			_actions[IconManager::Rebuild] = new QAction(icons[IconManager::Rebuild], tr("Rebuild"), this);
			_actions[IconManager::RebuildAll] = new QAction(icons[IconManager::RebuildAll], tr("Rebuild All"), this);
			_actions[IconManager::Clean] = new QAction(icons[IconManager::Clean], tr("Clean"), this);
			_actions[IconManager::CleanAll] = new QAction(icons[IconManager::CleanAll], tr("Clean All"), this);
			_actions[IconManager::Run] = new QAction(icons[IconManager::Run], tr("Run"), this);
			_actions[IconManager::Debug] = new QAction(icons[IconManager::Debug], tr("Debug"), this);
			_actions[IconManager::Stop] = new QAction(icons[IconManager::Stop], tr("Stop"), this);
			_actions[IconManager::StepOver] = new QAction(icons[IconManager::StepOver], tr("Step Over"), this);
			_actions[IconManager::StepInto] = new QAction(icons[IconManager::StepInto], tr("Step Into"), this);
			_actions[IconManager::Layout] = new QAction(icons[IconManager::Layout], tr("Layout"), this);
			_actions[IconManager::Preferences] = new QAction(icons[IconManager::Preferences], tr("Preferences"), this);
			_actions[IconManager::About] = new QAction(icons[IconManager::About], tr("About Natural GM"), this);
			_actions[IconManager::Plugins] = new QAction(icons[IconManager::Plugins], tr("Manage Plugins"), this);

			_actions[IconManager::NewProject]->setShortcut(QKeySequence(QKeySequence::New));
			_actions[IconManager::OpenProject]->setShortcut(QKeySequence(QKeySequence::Open));
			_actions[IconManager::Save]->setShortcut(QKeySequence(QKeySequence::Save));
			_actions[IconManager::SaveAll]->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
			_actions[IconManager::Close]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
			_actions[IconManager::CloseAll]->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_W));
			_actions[IconManager::Print]->setShortcut(QKeySequence(QKeySequence::Print));
			_actions[IconManager::Exit]->setShortcut(QKeySequence(QKeySequence::Quit));
			_actions[IconManager::Undo]->setShortcut(QKeySequence(QKeySequence::Undo));
			_actions[IconManager::Redo]->setShortcut(QKeySequence(QKeySequence::Redo));
			_actions[IconManager::Cut]->setShortcut(QKeySequence(QKeySequence::Cut));
			_actions[IconManager::Copy]->setShortcut(QKeySequence(QKeySequence::Copy));
			_actions[IconManager::Paste]->setShortcut(QKeySequence(QKeySequence::Paste));
			_actions[IconManager::SelectAll]->setShortcut(QKeySequence(QKeySequence::SelectAll));
			_actions[IconManager::ZoomIn]->setShortcut(QKeySequence(QKeySequence::ZoomIn));
			_actions[IconManager::ZoomOut]->setShortcut(QKeySequence(QKeySequence::ZoomOut));
			_actions[IconManager::FindReplace]->setShortcut(QKeySequence(QKeySequence::Find));
			_actions[IconManager::Build]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
			_actions[IconManager::BuildAll]->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_B));
			_actions[IconManager::Run]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
			_actions[IconManager::Debug]->setShortcut(QKeySequence(Qt::Key_F5));
			_actions[IconManager::Preferences]->setShortcut(QKeySequence(QKeySequence::Preferences));

			connect(_actions[IconManager::NewProject], &QAction::triggered, this, &AppManager::showNewProjectDialog);
			connect(_actions[IconManager::OpenProject], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Save], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::SaveAs], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::SaveAll], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Close], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::CloseAll], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::PageSetup], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Print], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Exit], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Import], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Export], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Undo], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Redo], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Cut], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Copy], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Paste], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::SelectAll], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::ZoomIn], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::ZoomOut], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::FindReplace], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Build], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::BuildAll], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Rebuild], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::RebuildAll], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Clean], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::CleanAll], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Run], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Debug], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Stop], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::StepOver], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::StepInto], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Layout], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::Preferences], &QAction::triggered, this, &AppManager::showIncomplete);
			connect(_actions[IconManager::About], &QAction::triggered, this, &AppManager::showAboutDialog);
			connect(_actions[IconManager::Plugins], &QAction::triggered, this, &AppManager::showIncomplete);

			_model = new Model::ResourceItemModel(nullptr);
			_model->setSort(true);

			Resource::Project *project = _projectManager.findProject("GML Script");
			qDebug() << project;
			Model::ResourceProjectItem *item = new Model::ResourceProjectItem(nullptr, project, "C:/Intel/Poo.pee", 0);

			Model::ResourceGroupItem *group1 = new Model::ResourceGroupItem("Group 1",
																			Model::ResourceBaseItem::CreateGroups);
			item->insert(group1);

			Model::ResourceGroupItem *group2 = new Model::ResourceGroupItem("Group 2");
			item->insert(group2);

			Model::ResourceContentItem *item1 = new Model::ResourceContentItem(nullptr, "Item 1", 0, group1);
			group1->insert(item1);

			Model::ResourceContentItem *item2 = new Model::ResourceContentItem(nullptr, "Item 2");
			group2->insert(item2);

			Model::ResourceContentItem *item4 = new Model::ResourceContentItem(nullptr, "Item 4");
			group2->insert(item4);

			Model::ResourceContentItem *item3 = new Model::ResourceContentItem(nullptr, "Item 3");
			group2->insert(item3);

			Model::ResourceGroupItem *group3 = new Model::ResourceGroupItem("Group 3");
			item->insert(group3);

			Model::ResourceContentItem *item6 = new Model::ResourceContentItem(nullptr, "Item 6");
			group3->insert(item6);

			_model->insert(item);

			createWindow();

			reloadActionIcons();
		}

		AppManager::~AppManager()
		{
#ifdef Q_OS_UNIX
			if (server != nullptr && server->isListening())
			{
				server->removeServer(NGM_APPLICATION_KEY);
			}
#endif
			QMap<QString, QAction*>::iterator i = _pluginActions.begin();
			while (i != _pluginActions.end())
			{
				delete i.value();
				++i;
			}

			for (size_t i = 0; i != IconManager::ActionSize; ++i)
			{
				delete _actions[i];
			}
		}

		void AppManager::getProcessMessage()
		{
			QLocalSocket *socket = server->nextPendingConnection();
			if (socket == nullptr)
			{
					return;
			}
			socket->waitForReadyRead();
			qDebug() << "MESSAGE:" << socket->readAll();
		}

#ifdef Q_OS_UNIX
		void AppManager::serverDisconnected()
		{

		}
#endif

		bool AppManager::isValidFlag(const QString &flag)
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
