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

namespace NGM
{
	namespace Manager
	{
		/**************************************************//*!
		*	@brief	Contains all managers.
		******************************************************/
		class GlobalManager : public QApplication
		{
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
			*	@brief	Creates all other managers.
			******************************************************/
			GlobalManager(int &argc, char *argv[]);

			/**************************************************//*!
			*	@brief	Checks whether or not it has been
			*			requested for this application to close.
			******************************************************/
			inline bool close()
			{
				return _flags & Close;
			}

			/**************************************************//*!
			*	@brief	Returns the current active instance.
			*			There should only be a single instance at
			*			a time.
			******************************************************/
			inline static GlobalManager *instance()
			{
				return _instance;
			}

			/**************************************************//*!
			*	@brief	Returns the window manager instance.
			******************************************************/
			inline void *windowManager()
			{
				nullptr;
			}

			/**************************************************//*!
			*	@brief	Returns the plugin manager instance.
			******************************************************/
			inline void *pluginManager()
			{
				nullptr;
			}

			/**************************************************//*!
			*	@brief	Returns the project manager instance.
			******************************************************/
			inline void *projectManager()
			{
				nullptr;
			}

		private slots:

			/**************************************************//*!
			*	@brief	Checks the message from another process.
			******************************************************/
			void getProcessMessage();

		private:

			/**************************************************//*!
			*	@brief	Returns false if the given flag is
			*			invalid. If valid, the flag is applied.
			*
			* The command checker is NOT strict. It always
			* depends on single character commands.
			******************************************************/
			bool isValidFlag(const QString &flag);

			/**************************************************//*!
			*	@brief	Stores the current instance.
			******************************************************/
			static GlobalManager *_instance;

			/**************************************************//*!
			*	@brief	Stores a server, used for checking when
			*			other processes are created.
			******************************************************/
			QLocalServer *server;

			/**************************************************//*!
			*	@brief	Stores all flags.
			*	@see	Flags
			******************************************************/
			uint8_t _flags;

		};
	}
}

#endif // NGM__GLOBALMANAGER__HPP
