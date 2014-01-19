/**
 *  @file GlobalManager.hpp
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
#ifndef NGM__GLOBALMANAGER__HPP
#define NGM__GLOBALMANAGER__HPP
#include <QApplication>
#include <QLocalServer>
#include "IconManager.hpp"
#include "ProjectManager.hpp"
#include "SettingManager.hpp"
#include "ResourceItemModel.hpp"

class QAction;
class QKeyEvent;

namespace NGM
{
	namespace Widget
	{
		class ResourceWindow;
	}
	namespace Manager
	{
		/**************************************************//*!
		*	@brief	Manages basic application startup, window
		*			creation and keyboard shortcuts.
		******************************************************/
		class AppManager : public QApplication
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Application command flags.
			******************************************************/
			enum Flags
			{
				Close			=	0x01,	// Reqests to close the window.
				MultiWindow		=	0x02,	// -m: Ignores shared memory.
				SafeMode		=	0x04	// -s: Disables plugins.
			};

			/**************************************************//*!
			*	@brief	Creates all other managers. Also checks
			*			arguments and connects to other
			*			processes before creating a window.
			******************************************************/
			AppManager(int &argc, char *argv[]);

			/**************************************************//*!
			*	@brief	Deletes all other managers.
			******************************************************/
			~AppManager();

			/**************************************************//*!
			*	@brief	Checks whether or not it has been
			*			requested for this application to close.
			******************************************************/
			inline bool close() const
			{
				return _flags & Close;
			}

			/**************************************************//*!
			*	@brief	Creates and returns a new window.
			******************************************************/
			Widget::ResourceWindow *createWindow();

			/**************************************************//*!
			*	@brief	Stores the current active resource
			*			window.
			*
			* Plugins are allowed to modify this at will,
			* provided that it is changed when it makes sense.
			* This includes having background resource windows
			* processing information. Keep in mind that whenever
			* a window gets focuse, this variable will be changed
			* to that window.
			******************************************************/
			Widget::ResourceWindow *activeResourceWindow;

			/**************************************************//*!
			*	@brief	Returns all open windows.
			******************************************************/
			inline QList<Widget::ResourceWindow*> windows() const
			{
				return _windows;
			}

			/**************************************************//*!
			*	@brief	Checks if the key matches an action, and
			*			triggers the action if it does.
			*
			* If the key is being held, then this function does
			* not execute any actions. In addition, if an action
			* was indeed triggered, then the event is accepted.
			******************************************************/
			void processKeyPress(QKeyEvent *);

			/**************************************************//*!
			*	@brief	Adds an actions. Users are able to add
			*			these actions into toolbars and menus,
			*			based on an internal name. Returns false
			*			if there was a name clash and the action
			*			was not added.
			*
			* The name is an internal name, so it is best to
			* randomly generate it or prefix it with the plugin
			* name to prevent clashing. Clashes are checked for
			* so insertion is O(nlogn).
			*
			* Also, once an action is added through this
			* function, it is also deleted by this class.
			******************************************************/
			bool addAction(const QString &name, QAction *action);

			/**************************************************//*!
			*	@brief	Returns the plugin manager instance.
			******************************************************/
			inline void *pluginManager() const
			{
				return nullptr;
			}

			/**************************************************//*!
			*	@brief	Returns the project manager instance.
			******************************************************/
			inline const ProjectManager *projectManager() const
			{
				return &_projectManager;
			}

			/**************************************************//*!
			*	@brief	Returns the icon manager instance.
			******************************************************/
			inline IconManager *iconManager() const
			{
				return const_cast<IconManager*>(&_iconManager);
			}

			inline const SettingManager *settingManager() const
			{
				return &_settingManager;
			}

			// to do.
			// void open(const QString &file);
			// void close(const int &row);
			// int rows();
			// QString rowText(const int &row);

		public slots:

			/**************************************************//*!
			*	@brief	Displays the about dialog.
			******************************************************/
			static void showAboutDialog();

			/**************************************************//*!
			*	@brief	Displays a functionality warning dialog.
			******************************************************/
			static void showIncomplete();

			/**************************************************//*!
			*	@brief	Creates a new project dialog and lets the
			*			user pick a project type.
			******************************************************/
			void showNewProjectDialog();

		signals:

			/**************************************************//*!
			*	@brief	Called when a window is created.
			******************************************************/
			void windowCreated(Widget::ResourceWindow *window);

			/**************************************************//*!
			*	@brief	Called when a window is destroyed.
			******************************************************/
			void windowClosed(Widget::ResourceWindow *window);

		private slots:

			/**************************************************//*!
			*	@brief	Checks the message from another process.
			******************************************************/
			void getProcessMessage();

#ifdef Q_OS_UNIX
			/**************************************************//*!
			*	@brief	When disconnected, it means that another
			*			process has to manage the server instead.
			******************************************************/
			void serverDisconnected();
#endif

			/**************************************************//*!
			*	@brief	Signals icons to be reloaded from the
			*			icon manager.
			******************************************************/
			void reloadActionIcons();

		private:

			/**************************************************//*!
			*	@brief	Returns false if the given flag is
			*			invalid. If valid, the flag is applied.
			*
			* The command checker is NOT strict. It ALWAYS only
			* depends on the first character.
			******************************************************/
			bool isValidFlag(const QString &flag);

			/**************************************************//*!
			*	@brief	Stores a server, used for communicating
			*			with other processes.
			******************************************************/
			QLocalServer *server;

			/**************************************************//*!
			*	@brief	Stores all flags, created when the
			*			application is started.
			*	@see	Flags
			******************************************************/
			uint8_t _flags;

			/**************************************************//*!
			*	@brief	Contains all open windows.
			******************************************************/
			QList<Widget::ResourceWindow*> _windows;

			/**************************************************//*!
			*	@brief	Stores default actions. Actions are
			*			relative to the icon manager's action
			*			icons.
			******************************************************/
			QAction *_actions[64];

			/**************************************************//*!
			*	@brief	Actions created by plugins.
			******************************************************/
			QMap<QString, QAction*> _pluginActions;

			ProjectManager _projectManager;


			/**************************************************//*!
			*	@brief	Stores the icon manager. This should be
			*			initialized in the begining.
			******************************************************/
			IconManager _iconManager;

			SettingManager _settingManager;
			// To do.
			NGM::Model::ResourceItemModel *_hierarchy;

		};
	}
}

#endif // NGM__GLOBALMANAGER__HPP
